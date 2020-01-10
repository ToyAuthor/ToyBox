
#pragma once

#include <memory>
#include <string>
#include "toy/archive/Export.hpp"
#include "toy/archive/Config.hpp"

namespace toy{
namespace archive{

struct StreamPrivate;

class TOY_API_ARCHIVE Stream
{
	public:

		Stream();
		Stream(const std::string &name);
		~Stream();

		bool open(const std::string &name);
		auto config() const ->const ::toy::archive::Config&;
		void close();
		bool empty();

	private:

		std::unique_ptr<::toy::archive::StreamPrivate> _this;
};

}}
