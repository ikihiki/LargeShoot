#include "stdafx.h"
#include "engine.h"

using namespace LargeShoot;

Id::Id(uint8_t computerNo, uint8_t threadNo, uint16_t objectType, uint32_t timestamp)
	:_id(static_cast<uint64_t>(computerNo) << 56 | static_cast<uint64_t>(threadNo) << 48 | static_cast<uint64_t>(objectType) << 32 | timestamp)
{

}

uint8_t Id::ComputerNo() const noexcept
{
	return _id >> 56;
}

uint8_t Id::ComputerNo(uint8_t value) noexcept
{
	_id = _id & 0x00FFFFFFFFFFFFFF | static_cast<uint64_t>(value) << 56;
	return value;
}

uint8_t Id::ThreadNo() const noexcept
{
	return (_id & 0x00FF000000000000) >> 48;
}

uint8_t Id::ThreadNo(uint8_t value) noexcept
{
	_id = _id & 0xFF00FFFFFFFFFFFF | static_cast<uint64_t>(value) << 48;
	return value;
}

uint16_t Id::ObjectType() const noexcept
{
	return (_id & 0x0000FFFF00000000) >> 32;
}

uint16_t Id::ObjectType(uint16_t value) noexcept
{
	_id = _id & 0xFFFF0000FFFFFFFF | static_cast<uint64_t>(value) << 32;
	return value;
}

uint32_t Id::Timestamp() const noexcept
{
	return _id & 0x00000000FFFFFFFF;
}

uint32_t Id::Timestamp(uint32_t value) noexcept
{
	_id = _id & 0xFFFFFFFF00000000 | static_cast<uint64_t>(value);
	return value;
}
