
#pragma once

#include <cstdint>
#include "toy/graph/Standard.hpp"

namespace toy{
namespace graph{

class RawTexture
{
	public:

		RawTexture(const GLuint id);
		~RawTexture();

		const GLuint* get() const;

	private:

		GLuint   _id = 0;
};


}}
