
#include <algorithm>
#include "toy/Oops.hpp"
#include "toy/math/IntCommon.hpp"

namespace toy{
namespace math{

int CompareAbsoluteValue(const std::vector<uint8_t> &number1,const std::vector<uint8_t> &number2)
{
	if ( number1.size() > number2.size() )
	{
		return 1;
	}
	if ( number1.size() < number2.size() )
	{
		return -1;
	}

	int size = number1.size();

	for ( int i=size-1 ; i>=0 ; i-- )
	{
		if ( number1[i] > number2[i] )
		{
			return 1;
		}
		else if ( number1[i] < number2[i] )
		{
			return -1;
		}
	}

	return 0;
}

void ArrayAndEqualArray(std::vector<uint8_t> *arrayA,const std::vector<uint8_t> &arrayB,void (*byteAndByte)(uint8_t,uint8_t,uint8_t*,uint8_t*))
{
	SetEnoughSize(arrayA,arrayB.size());

	arrayA->push_back(0);

	uint8_t   temp1 = 0;
	uint8_t   temp2 = 0;
	uint8_t   temp3 = 0;
	uint8_t   temp4 = 0;

	uint32_t  size = arrayB.size();

	for ( uint32_t i=0 ; i<size ; i++ )
	{
		byteAndByte( (*arrayA)[i], arrayB[i], &temp1, &temp2 );
		(*arrayA)[i]    = temp1;

		uint32_t  j = 1;

		do
		{
			byteAndByte( (*arrayA)[i+j], temp2, &temp3, &temp4 );
			(*arrayA)[i+j] = temp3;

			j++;
		}
		while( temp4>0 );
	}
}

void AddNumberToArray(       std::vector<uint8_t>* nbuffer,
                             uint32_t              index,
                             uint32_t              num,
                       const uint8_t               maxvalue )
{
	#if TOY_OPTION_CHECK
		if ( index>nbuffer->size() )
		{
			toy::Oops(TOY_MARK);
		}
	#endif

	if ( num==0 ) return;

	uint32_t   unit = uint32_t(maxvalue)+1;

	uint32_t   temp = (*nbuffer)[index];

	temp += num;

	if ( temp>=unit )
	{
		uint32_t  tempQ = temp / unit;
		temp -= tempQ*unit;

		::toy::math::AddNumberToArray(nbuffer,index+1,tempQ,maxvalue);
	}

	(*nbuffer)[index] = static_cast<uint8_t>(temp);
}

// ArrayA -= ArrayB
static void ArraySubtraction(       std::vector<uint8_t>* arrayA,
                              const std::vector<uint8_t>& arrayB,
                              const uint8_t               maxvalue )
{
	#if TOY_OPTION_CHECK
	{
		if ( arrayA->size()==0 || arrayB.size()==0 )
		{
			toy::Oops(TOY_MARK);
			return;
		}

		if ( arrayA->back()==0 )
		{
			toy::Oops(TOY_MARK);
			CleanZeroEnd(arrayA);
		}

		if ( arrayB.back()==0 )
		{
			toy::Oops(TOY_MARK);
			return;
		}

		auto comp = ::toy::math::CompareAbsoluteValue(arrayB,*arrayA);

		if ( comp>0 )
		{
			toy::Oops(TOY_MARK);
			return;
		}

		if ( comp==0 )
		{
			arrayA->assign(1,0);
			return;
		}
	}
	#endif

	auto  size = arrayB.size();

	for ( decltype(size) i=0 ; i<size ; i++ )
	{
		if ( (*arrayA)[i] < arrayB[i] )
		{
			for ( decltype(size) j=1 ;  ; j++ )
			{
				if ( (*arrayA)[i+j] == 0 )
				{
					(*arrayA)[i+j] = maxvalue;
				}
				else
				{
					(*arrayA)[i+j] -= 1;
					break;
				}
			}

			(*arrayA)[i] = (maxvalue - arrayB[i]) + (*arrayA)[i] + 1;
		}
		else
		{
			(*arrayA)[i] -= arrayB[i];
		}
	}

	CleanZeroEnd(arrayA);
}

static void SimpleArrayMultiplication( const std::vector<uint8_t>& arr,
                                       const uint8_t               num,
                                       const uint8_t               maxvalue,
                                             std::vector<uint8_t>* result )
{
	auto  size = arr.size();

	#if TOY_OPTION_CHECK
	{
		if ( size==0 )
		{
			toy::Oops(TOY_MARK);
			result->assign(1,0);
			return;
		}

		if ( arr.back()==0 )
		{
			toy::Oops(TOY_MARK);
			result->assign(1,0);
			return;
		}

		if ( num==0 )
		{
			toy::Oops(TOY_MARK);
			result->assign(1,0);
			return;
		}
	}
	#endif

	int   number = num;

	result->clear();
	result->resize(size+1,0);

	for ( decltype(size) i = 0 ; i<size ; i++ )
	{
		int   temp = arr[i];
		temp *= number;

		AddNumberToArray(result,i,temp,maxvalue);
	}

	if ( result->back()==0 )
	{
		result->pop_back();
	}
}

static uint8_t SimpleArrayDivide( const std::vector<uint8_t>& divisor,
                                  const std::vector<uint8_t>& dividends,
                                  const uint8_t               maxvalue,
                                        std::vector<uint8_t>* residue )
{
	#if TOY_OPTION_CHECK
		if ( dividends.size()<divisor.size() )
		{
			toy::Oops(TOY_MARK);
			residue->assign(1,0);
			return 0;
		}

		if ( dividends.size()-divisor.size()>1 )
		{
			toy::Oops(TOY_MARK);
			residue->assign(1,0);
			return 0;
		}
	#endif

	(*residue) = dividends;

	std::vector<uint8_t> temp;

	for ( int i=maxvalue ; i>0 ; i-- )
	{
		SimpleArrayMultiplication(divisor,i,maxvalue,&temp);

		if ( ::toy::math::CompareAbsoluteValue(temp,dividends)<1 )
		{
			ArraySubtraction(residue,temp,maxvalue);

			return i;
		}
	}

	toy::Oops(TOY_MARK);

	return 1;
}

void ArrayDivide( const std::vector<uint8_t>& dividends,
                  const std::vector<uint8_t>& divisor,
                        std::vector<uint8_t>* quotient,
                        std::vector<uint8_t>* residue,
                  const uint8_t               maxvalue )
{
	#if TOY_OPTION_CHECK
		if ( divisor.back()==0 )
		{
			toy::Oops(TOY_MARK);
		}

		if ( dividends.back()==0 )
		{
			toy::Oops(TOY_MARK);
		}
	#endif

	{
		auto   compa = CompareAbsoluteValue(dividends,divisor);

		if ( compa<0 )
		{
			quotient->assign(1,0);
			(*residue) = dividends;
			return;
		}

		if ( compa==0 )
		{
			quotient->assign(1,1);
			residue->assign(1,0);
			return;
		}
	}

	const auto   divisorSize = divisor.size();

	auto             undivSize = dividends.size();
	auto             divEnd    = dividends.end();
	decltype(divEnd) divBegin;

	std::vector<uint8_t>  dividendsHead;
	std::vector<uint8_t>  residueTemp(1,0);

	quotient->clear();

	for (;;)
	{
		if ( residueTemp.size()==1 && residueTemp[0]==0 )
		{
			bool findNothing = true;

			while ( undivSize>=divisorSize )
			{
				divBegin = divEnd;
				divEnd   = divBegin - divisorSize;

				undivSize -= divisorSize;
				quotient->insert(quotient->end(),divisorSize-1,0);
				dividendsHead.assign(divEnd,divBegin);

				while ( dividendsHead.back()==0 )
				{
					dividendsHead.pop_back();
				}

				if ( dividendsHead.size()>0 )
				{
					const auto needSize = divisor.size() - dividendsHead.size();

					if ( needSize>undivSize )
					{
						quotient->insert(quotient->end(),undivSize+1,0);
						break;
					}

					if ( needSize>0 )
					{
						divEnd -= needSize;
						undivSize -= needSize;
						quotient->insert(quotient->end(),needSize,0);
						dividendsHead.assign(divEnd,divBegin);
					}

					findNothing = false;
					break;
				}

				quotient->insert(quotient->end(),divEnd,divBegin);
			}

			if ( findNothing )
			{
				break;
			}
		}
		else
		{
			#if TOY_OPTION_CHECK
				if ( residueTemp.size()>divisor.size())
				{
					toy::Oops(TOY_MARK);
				}

				if ( divisor.back()==0 )
				{
					toy::Oops(TOY_MARK);
				}

				if ( residueTemp.back()==0 )
				{
					toy::Oops(TOY_MARK);
				}
			#endif

			#if TOY_OPTION_CHECK_CAREFUL
				if ( ::toy::math::CompareAbsoluteValue(divisor,residueTemp)<1 )
				{
					toy::Oops(TOY_MARK);
				}
			#endif

			auto needSize = divisor.size() - residueTemp.size();

			if ( needSize>0 )
			{
				if ( needSize>undivSize )
				{
					quotient->insert(quotient->end(),undivSize,0);
					break;
				}

				divBegin = divEnd;
				divEnd   = divBegin - needSize;
				undivSize -= needSize;
				quotient->insert(quotient->end(),needSize-1,0);
			}
			else
			{
				divBegin = divEnd;
				divEnd   = divBegin - 1;
				undivSize -= 1;
			}

			dividendsHead.assign(divEnd,divBegin);
			dividendsHead.insert(dividendsHead.end(),residueTemp.begin(),residueTemp.end());
		}

		if ( ::toy::math::CompareAbsoluteValue(divisor,dividendsHead)>0 )
		{
			if ( undivSize==0 )
			{
				quotient->push_back(0);
				residueTemp.swap(dividendsHead);
				break;
			}

			divEnd -= 1;
			undivSize -= 1;
			quotient->push_back(0);
			dividendsHead.assign(divEnd,divBegin);
			dividendsHead.insert(dividendsHead.end(),residueTemp.begin(),residueTemp.end());
		}

		CleanZeroEnd(&dividendsHead);

		quotient->push_back(SimpleArrayDivide(divisor,dividendsHead,maxvalue,&residueTemp));

		if ( undivSize==0 )
		{
			break;
		}
	}

	std::reverse(quotient->begin(), quotient->end());

	CleanZeroEnd(quotient);

	if ( undivSize==0 )
	{
		residue->swap(residueTemp);

		#if TOY_OPTION_CHECK
			if ( residue->back()==0 && residue->size()>1 )
			{
				toy::Oops(TOY_MARK);
			}
		#endif

		return;
	}

	residue->assign( dividends.begin(), dividends.begin()+undivSize );
	residue->insert( residue->end(), residueTemp.begin(),residueTemp.end() );
	CleanZeroEnd(residue);
}

}}
