
#pragma once

#include "toy/Standard.hpp"
#include "toy/Math.hpp"

namespace toy{
namespace graph{

template<typename T>
class ArrayBase
{
	public:

		ArrayBase(){}
		ArrayBase(int num,T value):_list(num,value){}
		virtual ~ArrayBase(){}

		void clear()
		{
			_list.clear();
		}

		const T* data() const
		{
			return _list.data();
		}

		T& operator [](int index)
		{
			return _list[index];
		}

		int size() const
		{
			return _list.size();
		}

	protected:

		std::vector<T>   _list;
};

template<typename T>
class Array1 : public ArrayBase<T>
{
	public:

		using ArrayBase<T>::_list;

		Array1(){}
		Array1(int num,T value):ArrayBase<T>(num,value){}
		Array1(std::initializer_list<T> list)
		{
			_list.insert(_list.end(), list.begin(), list.end());
		}
		~Array1(){}

		void append(std::initializer_list<T> list)
		{
			_list.insert(_list.end(), list.begin(), list.end());
		}

		void add(T x)
		{
			_list.push_back(x);
		}
};

template<typename T>
class Array2 : public ArrayBase<T>
{
	public:

		using ArrayBase<T>::_list;

		Array2(){}
		Array2(int num,T value):ArrayBase<T>(num,value)
		{
			if ( num%2 != 0 )
			{
				toy::Oops(TOY_MARK);
			}
		}
		Array2(std::initializer_list<T> list)
		{
			_list.insert(_list.end(), list.begin(), list.end());

			if ( _list.size()%2 != 0 )
			{
				toy::Oops(TOY_MARK);
			}
		}
		~Array2(){}

		void append(std::initializer_list<T> list)
		{
			_list.insert(_list.end(), list.begin(), list.end());

			if ( _list.size()%2 != 0 )
			{
				toy::Oops(TOY_MARK);
			}
		}

		void add(T x,T y)
		{
			_list.push_back(x);
			_list.push_back(y);
		}

		void add(const toy::math::Vector2<T> &array)
		{
			_list.push_back(array.x);
			_list.push_back(array.y);
		}
};

template<typename T>
class Array3 : public ArrayBase<T>
{
	public:

		using ArrayBase<T>::_list;

		Array3(){}
		Array3(int num,T value):ArrayBase<T>(num,value)
		{
			if ( num%3 != 0 )
			{
				toy::Oops(TOY_MARK);
			}
		}
		Array3(std::initializer_list<T> list)
		{
			_list.insert(_list.end(), list.begin(), list.end());

			if ( _list.size()%3 != 0 )
			{
				toy::Oops(TOY_MARK);
			}
		}
		~Array3(){}

		void append(std::initializer_list<T> list)
		{
			_list.insert(_list.end(), list.begin(), list.end());

			if ( _list.size()%3 != 0 )
			{
				toy::Oops(TOY_MARK);
			}
		}

		void add(T x,T y,T z)
		{
			_list.push_back(x);
			_list.push_back(y);
			_list.push_back(z);
		}

		void add(const toy::math::Vector3<T> &array)
		{
			_list.push_back(array.x);
			_list.push_back(array.y);
			_list.push_back(array.z);
		}
};

}}
