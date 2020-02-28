
namespace toy{
namespace luamodule{
namespace bignum{

class IntegerMaker
{
	public:

		IntegerMaker()
		{
			;
		}

		~IntegerMaker()
		{
			;
		}
};

class IntegerWrapper
{
	public:

		IntegerWrapper()
		{
			;
		}

		IntegerWrapper(lua::Obj<IntegerMaker>,lua::Str str):_integer(str)
		{
			;
		}

		IntegerWrapper(const ::toy::bignum::Int &num):_integer(num)
		{
			;
		}

		void addition(lua::Obj<IntegerWrapper> num)
		{
			_integer += num.ptr()->_integer;
		}

		void subtraction(lua::Obj<IntegerWrapper> num)
		{
			_integer -= num.ptr()->_integer;
		}

		void multiplication(lua::Obj<IntegerWrapper> num)
		{
			_integer *= num.ptr()->_integer;
		}

		void division(lua::Obj<IntegerWrapper> num)
		{
			_integer /= num.ptr()->_integer;
		}

		void modulo(lua::Obj<IntegerWrapper> num)
		{
			_integer %= num.ptr()->_integer;
		}

		lua::Bool equal(lua::Obj<IntegerWrapper> num)
		{
			if ( _integer == num.ptr()->_integer )
			{
				return true;
			}

			return false;
		}

		lua::Bool lessThan(lua::Obj<IntegerWrapper> num)
		{
			if ( _integer < num.ptr()->_integer )
			{
				return true;
			}

			return false;
		}

		lua::Bool lessThanOrEqual(lua::Obj<IntegerWrapper> num)
		{
			if ( _integer > num.ptr()->_integer )
			{
				return false;
			}

			return true;
		}

		void be_negative()
		{
			_integer *= -1;
		}

		void set(lua::Obj<IntegerWrapper> num)
		{
			_integer = num.ptr()->_integer;
		}

		void setString(lua::Str str)
		{
			_integer = str;
		}

		void setInt(lua::Int num)
		{
			_integer = num;
		}

		lua::Str str()
		{
			return _integer.str();
		}

	private:

		::toy::bignum::Int   _integer;
};

static lua::CFunction BindIntegerMake(lua::State<> *lua)
{
	namespace module = ::toy::luamodule::bignum;

	lua->bindMethod( "str",       &module::IntegerWrapper::str );
	lua->bindMethod( "set",       &module::IntegerWrapper::set );
	lua->bindMethod( "set_str",   &module::IntegerWrapper::setString );
	lua->bindMethod( "set_int",   &module::IntegerWrapper::setInt );
	lua->bindMethod( "add",       &module::IntegerWrapper::addition );
	lua->bindMethod( "sub",       &module::IntegerWrapper::subtraction );
	lua->bindMethod( "mul",       &module::IntegerWrapper::multiplication );
	lua->bindMethod( "div",       &module::IntegerWrapper::division );
	lua->bindMethod( "mod",       &module::IntegerWrapper::modulo );
	lua->bindMethod( "eq",        &module::IntegerWrapper::equal );
	lua->bindMethod( "lt",        &module::IntegerWrapper::lessThan );
	lua->bindMethod( "le",        &module::IntegerWrapper::lessThanOrEqual);
	lua->bindMethod( "unm",       &module::IntegerWrapper::be_negative );

	return lua->bindClass2ArgEx<module::IntegerWrapper,lua::Obj<module::IntegerMaker>,lua::Str>();
}

}}}
