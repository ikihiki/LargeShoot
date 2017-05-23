#pragma once
#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include "Id.h"
#include "TypeId.h"
#include "TypeRegistory.h"
#include "../Thread/thread.h"
#include "../Entities/EntityManager.h"

namespace LargeShoot
{

	class Object
	{
	protected:
		Id _id;
	public:
		explicit Object(Id id);
		Id Id() const noexcept;
		virtual ~Object();
	};

	class Engine
	{
		std::unique_ptr<ThreadManager> threaadManager_ = nullptr;
		std::unique_ptr<EntityManager> entityManager_ = nullptr;
		std::unique_ptr<TypeRegistory> typeRegistory_ = nullptr;

		void preConfig()
		{
			typeRegistory_ = std::make_unique<TypeRegistory>();
			ThreadManager::registerType(*typeRegistory_);
			threaadManager_ = std::make_unique<LargeShoot::ThreadManager>(Id(0, 0, typeRegistory_->getTypeId<LargeShoot::ThreadManager>(), 0), 4);

		}

		virtual void config(){}

		void postConfig()
		{
			
		}


	protected:
		ThreadManager& ThreadManager() const { return *threaadManager_; }
		EntityManager& EntityManager() const { return *entityManager_; }
		
	public:
		void run()
		{
			preConfig();
			config();
			postConfig();
			ThreadManager().addTask(nullptr);
			threaadManager_->waitAllthreads();
		}
	};

}
