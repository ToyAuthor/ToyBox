
#pragma once

#include "toy/file/ArchiverBase.hpp"

namespace toy{
namespace file{

class ArchiverDefaultZip : public ArchiverBase
{
	public:

		ArchiverDefaultZip();
		~ArchiverDefaultZip();

		bool compress(const std::string &input, const std::string &output);
		bool decompress(const std::string &input, const std::string &output);
};

}}
