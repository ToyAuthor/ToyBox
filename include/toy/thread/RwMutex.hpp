
#pragma once

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

		void readLock();
		void readUnlock();
		void writeLock();
		void writeUnlock();

	private:

		std::unique_ptr<RwMutexPrivate>    _this;

};

class ReadLockGuard
{
	public:

		ReadLockGuard(::toy::thread::RwMutex &mute):_mutex(mute)
		{
			_mutex.readLock();
		}

		~ReadLockGuard()
		{
			_mutex.readUnlock();
		}

	private:

		::toy::thread::RwMutex     &_mutex;
};

class WriteLockGuard
{
	public:

		WriteLockGuard(::toy::thread::RwMutex &mute):_mutex(mute)
		{
			_mutex.writeLock();
		}

		~WriteLockGuard()
		{
			_mutex.writeUnlock();
		}

	private:

		::toy::thread::RwMutex     &_mutex;
};

}}
