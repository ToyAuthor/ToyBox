
#pragma once

#include <string>
#include <memory>
#include "toy/CompilerConfig.hpp"

namespace toy{
namespace path{

struct _BrowserIteratorPrivate;

class TOY_API _BrowserIterator
{
	public:

		_BrowserIterator(const std::string &pathname);
		virtual ~_BrowserIterator();

		_BrowserIterator(const _BrowserIterator &mykind);

		void operator = (const _BrowserIterator &mykind);

		bool next(std::string*);
		bool next();
		auto get()const ->const std::string &;

	protected:

		std::unique_ptr<_BrowserIteratorPrivate>  _this;
};

struct BrowserPrivate;

class TOY_API Browser
{
	public:

		Browser();
		Browser(const std::string &pathname);
		virtual ~Browser();

	//	void operator = (const Browser &other);
	//	void change(const std::string &pathname);
		auto begin()->_BrowserIterator;

	protected:

		std::unique_ptr<BrowserPrivate>  _this;
};

}}
