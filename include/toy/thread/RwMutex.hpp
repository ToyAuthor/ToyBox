
#pragma once

#include <memory>
#include "toy/thread/Export.hpp"

namespace toy{
namespace thread{

struct RwMutexPrivate;

// Multiple readers, single writer lock.(Read-Write Mutex)
class TOY_API_THREAD RwMutex
{
	public:

		RwMutex();
		~RwMutex();

		void lockShared();
		void unlockShared();
		void lock();
		void unlock();

	private:

		std::unique_ptr<RwMutexPrivate>    _this;

};

class ReadLockGuard
{
	public:

		ReadLockGuard(::toy::thread::RwMutex &mute):_mutex(mute)
		{
			_mutex.lockShared();
		}

		~ReadLockGuard()
		{
			_mutex.unlockShared();
		}

	private:

		::toy::thread::RwMutex     &_mutex;
};

class WriteLockGuard
{
	public:

		WriteLockGuard(::toy::thread::RwMutex &mute):_mutex(mute)
		{
			_mutex.lock();
		}

		~WriteLockGuard()
		{
			_mutex.unlock();
		}

	private:

		::toy::thread::RwMutex     &_mutex;
};

}}
