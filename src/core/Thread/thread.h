#pragma once
#include <vector>
#include <memory>
#include "../Engine/engine.h"
#include <concurrentqueue.h>
#include <mutex>

namespace LargeShoot
{

	class IExecutable
	{
	public:
		virtual void execute() = 0;
		virtual ~IExecutable() {}
	};

	class Task
	{
	public:
		std::function<void(void)> func_;
	};

	class Thread : public Object, public IRegisterbleType<Thread>
	{
	public:
		static const uint8_t Vender = 0;
		static const uint8_t Type = 10;

		std::atomic_int64_t pendingTasks = 0;
		moodycamel::ConcurrentQueue<Task> tasks_;
		std::thread thread_;
		std::unique_lock<std::mutex> mutex_;
		std::condition_variable end_;
		std::atomic_bool isEnd_ = false;


		explicit Thread(const LargeShoot::Id& id)
			: Object(id)
		{
		}

		void startThread()
		{
			thread_ = std::thread([&]()
			{
				Task task;
				while (pendingTasks.load(std::memory_order_acquire) != 0) {
					if (!tasks_.try_dequeue(task)) {
						continue;
					}

					task.func_();

					pendingTasks.fetch_add(-1, std::memory_order_release);

				}
				isEnd_ = true;
				end_.notify_all();
			});
		}

	};


	class ThreadManager : public Object, public IRegisterbleType<ThreadManager>
	{
	public:
		static const uint8_t Vender = 0;
		static const uint8_t Type = 11;

		explicit ThreadManager(const LargeShoot::Id id, int threadNumber);

		static void registerType(TypeRegistory &registory)
		{
			registory.registerType<ThreadManager>();
			registory.registerType<Thread>();
		}


		void addTask(Task task)
		{
			Thread * into = &threads_[0];
			for (int i = 1; i < threads_.size(); ++i)
			{
				if (threads_[i].pendingTasks < into->pendingTasks)
				{
					into = &threads_[i];
				}
			}

			into->tasks_.enqueue(task);
			into->pendingTasks.fetch_add(1, std::memory_order_release);
		}

		void addTasks(Task *tasks, int count)
		{
			Thread * into = &threads_[0];
			for (int i = 1; i < threads_.size(); ++i)
			{
				if (threads_[i].pendingTasks < into->pendingTasks)
				{
					into = &threads_[i];
				}
			}

			into->tasks_.enqueue_bulk(tasks, count);
			into->pendingTasks.fetch_add(count, std::memory_order_release);
		}


		void waitAllthreads()
		{
			for (auto& thread : threads_)
			{
				while (!thread.isEnd_)
				{
					thread.end_.wait(thread.mutex_);
				}
			}
		}
	private:
		std::vector<Thread> threads_;


	};
}
