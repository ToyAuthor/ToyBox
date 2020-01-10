
#pragma once

#include <memory>
#include <string>
#include "toy/Block.hpp"
#include "toy/archive/Export.hpp"
#include "toy/archive/Config.hpp"
#include "toy/archive/Stream.hpp"

namespace toy{
namespace archive{
struct ArchiverPrivate;
}

class TOY_API_ARCHIVE Archiver
{
	public:

		Archiver();
		~Archiver();

		bool compress(const toy::Block &input,const std::string &output);
		auto decompress(const std::string &input)->std::shared_ptr<toy::Block>;
		#if TOY_OPTION_ENABLE_BETA_API
		bool compress(   const std::string &input,
		                 const std::string &output,
		                 const ::toy::archive::Config&);
		bool decompress( const std::string &input,
		                 const std::string &output,
		                 ::toy::archive::Config *config=nullptr);
		auto makeStream(const std::string &name) const -> std::shared_ptr<::toy::archive::Stream>;
		auto makeStreamRawPtr(const std::string &name) const -> ::toy::archive::Stream*;
		#endif
		void init();
		void drop();

	private:

		std::unique_ptr<::toy::archive::ArchiverPrivate> _this;
};

}

#if TOY_OPTION_ENABLE_BETA_API
namespace toy{
namespace archive{

TOY_API_ARCHIVE extern void Compress(const std::string &input,const std::string &output);
TOY_API_ARCHIVE extern void Decompress(const std::string &input,const std::string &output);

}}
#endif
