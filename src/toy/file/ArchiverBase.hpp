
#pragma once

#include <string>

namespace toy{
namespace file{

class ArchiverBase
{
	public:

		ArchiverBase(){}
		virtual ~ArchiverBase(){}

		virtual bool compress(const std::string &input, const std::string &output)=0;
		virtual bool decompress(const std::string &input, const std::string &output)=0;
};

}}
