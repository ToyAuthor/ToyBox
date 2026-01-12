
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace toy{
namespace math{

template<typename T,typename S>
static inline void SetEnoughSize(std::vector<T> *array,S size)
{
	auto   asize = array->size();

	if ( asize<size )
	{
		size -= asize;

		for ( S i=S(0); i<size ; i++ )
		{
			array->push_back( T(0) );
		}
	}
}

// example:
//     [1,2,3,0,0,0,0,0] -> [1,2,3]
//     [5,0,0,0,0]       -> [5]
//     [0,0,0,0,5]       -> [0,0,0,0,5]
//     [0,0,0,0,0]       -> [0]
//     empty             -> [0]
template<typename T>
static inline void CleanZeroEnd(std::vector<T> *array)
{
	while ( array->back()==T(0) )
	{
		array->pop_back();
	}

	if ( array->size()==0 )
	{
		array->push_back(T(0));
	}
}

// Return value:
//     1 :number1 >  number2
//     -1:number1 <  number2
//     0 :number1 == number2
extern int CompareAbsoluteValue(const std::vector<uint8_t> &number1,const std::vector<uint8_t> &number2);

// ArrayA += ArrayB
extern void ArrayAndEqualArray(       std::vector<uint8_t> *arrayA,
                                const std::vector<uint8_t> &arrayB,
                                void (*byteAndByte)(uint8_t,uint8_t,uint8_t*,uint8_t*) );

extern void ArrayDivide( const std::vector<uint8_t>& dividends,
                         const std::vector<uint8_t>& divisor,
                               std::vector<uint8_t>* quotient,
                               std::vector<uint8_t>* residue,
                               uint8_t               maxvalue );

extern void AddNumberToArray(       std::vector<uint8_t>* nbuffer,
                                    uint32_t              index,
                                    uint32_t              num,
                              const uint8_t               maxvalue );
}}
