
#pragma once

#include "toy/graph/Export.hpp"

namespace toy{
namespace graph{

class Program;
struct UniformBasePrivate;

class TOY_API_GRAPH UniformBase
{
	public:

		UniformBase(std::shared_ptr<Program>,const std::string &name);
		virtual ~UniformBase();

	protected:

		UniformBasePrivate*       _this = nullptr;
		std::shared_ptr<Program>  _program = nullptr;
};

class TOY_API_GRAPH Uniform1i : public UniformBase
{
	public:

		Uniform1i(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform1i(){}

		void set(int);
};

class TOY_API_GRAPH Uniform2i : public UniformBase
{
	public:

		Uniform2i(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform2i(){}

		void set(int,int);
};

class TOY_API_GRAPH Uniform3i : public UniformBase
{
	public:

		Uniform3i(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform3i(){}

		void set(int,int,int);
};

class TOY_API_GRAPH Uniform4i : public UniformBase
{
	public:

		Uniform4i(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform4i(){}

		void set(int,int,int,int);
};


class TOY_API_GRAPH Uniform1f : public UniformBase
{
	public:

		Uniform1f(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform1f(){}

		void set(float);
};

class TOY_API_GRAPH Uniform2f : public UniformBase
{
	public:

		Uniform2f(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform2f(){}

		void set(float,float);
};

class TOY_API_GRAPH Uniform3f : public UniformBase
{
	public:

		Uniform3f(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform3f(){}

		void set(float,float,float);
};

class TOY_API_GRAPH Uniform4f : public UniformBase
{
	public:

		Uniform4f(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform4f(){}

		void set(float,float,float,float);
};

}}
