
#pragma once

#include "toy/file/ArchiverBase.hpp"

namespace toy{
namespace file{

class ArchiverZip : public ArchiverBase
{
	public:

		ArchiverZip();
		~ArchiverZip();

		bool compress(const std::string &input, const std::string &output);
		bool decompress(const std::string &input, const std::string &output);
};

}}
