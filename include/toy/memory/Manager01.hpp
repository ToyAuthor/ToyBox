/*
┌-------┬-------------┬-----------┬--------------┬---------┐
│       │Manager01    │Pool       │Page          │Block    │
├-------┼-------------┼-----------┼--------------┼---------┤
│Content│Several Pools│63 Pages   │Several Blocks│         │
├-------┼-------------┼-----------┼--------------┼---------┤
│Size   │Not fixed    │262144 byte│4096 byte     │Not fixed│
└-------┴-------------┴-----------┴--------------┴---------┘
*/

#pragma once

#include "toy/Standard.hpp"
#include "toy/memory/Export.hpp"


namespace toy{
namespace memory{


/*
 * The max size of memory block is 255 byte.
 * If the size is bigger than 255 byte, it will be handled by std::malloc().
 */
class TOY_API_MEMORY Manager01
{
	public:

		Manager01();
		~Manager01();

		void*   malloc(size_t bytes);                   // Same as std::malloc()
		void    free(void *p);                          // Same as std::free()
		void*   realloc( void *p, size_t bytes );       // Same as std::realloc()
	//	bool    fit();                                  // Return unused memory back to OS.
		size_t  size();                                 // Let you know how many memory in pool.
		bool    clean();                                // Release all of memory.

		void*   calloc(size_t number, size_t size)
		{
			return this->malloc(number * size);
		}

	private:

		// A handle of Page.
		struct Page
		{
			Page*     next;
			uint8_t*  blocks;         // A list of blocks.
			uint32_t  pool_index;     // For recording this Page is belong to which Pool.
			uint16_t  free_block;     // For recording how many unused blocks.
			uint8_t   level;          // For recording the size of Block is how many times of 8 byte.
		};

		// To handl the latst Pool this Manager get.
		class BrandNewPool
		{
			public:

				BrandNewPool(std::vector<void*>*);
				~BrandNewPool();

				Page* getPage();     // Find a Page that is free.

			private:

				std::vector<void*>*  _pools;          // Pointer to Manager01::mPools.
				Page*                _pageList[63];   // The content of this new pool.
				uint8_t              _freePageNumber; // To record how many unused Pages.
		};

		Page* find_page(void *p);    // Find out this memory block is belong to which Page.

		Page*               _recyclingPages[32];    // 32 element. 32 level. Each single element has a Page list. Every Page has free block.
		std::vector<void*>  _pools;                 // All of Pools are stored here.
		BrandNewPool        _newPool;
		int32_t             _usedBlockNumber;       // To record how many Blocks has been give to user.

};

}//namespace memory
}//namespace toy
