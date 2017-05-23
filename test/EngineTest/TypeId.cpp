#include <gtest/gtest.h>
#include "../../src/core/Engine/engine.h"

using namespace LargeShoot;

class TestType:public IRegisterbleType<TestType>
{
public:
	static const uint8_t Vender = 0;
	static const uint8_t Type = 1;
};


TEST(TypeRegistry, registerType)
{
	TypeRegistory registory;
	ASSERT_TRUE(registory.registerType<TestType>());

}
