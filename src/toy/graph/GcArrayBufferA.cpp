#include "toy/graph/Standard.hpp"
#include "toy/graph/GcArrayBufferA.hpp"

static void InitBufferData(GLuint *handle,int size,const float *data)
{
	glGenBuffers(1, handle);
	glBindBuffer(GL_ARRAY_BUFFER, *handle);

	/*
	 * GL_STATIC_DRAW    data never changed
	 * GL_STREAM_DRAW    data may changed
	 * GL_DYNAMIC_DRAW   data may changed too many times
	 * *_DRAW
	 * *_READ
	 * *_COPY
	 */
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

using namespace toy;
using namespace graph;

GcArrayBufferA::GcArrayBufferA(std::shared_ptr<toy::graph::Brush> ptr,const std::vector<float> &buffer):_brush(ptr)
{
	InitBufferData(&(_handle),buffer.size(),buffer.data());
}

GcArrayBufferA::GcArrayBufferA(std::shared_ptr<toy::graph::Brush> ptr,const toy::graph::Array3<float> &buffer):_brush(ptr)
{
	InitBufferData(&(_handle),buffer.size(),buffer.data());
}

GcArrayBufferA::~GcArrayBufferA()
{
	glDeleteBuffers(1, &(_handle));
}

void GcArrayBufferA::_bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
}
