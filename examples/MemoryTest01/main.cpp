#include <ctime>
#include <iostream>
#include <toy/Standard.hpp>
#include <toy/memory/Manager01.hpp>

static void DoTheTest( std::function<void*(size_t)> malloc_f,
                       std::function<void(void*)>   free_f )
{
	const int            times  = 20000;     // Test how many times?
	const int            number = 3000;      // Allocate how many memory blocks?
	std::vector<void*>   list(number,0);     // To recording every single each address of memory block.

	auto   tick = std::clock();

	for ( int i=1; i<=times; i++ )
	{
		for ( int j=0; j<number; j++ )
		{
			list[j] = malloc_f(std::rand() % 256 + 1);
		}

		for ( int j=0; j<number; j++ )
		{
			free_f(list[j]);
		}
	}

	std::cout<<"Allocate "<<number<<" memory blocks with "<<times<<" times in "<<std::clock()-tick<<" clocks"<<std::endl;
}

static void TestMemoryPool()
{
	std::cout<<"Test with <toy/memory/Manager01.hpp>:"<<std::endl;

	toy::memory::Manager01  pool;

	auto malloc_f = [&pool](size_t n)->void*
	{
		return pool.malloc(n);
	};

	auto free_f = [&pool](void *p)
	{
		pool.free(p);
	};

	DoTheTest( malloc_f, free_f );
}

static void TestStdlib()
{
	std::cout<<"Test with <cstdlib>:"<<std::endl;
	DoTheTest( std::malloc, std::free );
}

int main()
{
	try
	{
		TestMemoryPool();
		TestStdlib();
	}
	catch(std::exception &e)
	{
		toy::Log(e);
	}

	return EXIT_SUCCESS;
}
