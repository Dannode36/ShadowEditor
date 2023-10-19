#pragma once
#include "rapidjson/pointer.h"

template <typename T>
struct ValuePair
{
	T value;
	rapidjson::Value* jsonValue;
};

