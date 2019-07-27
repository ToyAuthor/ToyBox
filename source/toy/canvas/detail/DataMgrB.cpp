#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Geometry.hpp"
#include "toy/canvas/Image.hpp"
#include "toy/canvas/detail/DataMgrB.hpp"

using namespace toy;
using namespace canvas;
using namespace _detail;

DataMgrB::DataMgrB()
{
	;
}

DataMgrB::~DataMgrB()
{
	;
}

template<typename T>
static inline void RenderGeometry(toy::canvas::Brush *,T &list)
{
	if ( list.size() > 0 )
	{
		glEnableVertexAttribArray(0);

		for ( auto &t : list )
		{
			if ( t->isVisible() )
			{
				t->_bind();
				t->_render();
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(0);
	}
}

template<typename T>
static inline void RenderImage(toy::canvas::Brush *brush,float diff,T &list)
{
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);  // GL_TEXTURE0 is default setting.
	glEnable(GL_TEXTURE_2D);

	if ( list.size() > 0 )
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glClientActiveTexture(GL_TEXTURE1);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		for ( auto &t : list )
		{
			if ( t->isVisible() )
			{
				t->_bind();
				t->_render(brush,diff);
			}
		}

		glBindTexture( GL_TEXTURE_2D, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glClientActiveTexture(GL_TEXTURE0);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
}

void DataMgrB::render(toy::canvas::Brush *brush,float diff)
{
	RenderGeometry(brush,_geometryList);
	RenderImage(brush,diff,_imageList);
//	RenderImage(brush,diff,_imageList2);
}

template<typename T>
static inline void FindAndRemoveElement(T *obj,std::vector<T*> &array)
{
	auto  size = array.size();

	if ( size==0 )
	{
		toy::Oops(TOY_MARK);
		return;
	}

	for ( decltype(size) i=0; i<size ; i++ )
	{
		if ( array[i] == obj )
		{
			array[i] = array[size-1];
			array.pop_back();

			return;
		}
	}

	toy::Oops(TOY_MARK);
}

void DataMgrB::add(toy::canvas::Geometry *array)
{
	_geometryList.push_back(array);
}

void DataMgrB::del(toy::canvas::Geometry *array)
{
	FindAndRemoveElement(array,_geometryList);
}

void DataMgrB::add(toy::canvas::Image *obj)
{
	_imageList.push_back(obj);
}

void DataMgrB::del(toy::canvas::Image *obj)
{
	FindAndRemoveElement(obj,_imageList);
}
