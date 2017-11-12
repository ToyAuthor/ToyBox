
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/Array.hpp"

namespace toy{
namespace graph{

class _Texture
{
	public:

		_Texture(){}
		virtual ~_Texture(){}

		// Create a new toy::graph::Texture with different texture coordinate(UV).
		virtual auto create(std::shared_ptr<toy::graph::Array2<float>> textureCoord)->std::shared_ptr<_Texture> =0;

		virtual const void* _data() const=0;
	//	virtual const void* _texcoord() const=0;
};

/*
 * It is a handle for the image that stored on OpenGL.
 * It must be deleted before toy::graph::Brush.
 */
typedef std::shared_ptr<_Texture> Texture;

}}
