
#pragma once

#include "toy/Standard.hpp"

#include "toy/canvas/detail/Brush.hpp"
#include "toy/canvas/detail/Code.hpp"
#include "toy/canvas/detail/Program.hpp"
#include "toy/canvas/detail/ModelBuffer.hpp"

#include "toy/canvas/detail/Image.hpp"
#include "toy/canvas/detail/Geometry.hpp"
#include "toy/canvas/detail/Canvas.hpp"

namespace toy{
namespace canvas{

class Factory
{
	public:

		struct Config
		{
			toy::canvas::_detail::Brush*         (*createBrush)() = nullptr;
			toy::canvas::_detail::Code*          (*createCode_01)(toy::Text&,enum toy::Option) = nullptr;
			toy::canvas::_detail::Code*          (*createCode_02)(std::string,enum toy::Option) = nullptr;
			toy::canvas::_detail::Program*       (*createProgram)(std::shared_ptr<toy::canvas::Code>,std::shared_ptr<toy::canvas::Code>) = nullptr;
			toy::canvas::_detail::ModelBuffer*   (*createModelBuffer)() = nullptr;

			toy::canvas::_detail::Image*         (*createImage)(std::shared_ptr<::toy::canvas::Brush>) = nullptr;
			toy::canvas::_detail::Geometry*      (*createGeometry)(std::shared_ptr<::toy::canvas::Brush>) = nullptr;
			toy::canvas::_detail::Canvas*        (*createCanvas)() = nullptr;
		};

		Factory(const struct Factory::Config &config)
		{
			_list = config;
		}

		~Factory(){}

		auto createBrush()->toy::canvas::_detail::Brush*
		{
			return _list.createBrush();
		}

		auto createCanvas()->toy::canvas::_detail::Canvas*
		{
			return _list.createCanvas();
		}

		auto createCode_01(toy::Text &code,enum toy::Option type)->toy::canvas::_detail::Code*
		{
			return _list.createCode_01(code,type);
		}

		auto createCode_02(std::string filename,enum toy::Option type)->toy::canvas::_detail::Code*
		{
			return _list.createCode_02(filename,type);
		}

		auto createGeometry(std::shared_ptr<::toy::canvas::Brush> brush)->toy::canvas::_detail::Geometry*
		{
			return _list.createGeometry(brush);
		}

		auto createImage(std::shared_ptr<::toy::canvas::Brush> brush)->toy::canvas::_detail::Image*
		{
			return _list.createImage(brush);
		}

		auto createModelBuffer()->toy::canvas::_detail::ModelBuffer*
		{
			return _list.createModelBuffer();
		}

		auto createProgram(std::shared_ptr<toy::canvas::Code> vs,std::shared_ptr<toy::canvas::Code> fs)->toy::canvas::_detail::Program*
		{
			return _list.createProgram(vs,fs);
		}

	private:

		struct Config    _list;
};

extern bool CreateFactory(enum toy::Option version,toy::canvas::Factory **factory);

}}
