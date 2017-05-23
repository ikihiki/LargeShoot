#pragma once
#include "../Thread/thread.h"

#define MAX_EVENT_TYPE 1000

namespace LargeShoot
{
	class Future
	{
		
	};

	class IEvent
	{
	public:
		static const int eventId = -1;
	};


	class IEventListenerImpl
	{
	public:
		virtual ~IEventListenerImpl() = default;
		PROPLIKE_RCNE_WNE_B(bool, IsListen)
	};

	template<typename T>
	class IEventListener: public IEventListenerImpl
	{
		virtual void listen(T event) = 0;
	};

	class EventManager
	{
		ThreadManager *threadManager_;
		std::array<moodycamel::ConcurrentQueue<Future>, MAX_EVENT_TYPE> futures_;
		std::array<moodycamel::ConcurrentQueue<IEventListenerImpl *>, MAX_EVENT_TYPE> listeners_;

		template<typename T>
		auto sendEvent(T& event) -> typename std::enable_if<std::is_base_of<IEvent, T>::value, Future>::type;



	};

	template<typename T>
	inline auto EventManager::sendEvent(T & event) -> typename std::enable_if<std::is_base_of<IEvent, T>::value, Future>::type
	{
		IEventListenerImpl *listener= nullptr;
		std::vector<Task> tasks;
		while (futures_[0].try_dequeue(listener))
		{
			Task task;
			task.func_ = [listener, event]
			{
				static_cast<IEventListener<T>>(listener).listen(event);
			};
			tasks.push_back(task);
		}


		while(listeners_[0].try_dequeue(listener))
		{
			
		}

		threadManager_->addTasks(tasks.data(), tasks.size());
		return Future();
	}
}
