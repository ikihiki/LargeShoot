#pragma once
#include <cstdint>
#include "PropLike.h"

namespace LargeShoot
{

	class TypeId
	{
		friend class Id;
		uint16_t typeId;
		explicit constexpr TypeId(uint16_t id);
	public:
		constexpr TypeId(uint8_t vender, uint8_t type);
		PROPLIKE_RCECNE_WCENE(uint8_t, Vender)
		PROPLIKE_RCECNE_WCENE(uint8_t, Type)
		constexpr bool operator==(const TypeId rhs) const;
	};


	constexpr LargeShoot::TypeId::TypeId(uint16_t id)
		:typeId(id)
	{
	}

	constexpr LargeShoot::TypeId::TypeId(uint8_t vender, uint8_t type)
		: typeId(vender << 8 | type)
	{

	}

	constexpr uint8_t LargeShoot::TypeId::Vender() const noexcept
	{
		return typeId >> 8;
	}

	constexpr uint8_t LargeShoot::TypeId::Vender(uint8_t value) noexcept
	{
		typeId = (typeId & 0x00FF) | value << 8;
		return value;
	}

	constexpr uint8_t LargeShoot::TypeId::Type() const noexcept
	{
		return typeId & 0x00FF;
	}

	constexpr uint8_t LargeShoot::TypeId::Type(uint8_t value) noexcept
	{
		typeId = (typeId & 0xFF00) | value;
		return value;
	}

	constexpr bool LargeShoot::TypeId::operator==(const TypeId rhs) const
	{
		return typeId == rhs.typeId;
	}
}