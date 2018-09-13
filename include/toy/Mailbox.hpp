
#pragma once

#include <cstdint>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "toy/Exception.hpp"

namespace toy{

template<typename T>
class Mailbox
{
	public:

		Mailbox(){}
		~Mailbox(){}

		bool empty() const
		{
			std::lock_guard<std::mutex>   guard(_mutex);
			return _queue.empty();
		}

		void clear()
		{
			std::lock_guard<std::mutex>   guard(_mutex);
		//	_queue.swap(std::queue<T>());    // Which one better?
			std::queue<T>().swap(_queue);    // Which one better?
		}

		/*
		 * To enqueue a element.
		 * It's a non-blocking method!
		 */
		void send(T t)
		{
			std::lock_guard<std::mutex>   guard(_mutex);
			_queue.push(t);
			_condi.notify_one();
		}

		/*
		 * To dequeue a element, if queue isn't empty.
		 * It's a non-blocking method!
		 */
		bool peek(T *t)
		{
			std::lock_guard<std::mutex>   guard(_mutex);

			if ( _queue.empty() )
			{
				return false;
			}

			*t = _queue.front();
			_queue.pop();

			return true;
		}

		/*
		 * To dequeue a element.
		 * It's a blocking method!
		 */
		T read()
		{
			std::unique_lock<std::mutex>   guard(_mutex);

			while ( _queue.empty() )
			{
				_condi.wait(guard);
			}

			T   result = _queue.front();
			_queue.pop();

			return result;
		}

		bool peek(T *t,float sec)
		{
			std::unique_lock<std::mutex>   guard(_mutex);

			if ( _queue.empty() && sec!=float(0) )
			{
				if ( sec<float(0) )
				{
					throw toy::Exception(TOY_MARK);
				}
				else if ( sec<float(4294967) )
				{
					_condi.wait(guard,std::chrono::duration<uint32_t,std::ratio<1,1000>>(static_cast<uint32_t>(sec*float(1000))));
				}
				else
				{
					// 4294967 seconds is over than 49 days. Why waiting so long?
					throw toy::Exception(TOY_MARK);
				}
			}

			if ( _queue.empty() )
			{
				return false;
			}

			*t = _queue.front();
			_queue.pop();

			return true;
		}

	private:

		std::queue<T>             _queue;
		mutable std::mutex        _mutex;
		std::condition_variable   _condi;
};

}
