#include "jsonRendering.h"
#include "../Application.h"
#include "imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

//Base Types
inline void jsonDragInt(const char* label, ValuePair<int>& pair) {
	if (ImGui::DragInt(label, &pair.value)) {
		pair.jsonValue->SetInt(pair.value);
	}
}
inline void jsonDragFloat(const char* label, ValuePair<float>& pair) {
	if (ImGui::DragFloat(label, &pair.value)) {
		pair.jsonValue->SetFloat(pair.value);
	}
}
inline void jsonInputText(const char* label, ValuePair<std::string>& pair) {
	if (ImGui::InputText(label, &pair.value)) {
		pair.jsonValue->SetString(pair.value.c_str(), pair.value.length());
	}
}
inline void jsonCheckbox(const char* label, ValuePair<bool>& pair) {
	if (ImGui::Checkbox(label, &pair.value)) {
		pair.jsonValue->SetBool(pair.value);
	}
}

inline void Application::StreetUI(std::vector<Street>& streets) {
	if (!ImGui::CollapsingHeader("Streets"))
		return;

	for (auto& street : streets)
	{
		if (ImGui::BeginChild(street.name.value.c_str())) {
			jsonInputText((street.name.value + "_name").c_str(), street.name);
			jsonDragInt((street.name.value + "_residenceNum").c_str(), street.residenceNumber);
			unsaved_document = true;
		}
		ImGui::EndChild();
	}
}

inline void Application::DistrictUI(std::vector<District>& districts) {
	if (!ImGui::CollapsingHeader("Districts"))
		return;

	for (auto& district : districts)
	{
		if (ImGui::BeginChild("Districts")) {
			jsonInputText((district.name.value + "_name").c_str(), district.name);
			//jsonDragInt((district.name.value + "_residenceNum").c_str(), district.residenceNumber);
			unsaved_document = true;
		}
		ImGui::EndChild();
	}
}

void Application::RenderDocument(bool* p_open) {
	ImGuiWindowFlags window_flags = 0;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;

	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("JSON Editor", p_open, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	DistrictUI(city.districts.value);
	StreetUI(city.streets.value);

	ImGui::End();
}
