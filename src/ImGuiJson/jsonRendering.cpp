#include "jsonRendering.h"
#include "../Application.h"
#include <string>
#include "imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

//Base Types
inline void jsonDragInt(const char* label, ValuePair<int>& pair) {
	if (ImGui::DragInt(label, &pair.value)) {
		pair.jsonValue->SetInt(pair.value);
	}
}

void jsonDragFloat(const char* label, rapidjson::Value* jsonValue, float* imguiValue) {
	if (ImGui::DragFloat(label, imguiValue)) {
		jsonValue->SetFloat(*imguiValue);
	}
}
void jsonInputText(const char* label, ValuePair<std::string>& pair) {
	if (ImGui::InputText(label, &pair.value)) {
		pair.jsonValue->SetString(pair.value.c_str(), pair.value.length());
	}
}
void jsonCheckbox(const char* label, rapidjson::Value* jsonValue, bool* v) {
	if (ImGui::Checkbox(label, v)) {
		jsonValue->SetBool(v);
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

void StreetUI(Street& street) {
	jsonInputText((street.name.value + "_name").c_str(), street.name);
	jsonDragInt((street.name.value + "_residenceNum").c_str(), street.residenceNumber);
}

void Application::RenderDocument() {
	if (ImGui::BeginChild("Streets")) {
		for (auto& street : city.streets.value)
		{
			StreetUI(street);
		}
	}
	ImGui::EndChild();
}
