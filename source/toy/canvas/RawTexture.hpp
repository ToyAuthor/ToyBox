
#pragma once

#include <cstdint>
#include "toy/canvas/Standard.hpp"

namespace toy{
namespace canvas{

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
