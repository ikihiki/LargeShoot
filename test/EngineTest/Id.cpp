#include <gtest/gtest.h>
#include "../../src/core/Engine/engine.h"

using namespace LargeShoot;

TEST(Create_Id, ComputerNo)
{
	Id id(10, 0, TypeId(0, 0), 0);
	ASSERT_EQ(10, id.ComputerNo());
}

TEST(Create_Id, ThreadNo)
{
	Id id(0, 10, TypeId(0, 0), 0);
	ASSERT_EQ(10, id.ThreadNo());
}

TEST(Create_Id, ObjectType)
{
	Id id(0, 0, TypeId(1, 10), 0);
	ASSERT_EQ(TypeId(1, 10), id.ObjectType());
}

TEST(Create_Id, Timestamp)
{
	Id id(0, 0, TypeId(0, 0), 10);
	ASSERT_EQ(10, id.Timestamp());
}

TEST(Get_Id ,ComputerNo)
{
	Id id(10, 20, TypeId(0, 30), 40);
	ASSERT_EQ(10, id.ComputerNo());
}

TEST(Get_Id, ThreadNo)
{
	Id id(10, 20, TypeId(0, 30), 40);
	ASSERT_EQ(20, id.ThreadNo());
}

TEST(Get_Id, ObjectType)
{
	Id id(10, 20, TypeId(0, 30), 40);
	ASSERT_EQ(TypeId(0, 30), id.ObjectType());
}

TEST(Ge_Id, Timestamp)
{
	Id id(10, 20, TypeId(0, 30), 40);
	ASSERT_EQ(40, id.Timestamp());
}

TEST(Set_Id, ComputerNo)
{
	Id id(10, 20, TypeId(0, 30), 40);
	id.ComputerNo(0xFF);
	ASSERT_EQ(0xFF, id.ComputerNo());
	ASSERT_EQ(20, id.ThreadNo());
	ASSERT_EQ(TypeId(0, 30), id.ObjectType());
	ASSERT_EQ(40, id.Timestamp());
}

TEST(Set_Id, ThreadNo)
{
	Id id(10, 20, TypeId(0, 30), 40);
	id.ThreadNo(0xFF);
	ASSERT_EQ(10, id.ComputerNo());
	ASSERT_EQ(0xFF, id.ThreadNo());
	ASSERT_EQ(TypeId(0, 30), id.ObjectType());
	ASSERT_EQ(40, id.Timestamp());
}

TEST(Set_Id, ObjectType)
{
	Id id(10, 20, TypeId(0, 30), 40);
	id.ObjectType(TypeId(0xFF, 0xFF));
	ASSERT_EQ(10, id.ComputerNo());
	ASSERT_EQ(20, id.ThreadNo());
	ASSERT_EQ(TypeId(0xFF, 0xFF), id.ObjectType());
	ASSERT_EQ(40, id.Timestamp());
}

TEST(Se_Id, Timestamp)
{
	Id id(10, 20, TypeId(0, 30), 40);
	id.Timestamp(0xFFFFFFFF);
	ASSERT_EQ(10, id.ComputerNo());
	ASSERT_EQ(20, id.ThreadNo());
	ASSERT_EQ(TypeId(0, 30), id.ObjectType());
	ASSERT_EQ(0xFFFFFFFF, id.Timestamp());
}