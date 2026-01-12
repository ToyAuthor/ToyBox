#include "toy/canvas/Brush.hpp"
#include "toy/canvas/Geometry.hpp"
#include "toy/canvas/Image.hpp"
#include "toy/canvas/detail/DataMgrA.hpp"

using namespace toy;
using namespace canvas;
using namespace _detail;

DataMgrA::DataMgrA()
{
	;
}

DataMgrA::~DataMgrA()
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
	glEnable(GL_BLEND);

	if ( list.size() > 0 )
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

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

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}

	glDisable(GL_BLEND);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
}

void DataMgrA::render(toy::canvas::Brush *brush,float diff)
{
	RenderGeometry(brush,_geometryList);
	RenderImage(brush,diff,_imageList);
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

void DataMgrA::add(toy::canvas::Geometry *array)
{
	_geometryList.push_back(array);
}

void DataMgrA::del(toy::canvas::Geometry *array)
{
	FindAndRemoveElement(array,_geometryList);
}

void DataMgrA::add(toy::canvas::Image *obj)
{
	_imageList.push_back(obj);
}

void DataMgrA::del(toy::canvas::Image *obj)
{
	FindAndRemoveElement(obj,_imageList);
}
