
namespace toy{
namespace luamodule{
namespace bignum{

class FloatMaker
{
	public:

		FloatMaker()
		{
			;
		}

		~FloatMaker()
		{
			;
		}
};

class FloatWrapper
{
	public:

		FloatWrapper()
		{
			;
		}

		FloatWrapper(lua::Obj<FloatMaker>,lua::Str str):_number(str)
		{
			;
		}

		FloatWrapper(const ::toy::bignum::Num &num):_number(num)
		{
			;
		}

		void addition(lua::Obj<FloatWrapper> num)
		{
			_number += num.ptr()->_number;
		}

		void subtraction(lua::Obj<FloatWrapper> num)
		{
			_number -= num.ptr()->_number;
		}

		void multiplication(lua::Obj<FloatWrapper> num)
		{
			_number *= num.ptr()->_number;
		}

		void division(lua::Obj<FloatWrapper> num)
		{
			_number /= num.ptr()->_number;
		}

		/* No. Only integer have modulo.
		void modulo(lua::Obj<FloatWrapper> num)
		{
			_number %= num.ptr()->_number;
		}
		*/

		lua::Bool equal(lua::Obj<FloatWrapper> num)
		{
			if ( _number == num.ptr()->_number )
			{
				return true;
			}

			return false;
		}

		lua::Bool lessThan(lua::Obj<FloatWrapper> num)
		{
			if ( _number < num.ptr()->_number )
			{
				return true;
			}

			return false;
		}

		lua::Bool lessThanOrEqual(lua::Obj<FloatWrapper> num)
		{
			if ( _number > num.ptr()->_number )
			{
				return false;
			}

			return true;
		}

		void be_negative()
		{
			_number *= -1;
		}

		void set(lua::Obj<FloatWrapper> num)
		{
			_number = num.ptr()->_number;
		}

		void setString(lua::Str str)
		{
			_number = str;
		}

		void setInt(lua::Int num)
		{
			_number = num;
		}

		void setNum(lua::Num num)
		{
			_number = num;
		}

		lua::Str str()
		{
			return _number.str();
		}

	private:

		::toy::bignum::Num   _number;
};

static lua::CFunction BindFloatMake(lua::State<> *lua)
{
	namespace module = ::toy::luamodule::bignum;

	lua->bindMethod( "str",       &module::FloatWrapper::str );
	lua->bindMethod( "set",       &module::FloatWrapper::set );
	lua->bindMethod( "set_str",   &module::FloatWrapper::setString );
	lua->bindMethod( "set_int",   &module::FloatWrapper::setInt );
	lua->bindMethod( "set_float", &module::FloatWrapper::setNum );
	lua->bindMethod( "add",       &module::FloatWrapper::addition );
	lua->bindMethod( "sub",       &module::FloatWrapper::subtraction );
	lua->bindMethod( "mul",       &module::FloatWrapper::multiplication );
	lua->bindMethod( "div",       &module::FloatWrapper::division );
//	lua->bindMethod( "mod",       &module::FloatWrapper::modulo );
	lua->bindMethod( "eq",        &module::FloatWrapper::equal );
	lua->bindMethod( "lt",        &module::FloatWrapper::lessThan );
	lua->bindMethod( "le",        &module::FloatWrapper::lessThanOrEqual);
	lua->bindMethod( "unm",       &module::FloatWrapper::be_negative );

	return lua->bindClass2ArgEx<module::FloatWrapper,lua::Obj<module::FloatMaker>,lua::Str>();
}

}}}
