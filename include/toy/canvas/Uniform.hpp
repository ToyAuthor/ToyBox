
#pragma once

#include "toy/canvas/Export.hpp"

namespace toy{
namespace canvas{

class Program;
struct UniformBasePrivate;

class TOY_API_CANVAS UniformBase
{
	public:

		UniformBase(std::shared_ptr<Program>,const std::string &name);
		virtual ~UniformBase();

	protected:

		std::unique_ptr<UniformBasePrivate>   _this;
		std::shared_ptr<Program>              _program;
};

class TOY_API_CANVAS Uniform1i : public UniformBase
{
	public:

		Uniform1i(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform1i(){}

		void set(int);
};

class TOY_API_CANVAS Uniform2i : public UniformBase
{
	public:

		Uniform2i(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform2i(){}

		void set(int,int);
};

class TOY_API_CANVAS Uniform3i : public UniformBase
{
	public:

		Uniform3i(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform3i(){}

		void set(int,int,int);
};

class TOY_API_CANVAS Uniform4i : public UniformBase
{
	public:

		Uniform4i(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform4i(){}

		void set(int,int,int,int);
};


class TOY_API_CANVAS Uniform1f : public UniformBase
{
	public:

		Uniform1f(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform1f(){}

		void set(float);
};

class TOY_API_CANVAS Uniform2f : public UniformBase
{
	public:

		Uniform2f(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform2f(){}

		void set(float,float);
};

class TOY_API_CANVAS Uniform3f : public UniformBase
{
	public:

		Uniform3f(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform3f(){}

		void set(float,float,float);
};

class TOY_API_CANVAS Uniform4f : public UniformBase
{
	public:

		Uniform4f(std::shared_ptr<Program> ptr,std::string name):UniformBase(ptr,name){}
		~Uniform4f(){}

		void set(float,float,float,float);
};

}}
