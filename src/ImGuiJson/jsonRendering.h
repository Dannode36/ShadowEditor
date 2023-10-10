#pragma once
#include "rapidjson/pointer.h"

void jsonDragInt(const char* label, rapidjson::Value* jsonValue, int* imguiValue);
void jsonDragFloat(const char* label, rapidjson::Value* jsonValue, float* imguiValue);
void jsonInputText(const char* label, rapidjson::Value* jsonValue, char* imguiValue);

void jsonDragIntA(const char* label, rapidjson::Value* jsonValue, int* imguiArray);
void jsonDragFloatA(const char* label, rapidjson::Value* jsonValue, float* imguiArray);
void jsonInputTextA(const char* label, rapidjson::Value* jsonValue, char** imguiArray);
