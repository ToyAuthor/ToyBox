#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Program.hpp"
#include "toy/canvas/detail/GcArrayBufferA.hpp"
#include "toy/canvas/detail/GcIndicesA.hpp"
#include "toy/canvas/detail/ImageA.hpp"

static inline std::string GetVertexShaderCode()
{
	#if defined(TOY_LINUX)
		// Ubuntu need this to use VertexAttribPointer.
		std::string    top = "#version 130";
	#else
		std::string    top = "// nothing";
	#endif

	return top + R"(
		varying vec2      TempTexCoord;
		in vec2           toy_TextureCoord;

		void main(void)
		{
			TempTexCoord = toy_TextureCoord;

		//	TempTexCoord = gl_MultiTexCoord0.xy;

			gl_Position = ftransform();
		}
	)";
}

static inline std::string GetFragmentShaderCode()
{
	return R"(
		uniform int       toy_TextureCount;
		uniform sampler2D toy_Sampler0;
		uniform sampler2D toy_Sampler1;
		varying vec2      TempTexCoord;

		void main(void)
		{
			vec4  color01 = texture2D(toy_Sampler0,TempTexCoord);
			vec4  color02 = texture2D(toy_Sampler1,TempTexCoord);

			if ( toy_TextureCount==1 )
			{
				gl_FragColor = color01;
			}
			else if ( toy_TextureCount==2 )
			{
				gl_FragColor = ( color01 + color02 )/2.0;
			}
		}
	)";
}

static inline auto BuildDefaultProgram(std::shared_ptr<toy::canvas::Brush> brush)
->std::shared_ptr<toy::canvas::Program>
{
	toy::Text  text1(GetVertexShaderCode());

	auto   vs = std::make_shared<toy::canvas::Code>(brush,text1,toy::VERTEX_SHADER);

	toy::Text  text2(GetFragmentShaderCode());

	auto   fs = std::make_shared<toy::canvas::Code>(brush,text2,toy::FRAGMENT_SHADER);

	return std::make_shared<toy::canvas::Program>(vs,fs);
}

static auto InitCommonProgram(std::shared_ptr<::toy::canvas::Brush> brush)
->std::shared_ptr<toy::canvas::Program>
{
	static std::weak_ptr<::toy::canvas::Program>   program;

	if ( program.expired() )
	{
		auto  ptr = BuildDefaultProgram(brush);
		program = ptr;
		return ptr;
	}
	else
	{
		return program.lock();
	}
}

using namespace toy;
using namespace canvas;
using namespace _detail;

ImageA::ImageA(std::shared_ptr<::toy::canvas::Brush> brush)
{
	this->setProgram(InitCommonProgram(brush));
}

ImageA::~ImageA()
{
	;
}

void ImageA::visible(bool show)
{
	#if TOY_OPTION_CHECK

		if ( _texture==nullptr )
		{
			// You can't show a image without texture.
			toy::Oops(TOY_MARK);
		}

		if ( _program==nullptr )
		{
			// You can't show a image without shader.
			toy::Oops(TOY_MARK);
		}

	#endif

	_isVisible = show;
}

bool ImageA::isVisible() const
{
	return _isVisible;
}

struct FakeModelBufferPrivate
{
	std::vector<float>     vertex;
	std::vector<uint8_t>   indices;
};

void ImageA::setModel( std::shared_ptr<::toy::canvas::Brush> brush,
                       const ::toy::canvas::ModelBuffer      &data )
{
	auto dev = static_cast<const FakeModelBufferPrivate*>(data._data());

	_vList = std::make_shared<toy::canvas::_detail::GcArrayBufferA>(brush,dev->vertex);
	_iList = std::make_shared<toy::canvas::_detail::GcIndicesA>(brush,dev->indices);
}

void ImageA::setPosition(const float* data)
{
	_vList->setPosition(data);
}

void ImageA::setTexture(::toy::canvas::Texture id)
{
	_texture = id;
}

auto ImageA::getTexture(int index)->::toy::canvas::Texture
{
	if ( index<0 )
	{
		toy::Oops(TOY_MARK);
		return nullptr;
	}

	if ( index==0 )
	{
		return _texture;
	}

	if ( _multiTextureList.size()<static_cast<std::string::size_type>(index) )
	{
		// Don't request a item that doesn't exist.
		toy::Oops(TOY_MARK);
		return nullptr;
	}

	return _multiTextureList[index-1];
}

void ImageA::pushMoreTexture(::toy::canvas::Texture id)
{
	_multiTextureList.push_back(id);
}

void ImageA::setProgram(std::shared_ptr<::toy::canvas::Program> program)
{
	_program = program;

	_var.textureCoord = glGetAttribLocation(_program->_id(), "toy_TextureCoord");
	_var.texture0     = glGetUniformLocation(_program->_id(), "toy_Sampler0");
	_var.texture1     = glGetUniformLocation(_program->_id(), "toy_Sampler1");
	_var.textureCount = glGetUniformLocation(_program->_id(), "toy_TextureCount");

	#if TOY_OPTION_CHECK
	if ( _var.textureCoord == -1 ) toy::Oops(TOY_MARK);   // Toy_TextureCoord not exist!
	if ( _var.texture0     == -1 ) toy::Oops(TOY_MARK);
//	if ( _var.texture1     == -1 ) toy::Oops(TOY_MARK);   // Not every image need second texture.
	if ( _var.textureCount == -1 ) toy::Oops(TOY_MARK);
	#endif
}

auto ImageA::getProgram()->std::shared_ptr<::toy::canvas::Program>
{
	return _program;
}

void ImageA::bind(std::shared_ptr<::toy::canvas::Brush>)
{
	_program->use();

	_vList->_bind();
	_iList->_bind();
}

void ImageA::render(toy::canvas::Brush *brush,float diff)
{
	(void)brush;
	(void)diff;

	#define BUFFER_OFFSET(i) (((char*)0)+(i))

	glUniform1i(_var.textureCount, _multiTextureList.size()+1);
	glUniform1i(_var.texture0, 0);

//	glActiveTexture(GL_TEXTURE0);     // GL_TEXTURE0 already.
	auto   id = *(static_cast<const GLint*>(_texture->_data()));
	glBindTexture( GL_TEXTURE_2D, id );

	if ( _var.texture1 != -1 )
	{
		if ( _multiTextureList.size()>0 )
		{
			glUniform1i(_var.texture1, 1);  // Texture 1
			glActiveTexture(GL_TEXTURE1);
			glBindTexture( GL_TEXTURE_2D, *(static_cast<const GLint*>(_multiTextureList[0]->_data())) );
			glActiveTexture(GL_TEXTURE0);  // Back to default setting.
		}
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));

	glVertexAttribPointer(_var.textureCoord, 2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
	glEnableVertexAttribArray(_var.textureCoord);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

	glDisableVertexAttribArray(_var.textureCoord);

	#undef BUFFER_OFFSET
}

void ImageA::update(float)
{
	;
}
