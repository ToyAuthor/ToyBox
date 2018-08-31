
#include <toy/Standard.hpp>
#include <toy/math/NumberFormat.hpp>

static int main2()
{
	auto report = std::make_shared<toy::math::NumberFormat>("952348124");

	if ( ! report->isGood() )
	{
		toy::Oops(TOY_MARK);
	}
	else
	{
		if ( report->isNegative() )
		{
			toy::Oops(TOY_MARK);
		}
	}

	report = std::make_shared<toy::math::NumberFormat>("0xabg");

	if ( report->isGood() )
	{
		toy::Oops(TOY_MARK);
	}

	report = std::make_shared<toy::math::NumberFormat>("-6335444");

	if ( ! report->isGood() )
	{
		toy::Oops(TOY_MARK);
	}
	else
	{
		if ( ! report->isInteger() )
		{
			toy::Oops(TOY_MARK);
		}

		if ( ! report->isDecimal() )
		{
			toy::Oops(TOY_MARK);
		}

		if (   report->isHexadecimal() )
		{
			toy::Oops(TOY_MARK);
		}

		if ( ! report->isNegative() )
		{
			toy::Oops(TOY_MARK);
		}
	}

	return EXIT_SUCCESS;
}

int main()
{
	int result = EXIT_FAILURE;

	try
	{
		result = main2();
	}
	catch(std::exception &e)
	{
		toy::Log(e);
	}

	if ( result==EXIT_FAILURE )
	{
		toy::Oops(TOY_MARK);
	}

	return result;
}
