#include <cstdint>
#include <mutex>
#include <condition_variable>
#include "toy/Oops.hpp"
#include "toy/thread/RwMutex.hpp"

namespace toy{
namespace thread{

struct RwMutexPrivate
{
	mutable std::mutex        mutex;
	std::condition_variable   readGate;
	std::condition_variable   writeGate;
	uint32_t                  readersCount = 0;
	uint32_t                  writersWaitCount = 0;
	uint32_t                  writersCount = 0;
};

}}

using namespace toy;
using namespace thread;

RwMutex::RwMutex():_this(new RwMutexPrivate)
{
	;
}

RwMutex::~RwMutex()
{
	;
}

void RwMutex::readLock()
{
	std::unique_lock<std::mutex>    guard(_this->mutex);

	for ( ; _this->writersWaitCount>0 || _this->writersCount>0 ; )
	{
		_this->readGate.wait(guard);
	}

	++(_this->readersCount);
}

void RwMutex::readUnlock()
{
	std::unique_lock<std::mutex>    guard(_this->mutex);

	if ( _this->readersCount==0 )
	{
		toy::Oops(TOY_MARK);
		_this->readersCount = 1;
	}

	--(_this->readersCount);

	if ( _this->readersCount==0 && _this->writersWaitCount>0 )
	{
		_this->writeGate.notify_one();
	}
}

void RwMutex::writeLock()
{
	std::unique_lock<std::mutex>    guard(_this->mutex);

	++(_this->writersWaitCount);

	for ( ; _this->readersCount>0 || _this->writersCount>0 ; )
	{
		_this->writeGate.wait(guard);
	}

	--(_this->writersWaitCount);
	++(_this->writersCount);
}

void RwMutex::writeUnlock()
{
	std::unique_lock<std::mutex>    guard(_this->mutex);

	if ( _this->readersCount>1 )
	{
		toy::Oops(TOY_MARK);
	}

	if ( _this->writersCount!=1 )
	{
		toy::Oops(TOY_MARK);
	}

	_this->writersCount = 0;

	if ( _this->writersWaitCount>0 )
	{
		_this->writeGate.notify_one();
	}
	else
	{
		_this->readGate.notify_all();
	}
}
