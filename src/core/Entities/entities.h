#pragma once
#include <unordered_map>
#include <stack>
#include "../Engine/engine.h"
#include "EntityManager.h"
#include <bitset>
#include <array>
#include <memory>
#include <queue>


#define MAX_COMPONENT 256

#define $Component

namespace LargeShoot
{

	class $A
	{
		
	};





	class IComponent
	{
		virtual void reset() = 0;
		virtual ~IComponent(){}
	};

	class ComponentHolder
	{
		
	};





	template<typename T>
	class ComponentContainer final : public Object
	{
		std::vector<T> _pool;
		std::stack<T*> _wait;
	public:
		explicit ComponentContainer(const LargeShoot::Id& id);

	private:
		T * getComponent();
		void removeComponent(T *component);
	};

	class Entity final : public Object
	{
		EntityManager *_manager;
	public:
		Entity(const LargeShoot::Id& id)
			: Object(id)
		{
		}

		
	};

	class EntityContainer: public Object
	{
		std::stack<uint32_t> _blankIds;
		std::array<std::unique_ptr<Object>, MAX_COMPONENT> _components;
		std::vector<std::bitset<MAX_COMPONENT>> _componentFlags;

	public:
		Entity createEntity();
		Entity getEntity(LargeShoot::Id id);
		ComponentHolder createComponent(Entity entity);
		ComponentHolder getComponent(Entity entity);
		void removeComponent(Entity entity);
		std::bitset<MAX_COMPONENT> getCOmponentFlags(Entity entity);
		bool hasComponent(Entity entity);
	};


	template <typename T>
	ComponentContainer<T>::ComponentContainer(const LargeShoot::Id& id): Object(id)
	{
	}

	template<typename T>
	inline T * ComponentContainer<T>::getComponent()
	{
		if(!_wait.empty())
		{
			T *component = _wait.back();
			component->reset();
			_wait.pop();
			return component;
		}
		else
		{
			_pool.push_back(T());
			return _pool.back();
		}
	}

	template <typename T>
	void ComponentContainer<T>::removeComponent(T* component)
	{
		_wait.push(component);
	}
}
