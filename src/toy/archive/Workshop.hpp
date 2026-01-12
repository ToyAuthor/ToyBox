
#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include "toy/Block.hpp"
#include "toy/archive/Config.hpp"
#include "toy/archive/CoreLZ4.hpp"

namespace toy{
namespace archive{

class Workshop
{
	public:

		Workshop();
		~Workshop();

		bool compress(const toy::Block &input,const std::string &output);
		auto decompress(const std::string &input)->std::shared_ptr<toy::Block>;
		bool compress(   const std::string &input,
		                 const std::string &output,
		                 const ::toy::archive::Config&);
		bool decompress( const std::string &input,
		                 const std::string &output,
		                 ::toy::archive::Config *config=nullptr);
		void init();
		void drop();

	private:

		CoreLZ4          _core;
};

}}
