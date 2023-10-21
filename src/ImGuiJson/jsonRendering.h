#pragma once
#include "rapidjson/pointer.h"
#include "ValuePair.h"
#include <string>

void jsonDragInt(const char* label, ValuePair<int>& pair);
void jsonDragFloat(const char* label, ValuePair<float>& pair);
void jsonInputText(const char* label, ValuePair<std::string>& pair);
 