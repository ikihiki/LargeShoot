#pragma once
#include <cstdint>
#include <typeindex>
#include <unordered_map>
#include "TypeId.h"


namespace LargeShoot
{
	class IRegisterbleTypeImpl
	{
	public:
		static const uint8_t Vender = -1;
		static const uint8_t Type = -1;
	};

	template<typename T>
	class IRegisterbleType : public IRegisterbleTypeImpl
	{
		friend class TypeRegistory;
		static TypeId typeId;
	};

	template<typename T>
	TypeId IRegisterbleType<T>::typeId = TypeId(-1, -1);


	class TypeRegistory
	{
		std::unordered_map<std::type_index, TypeId> types;

	public:
		template<typename T>
		auto registerType() -> typename std::enable_if<std::is_base_of<IRegisterbleType<T>, T>::value, bool>::type;

		template <typename T>  
		auto getTypeId() -> typename std::enable_if<std::is_base_of<IRegisterbleType<T>, T>::value, TypeId>::type;

	};

	template <typename T>
	auto TypeRegistory::registerType() -> typename std::enable_if<std::is_base_of<IRegisterbleType<T>, T>::value, bool>::type
	{
		if (types.find(typeid(T)) != types.end())
		{
			return false;
		}

		if (T::Vender == -1 || T::Type == -1)
		{
			return false;
		}

		TypeId id{ T::Vender,T::Type };

		T::typeId = id;

		types.insert(std::pair<std::type_index, TypeId>(typeid(T), id));
		return true;
	}

	template<typename T>
	inline auto TypeRegistory::getTypeId() -> typename std::enable_if<std::is_base_of<IRegisterbleType<T>, T>::value, TypeId>::type
	{
		return T::typeId;
	}

}
