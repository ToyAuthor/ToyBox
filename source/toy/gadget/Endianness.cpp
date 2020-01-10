#include "toy/Oops.hpp"
#include "toy/gadget/Endianness.hpp"

namespace toy{
namespace gadget{

class EndiannessFlag
{
	public:

		EndiannessFlag()
		{
			uint16_t  num = 1;

			uint8_t* ptr = (uint8_t*)(&num);

			if ( ptr[0]==0 )
			{
				_flag = false;
			}
		}

		~EndiannessFlag()
		{
			;
		}

		bool get()
		{
			return _flag;
		}

	private:

		bool _flag = true;
};

static bool IsLittleEndian()
{
	static EndiannessFlag flag;

	return flag.get();
}

uint16_t LittleEndian(uint16_t input)
{
	if ( IsLittleEndian() )
	{
		return input;
	}
	else
	{
		uint16_t result;
		uint8_t* temp1 = (uint8_t*)(&input);
		uint8_t* temp2 = (uint8_t*)(&result);

		temp2[1] = temp1[0];
		temp2[0] = temp1[1];

		return result;
	}

	toy::Oops(TOY_MARK);

	return 0;
}

int16_t LittleEndian(int16_t input)
{
	if ( IsLittleEndian() )
	{
		return input;
	}
	else
	{
		int16_t result;
		uint8_t* temp1 = (uint8_t*)(&input);
		uint8_t* temp2 = (uint8_t*)(&result);

		temp2[1] = temp1[0];
		temp2[0] = temp1[1];

		return result;
	}

	toy::Oops(TOY_MARK);

	return 0;
}

uint32_t LittleEndian(uint32_t input)
{
	if ( IsLittleEndian() )
	{
		return input;
	}
	else
	{
		uint32_t result;
		uint8_t* temp1 = (uint8_t*)(&input);
		uint8_t* temp2 = (uint8_t*)(&result);

		temp2[3] = temp1[0];
		temp2[2] = temp1[1];
		temp2[1] = temp1[2];
		temp2[0] = temp1[3];

		return result;
	}

	toy::Oops(TOY_MARK);

	return 0;
}

uint64_t LittleEndian(uint64_t input)
{
	if ( IsLittleEndian() )
	{
		return input;
	}
	else
	{
		uint64_t result;
		uint8_t* temp1 = (uint8_t*)(&input);
		uint8_t* temp2 = (uint8_t*)(&result);

		temp2[7] = temp1[0];
		temp2[6] = temp1[1];
		temp2[5] = temp1[2];
		temp2[4] = temp1[3];
		temp2[3] = temp1[4];
		temp2[2] = temp1[5];
		temp2[1] = temp1[6];
		temp2[0] = temp1[7];

		return result;
	}

	toy::Oops(TOY_MARK);

	return 0;
}

uint16_t BigEndian(uint16_t input)
{
	if ( IsLittleEndian() )
	{
		uint16_t result;
		uint8_t* temp1 = (uint8_t*)(&input);
		uint8_t* temp2 = (uint8_t*)(&result);

		temp2[1] = temp1[0];
		temp2[0] = temp1[1];

		return result;
	}
	else
	{
		return input;
	}

	toy::Oops(TOY_MARK);

	return 0;
}

uint32_t BigEndian(uint32_t input)
{
	if ( IsLittleEndian() )
	{
		uint32_t result;
		uint8_t* temp1 = (uint8_t*)(&input);
		uint8_t* temp2 = (uint8_t*)(&result);

		temp2[3] = temp1[0];
		temp2[2] = temp1[1];
		temp2[1] = temp1[2];
		temp2[0] = temp1[3];

		return result;
	}
	else
	{
		return input;
	}

	toy::Oops(TOY_MARK);

	return 0;
}


uint64_t BigEndian(uint64_t input)
{
	if ( IsLittleEndian() )
	{
		uint64_t result;
		uint8_t* temp1 = (uint8_t*)(&input);
		uint8_t* temp2 = (uint8_t*)(&result);

		temp2[7] = temp1[0];
		temp2[6] = temp1[1];
		temp2[5] = temp1[2];
		temp2[4] = temp1[3];
		temp2[3] = temp1[4];
		temp2[2] = temp1[5];
		temp2[1] = temp1[6];
		temp2[0] = temp1[7];

		return result;
	}
	else
	{
		return input;
	}

	toy::Oops(TOY_MARK);

	return 0;
}

void LittleEndian(int16_t *input)
{
	*input = LittleEndian(*input);
}

void LittleEndian(uint16_t *input)
{
	*input = LittleEndian(*input);
}

void LittleEndian(uint32_t *input)
{
	*input = LittleEndian(*input);
}

void LittleEndian(uint64_t *input)
{
	*input = LittleEndian(*input);
}

void BigEndian(uint16_t *input)
{
	*input = BigEndian(*input);
}

void BigEndian(uint32_t *input)
{
	*input = BigEndian(*input);
}

void BigEndian(uint64_t *input)
{
	*input = BigEndian(*input);
}

void LittleEndianToCorrect(int16_t *input)
{
	#pragma pack(push,1)    // Not sure have to do this

	if ( false==IsLittleEndian() )
	{
		auto ptr = reinterpret_cast<uint8_t*>(input);

		uint8_t temp = ptr[0];
		ptr[0] = ptr[1];
		ptr[1] = temp;
	}

	#pragma pack(pop)
}

}}
