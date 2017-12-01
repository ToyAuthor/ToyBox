#include "toy/memory/Manager01.hpp"


static const size_t     TOY_PAGE_SIZE  = 4096;
static const size_t     TOY_POOL_SIZE  = 262144;   // 64 * page size
static const size_t     TOY_BLOCK_SIZE = 255;      // Limit size of Block.


// Memory align by 4096 byte.
static void* align_mask(void *pointer)
{
	return (void*)(((uintptr_t)pointer) & ~0xfff);//0xfff=4096-1
}


using namespace toy;
using namespace memory;


Manager01::BrandNewPool::BrandNewPool(std::vector<void*>* ptr):_pools(ptr),_freePageNumber(0)
{
	memset(_pageList,0,sizeof(uintptr_t)*63);
}

Manager01::BrandNewPool::~BrandNewPool()
{
	;
}

Manager01::Page* Manager01::BrandNewPool::getPage()
{
	/*
	if( Pool is clean )
	{
		Get new pool.
		Initial the each page of the new pool.
	}
	*/
	if (_freePageNumber == 0)
	{
		void    *new_pool = std::malloc(TOY_POOL_SIZE);

		if (!new_pool)
		{
			return nullptr;
		}

		_pools->push_back(new_pool);

		uint8_t   *the_align = (uint8_t *) align_mask( new_pool );

		// Refresh the page list.
		while( _freePageNumber < 63 )
		{
			the_align += TOY_PAGE_SIZE;     // Go to next Page.

			_pageList[_freePageNumber] = (Page*)the_align;
			_pageList[_freePageNumber]->next                 = nullptr;
			_pageList[_freePageNumber]->blocks               = the_align + sizeof(Page);
			_pageList[_freePageNumber]->pool_index           = _pools->size()-1;
			*((uint8_t **)_pageList[_freePageNumber]->blocks)= nullptr;

			_freePageNumber++;
		}
	}
	_freePageNumber--;

	return (_pageList[_freePageNumber]);
}

Manager01::Manager01():_newPool(&_pools),_usedBlockNumber(0)
{
	//_newPool.setPools(&_pools);
	std::memset(_recyclingPages,0,sizeof(uintptr_t)*32);
}

bool Manager01::clean()
{
	// if( Pool exist )
	if(_pools.size()>0)
	{
		if(_usedBlockNumber!=0)
		{
			/*
			_usedBlockNumber>0 : Some one didn't return memory.
			_usedBlockNumber<0 : Manager01 has inside error.
			*/
			toy::Logger<<"toy::memory::Manager01::clean() _usedBlockNumber="<<_usedBlockNumber<<toy::NextLine;
			return false;
		}

		// Release every each pool.
		for(int32_t i=_pools.size()-1;i<0;i--)
		{
			std::free(_pools[i]);
		}
		return true;
	}

	// I forget to handle BrandNewPool here, do it later.

	return true;
}

Manager01::~Manager01()
{
	this->clean();
}

size_t Manager01::size()
{
	return (size_t)(_pools.size()*TOY_POOL_SIZE);
}

Manager01::Page* Manager01::find_page(void *pointer)
{
	Page	*page = (Page*) align_mask( pointer );

	// if( Page's pool index exist )
	if(page->pool_index >= _pools.size())
		return nullptr;

	// if( Page's pool index is OK )
	if(((uintptr_t) pointer - (uintptr_t) _pools[page->pool_index]) >= TOY_POOL_SIZE)
		return nullptr;

	// if( The pool exist )
	if(!_pools[page->pool_index])
		return nullptr;

	return page;
}

void* Manager01::malloc(size_t size)
{
	if( size - 1 > TOY_BLOCK_SIZE )
	{
		return (std::malloc(size ? size : 1));
	}

	/*
	size :  1 -> page_level : 0 -> block_size :  8 byte
	size : 15 -> page_level : 1 -> block_size : 16 byte
	size : 24 -> page_level : 2 -> block_size : 24 byte
	size : 25 -> page_level : 3 -> block_size : 32 byte
	*/
	uint8_t     page_level  = (uint8_t) (size - 1) >> 3;
	uint16_t    block_size  = (page_level + 1) << 3;

	Page*       page        = _recyclingPages[page_level];  // Search for free Page from old data base.

	// if( There is no available Page )
	if( !page )
	{
		page = _newPool.getPage();          // Get Page from the latest Pool.

		if( !page )
		{
			// Maybe computer memory almost full.
			return (std::malloc(size));
		}

		_recyclingPages[page_level] = page;
		page->free_block = (TOY_PAGE_SIZE - sizeof(Page)) / block_size;// Figure out how many free block in this Page.
		page->level = page_level;
	}

	page->free_block--;

	uint8_t*	free_memory = page->blocks;

	/*
	if( This Page still has free block )
	{
		Refresh free block list.
	}
	else
	{
		Remove this Page from "Recycling Pages" group.
	}
	*/
	if( page->free_block )
	{
		uint8_t      *the_next_free_block = *((uint8_t **) free_memory);

		if( the_next_free_block )
		{
			page->blocks = the_next_free_block;
		}
		else
		{
			page->blocks = free_memory + block_size;
			*((uint8_t **) page->blocks) = nullptr;
		}
	}
	else
	{
		_recyclingPages[page_level] = page->next;
	}

	_usedBlockNumber++;

	return free_memory;
}

void* Manager01::realloc(void *pointer, size_t size)
{
	if( pointer==nullptr )
	{
		toy::Oops(TOY_MARK);
		return this->malloc(size);
	}

	if( !size )
	{
		toy::Oops(TOY_MARK);
		this->free(pointer);
		return nullptr;
	}

	Page	*page = find_page(pointer);

	if( page )
	{
		if( size > (size_t) (page->level << 3) )
		{
			uint8_t      *free_memory = (uint8_t*)this->malloc(size);

			if (free_memory)
			{
				std::memcpy( free_memory, pointer, static_cast<size_t>( page->level << 3) );
				this->free(pointer);
				return free_memory;
			}
			else
			{
				return free_memory;
			}
		}
		else
		{
			return pointer;
		}
	}
	else
	{
		// This memory is come form std::malloc().
		return std::realloc(pointer, size);
	}
}

void Manager01::free(void *pointer)
{
	if ( pointer )
	{
		Page	*page = find_page(pointer);

		if ( page )
		{
			/*
			if( The block we went to "free" is come from a full block Page )
			{
				Move this Page to "Recycling Pages" group.
			}
			*/
			if (!page->free_block)
			{
				page->next = _recyclingPages[page->level];
				_recyclingPages[page->level] = page;
			}

			page->free_block++;     // Now we have one more free Block.

			if ( _usedBlockNumber>0 )
			{
				_usedBlockNumber--;
			}
			else
			{
				// The number of release memory is more than the number of allocate memory? It's impossible.
				toy::Oops(TOY_MARK);
			}

			// Add this block to the free block list.
			*((uint8_t**)pointer) = page->blocks;
			page->blocks = (uint8_t*)pointer;
		}
		else
		{
			std::free(pointer);      // This memory is come form std::malloc().
		}
	}
}
