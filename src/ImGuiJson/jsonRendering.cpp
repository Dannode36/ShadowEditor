#include "jsonRendering.h"
#include "imgui.h"
#include "rapidjson/pointer.h"

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

void jsonInputText(const char* label, rapidjson::Value* jsonValue, char* imguiValue) {
	if (ImGui::InputText(label, imguiValue, strlen(imguiValue))) {
		jsonValue->SetString(imguiValue, strlen(imguiValue));
	}
}
