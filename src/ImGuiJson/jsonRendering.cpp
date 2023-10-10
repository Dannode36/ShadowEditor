#include "jsonRendering.h"
#include <string>
#include "imgui.h"

//Base Types
void jsonDragInt(const char* label, rapidjson::Value* jsonValue, int* imguiValue) {
	if (ImGui::DragInt(label, imguiValue)) {
		jsonValue->SetInt(*imguiValue);
	}
}
void jsonDragFloat(const char* label, rapidjson::Value* jsonValue, float* imguiValue) {
	if (ImGui::DragFloat(label, imguiValue)) {
		jsonValue->SetFloat(*imguiValue);
	}
}
void jsonInputText(const char* label, rapidjson::Value* jsonValue, char* buf) {
	if (ImGui::InputText(label, buf, strlen(buf))) {
		jsonValue->SetString(buf, strlen(buf));
	}
}

//Array Types
void jsonDragIntA(const char* label, rapidjson::Value* jsonValue, int* imguiArray) {
	if (jsonValue->Empty()) { return; }
	assert(jsonValue[0].IsInt());
	for (rapidjson::SizeType i = 0; i < jsonValue->Size(); i++)
	{
		std::string elemLabel(label);
		elemLabel += std::to_string(i);
		jsonDragInt(elemLabel.c_str(), &jsonValue[i], &imguiArray[i]);
	}
}

void jsonDragFloatA(const char* label, rapidjson::Value* jsonValue, float* imguiArray) {
	if (jsonValue->Empty()) { return; }
	assert(jsonValue[0].IsFloat());
	for (rapidjson::SizeType i = 0; i < jsonValue->Size(); i++)
	{
		std::string elemLabel(label);
		elemLabel += std::to_string(i);
		jsonDragFloat(elemLabel.c_str(), &jsonValue[i], &imguiArray[i]);
	}
}

void jsonInputTextA(const char* label, rapidjson::Value* jsonValue, char** imguiArray) {
	if (jsonValue->Empty()) { return; }
	assert(jsonValue[0].IsString());
	for (rapidjson::SizeType i = 0; i < jsonValue->Size(); i++)
	{
		std::string elemLabel(label);
		elemLabel += std::to_string(i);
		jsonInputText(elemLabel.c_str(), &jsonValue[i], imguiArray[i]);
	}
}
