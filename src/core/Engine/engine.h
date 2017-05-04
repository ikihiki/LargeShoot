#pragma once
#include <cstdint>

#define PROPLIKE_R(type,name) type name();
#define PROPLIKE_RNE(type,name) type name() noexcept;

#define PROPLIKE_RNE_WNE(type,name) type name() noexcept; \
							type name(type value) noexcept;

#define PROPLIKE_RC(type,name) type name() const;

#define PROPLIKE_RCNE(type,name) type name() const noexcept;

#define PROPLIKE_RC_W(type,name) type name() const; \
							type name(type value);

#define PROPLIKE_RCNE_W(type,name) type name() const noexcept; \
							type name(type value);

#define PROPLIKE_RCNE_WNE(type,name) type name() const noexcept; \
							type name(type value) noexcept;
namespace LargeShoot
{
	class Id
	{
		uint64_t _id;
	public:
		Id(uint8_t computerNo, uint8_t threadNo, uint16_t objectType,  uint32_t timestamp);
		PROPLIKE_RCNE_WNE(uint8_t,ComputerNo)
		PROPLIKE_RCNE_WNE(uint8_t, ThreadNo)
		PROPLIKE_RCNE_WNE(uint16_t, ObjectType)
		PROPLIKE_RCNE_WNE(uint32_t, Timestamp)
	};


	class IExecutable
	{
		virtual void execute() = 0;
		virtual ~IExecutable(){}
	};
}
