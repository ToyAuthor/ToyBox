
#pragma once

#include "toy/Standard.hpp"

#include "toy/graph/detail/Brush.hpp"
#include "toy/graph/detail/Code.hpp"
#include "toy/graph/detail/Program.hpp"
#include "toy/graph/detail/ModelBuffer.hpp"

#include "toy/graph/detail/Image.hpp"
#include "toy/graph/detail/Geometry.hpp"

namespace toy{
namespace graph{


class Factory
{
	public:

		struct Config
		{
			toy::graph::_detail::Brush*         (*createBrush)() = nullptr;
			toy::graph::_detail::Code*          (*createCode01)(toy::Text&,enum toy::Option) = nullptr;
			toy::graph::_detail::Code*          (*createCode02)(std::string,enum toy::Option) = nullptr;
			toy::graph::_detail::Program*       (*createProgram)(std::shared_ptr<toy::graph::Code>,std::shared_ptr<toy::graph::Code>) = nullptr;
			toy::graph::_detail::ModelBuffer*   (*createModelBuffer)() = nullptr;

			toy::graph::_detail::Image*         (*createImage)(std::shared_ptr<::toy::graph::Brush>) = nullptr;
			toy::graph::_detail::Geometry*      (*createGeometry)() = nullptr;
		};

		Factory(const struct Factory::Config &config)
		{
			_list = config;
		}

		~Factory(){}

		auto createBrush()->toy::graph::_detail::Brush*
		{
			return _list.createBrush();
		}

		auto createCode01(toy::Text &code,enum toy::Option type)->toy::graph::_detail::Code*
		{
			return _list.createCode01(code,type);
		}

		auto createCode02(std::string filename,enum toy::Option type)->toy::graph::_detail::Code*
		{
			return _list.createCode02(filename,type);
		}

		auto createProgram(std::shared_ptr<toy::graph::Code> vs,std::shared_ptr<toy::graph::Code> fs)->toy::graph::_detail::Program*
		{
			return _list.createProgram(vs,fs);
		}

		auto createModelBuffer()->toy::graph::_detail::ModelBuffer*
		{
			return _list.createModelBuffer();
		}

		auto createImage(std::shared_ptr<::toy::graph::Brush> brush)->toy::graph::_detail::Image*
		{
			return _list.createImage(brush);
		}

		auto createGeometry()->toy::graph::_detail::Geometry*
		{
			return _list.createGeometry();
		}

	private:

		struct Config    _list;
};

extern bool CreateFactory(enum toy::Option version,toy::graph::Factory **factory);


}}
