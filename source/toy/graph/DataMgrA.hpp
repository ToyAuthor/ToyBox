
#pragma once

#include "toy/Standard.hpp"
#include "toy/graph/Standard.hpp"

namespace toy{
namespace graph{

class Brush;
class Geometry;
class Image;

/*
 * For OpenGL 3.0+
 */
class DataMgrA
{
	public:

		DataMgrA();
		~DataMgrA();

		void render(toy::graph::Brush *brush,float diff);
		void sorting();

		void add(toy::graph::Geometry*);
		void del(toy::graph::Geometry*);
		void add(toy::graph::Image*);
		void del(toy::graph::Image*);

	private:

		std::vector<toy::graph::Geometry*>      _geometryList;
		std::vector<toy::graph::Image*>         _imageList;
};


}}
