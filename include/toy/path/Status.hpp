
#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include "toy/CompilerConfig.hpp"

namespace toy{
namespace path{

struct StatusPrivate;

class TOY_API Status
{
	public:

		Status(const std::string &filename);
		Status(const Status &other);
		virtual ~Status();

		void operator = (const Status &other);
		void operator = (const std::string &filename);
		bool exist();
		void remove();
		auto size()->uint64_t;
		auto location()->std::string;
		auto name()->std::string;
		bool isDirectory();
		bool isFile();

	protected:

		std::unique_ptr<StatusPrivate>     _this;
};

TOY_API extern bool IsExist(const std::string &filename);
TOY_API extern bool IsFile(const std::string &filename);
TOY_API extern bool IsFolder(const std::string &filename);
TOY_API extern bool IsEmptyFolder(const std::string &filename);
TOY_API extern uintmax_t Remove(const std::string &filename);
TOY_API extern bool MakeDir(const std::string &filename);
TOY_API extern auto GetFileSize(const std::string &filename)->uint64_t;
TOY_API extern bool OpenFolder(const std::string &filename);

}}
