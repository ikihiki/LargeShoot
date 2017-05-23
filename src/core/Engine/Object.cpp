#include "stdafx.h"
#include "engine.h"

using namespace LargeShoot;


Object::Object(LargeShoot::Id id)
	: _id(id)
{
}

Id Object::Id() const noexcept
{
	return _id;
}

Object::~Object()
{
}
