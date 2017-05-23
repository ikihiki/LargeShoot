#pragma once

#include <cstdint>
#include "PropLike.h"
#include "TypeId.h"

namespace LargeShoot
{
	class Id
	{
		uint64_t _id;
	public:
		constexpr Id(uint8_t computerNo, uint8_t threadNo, TypeId objectType, uint32_t timestamp);
		PROPLIKE_RCECNE_WCENE(uint8_t, ComputerNo)
		PROPLIKE_RCECNE_WCENE(uint8_t, ThreadNo)
		PROPLIKE_RCECNE_WCENE(TypeId, ObjectType)
		PROPLIKE_RCECNE_WCENE(uint32_t, Timestamp)
	};

	constexpr Id::Id(uint8_t computerNo, uint8_t threadNo, TypeId objectType, uint32_t timestamp)
		:_id(static_cast<uint64_t>(computerNo) << 56 | static_cast<uint64_t>(threadNo) << 48 | static_cast<uint64_t>(objectType.typeId) << 32 | timestamp)
	{

	}

	constexpr uint8_t Id::ComputerNo() const noexcept
	{
		return _id >> 56;
	}

	constexpr uint8_t Id::ComputerNo(uint8_t value) noexcept
	{
		_id = _id & 0x00FFFFFFFFFFFFFF | static_cast<uint64_t>(value) << 56;
		return value;
	}

	constexpr uint8_t Id::ThreadNo() const noexcept
	{
		return (_id & 0x00FF000000000000) >> 48;
	}

	constexpr uint8_t Id::ThreadNo(uint8_t value) noexcept
	{
		_id = _id & 0xFF00FFFFFFFFFFFF | static_cast<uint64_t>(value) << 48;
		return value;
	}

	constexpr TypeId Id::ObjectType() const noexcept
	{
		return TypeId((_id & 0x0000FFFF00000000) >> 32);
	}

	constexpr TypeId Id::ObjectType(TypeId value) noexcept
	{
		_id = _id & 0xFFFF0000FFFFFFFF | static_cast<uint64_t>(value.typeId) << 32;
		return value;
	}

	constexpr uint32_t Id::Timestamp() const noexcept
	{
		return _id & 0x00000000FFFFFFFF;
	}

	constexpr uint32_t Id::Timestamp(uint32_t value) noexcept
	{
		_id = _id & 0xFFFFFFFF00000000 | static_cast<uint64_t>(value);
		return value;
	}

}