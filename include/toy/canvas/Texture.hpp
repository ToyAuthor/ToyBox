
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/Array.hpp"

namespace toy{
namespace canvas{

class _Texture
{
	public:

		virtual ~_Texture(){}

		// Create a new toy::canvas::Texture with different texture coordinate(UV).
		virtual auto create(std::shared_ptr<toy::canvas::Array2<float>> textureCoord)->std::shared_ptr<_Texture> =0;
		virtual auto width()const ->uint32_t = 0;
		virtual auto height()const ->uint32_t = 0;

	protected:

		_Texture(){}

	public:

		virtual const void* _data() const=0;
};

/*
 * It is a handle for the image that stored on OpenGL.
 * It must be deleted before toy::canvas::Brush.
 */
typedef std::shared_ptr<_Texture> Texture;

}}
