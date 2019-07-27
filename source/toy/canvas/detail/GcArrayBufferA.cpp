#include "toy/canvas/Standard.hpp"
#include "toy/canvas/detail/GcArrayBufferA.hpp"

static void InitBufferData(GLuint *handle,int size,const float *data)
{
	glGenBuffers(1, handle);

	if ( *handle==0 )
	{
		throw toy::Exception(TOY_MARK);
	}

	glBindBuffer(GL_ARRAY_BUFFER, *handle);

	/*
	 * GL_STATIC_DRAW    data never changed
	 * GL_STREAM_DRAW    data may changed
	 * GL_DYNAMIC_DRAW   data may changed too many times
	 * *_DRAW
	 * *_READ
	 * *_COPY
	 */
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size, data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

using namespace toy;
using namespace canvas;
using namespace _detail;

GcArrayBufferA::GcArrayBufferA(std::shared_ptr<toy::canvas::Brush> ptr,const std::vector<float> &buffer):_brush(ptr)
{
	InitBufferData(&(_handle),buffer.size(),buffer.data());
}

GcArrayBufferA::GcArrayBufferA(std::shared_ptr<toy::canvas::Brush> ptr,const toy::canvas::Array3<float> &buffer):_brush(ptr)
{
	InitBufferData(&(_handle),buffer.size(),buffer.data());
}

GcArrayBufferA::~GcArrayBufferA()
{
	glDeleteBuffers(1, &(_handle));
}

void GcArrayBufferA::setPosition(const float* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3, data);
	data += 3;
	glBufferSubData(GL_ARRAY_BUFFER, 8*sizeof(float), sizeof(float)*3, data);
	data += 3;
	glBufferSubData(GL_ARRAY_BUFFER,16*sizeof(float), sizeof(float)*3, data);
	data += 3;
	glBufferSubData(GL_ARRAY_BUFFER,24*sizeof(float), sizeof(float)*3, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GcArrayBufferA::_bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
}
