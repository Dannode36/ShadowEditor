#include "jsonRendering.h"
#include "../Application.h"
#include "imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

//Base Types
inline void jsonDragInt(const char* label, ValuePair<int>& pair) {
	ImGui::SetNextItemWidth(100.f);
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
	ImGui::SetNextItemWidth(500.f);
	if (ImGui::InputText(label, &pair.value, ImGuiInputTextFlags_EnterReturnsTrue)) {
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

	int i = 0;
	for (auto& street : streets)
	{
		if (ImGui::TreeNode((street.name.value + "###" + std::to_string(i)).c_str())) {
			ImGui::Text("Name"); ImGui::SameLine();
			jsonInputText(("##street_name_" + std::to_string(i)).c_str(), street.name);

			ImGui::Text("Residence Number"); ImGui::SameLine();
			jsonDragInt(("##street_residenceNum_" + std::to_string(i)).c_str(), street.residenceNumber);

			ImGui::Separator();
			ImGui::TreePop();
		}
		i++;
	}
}

inline void Application::DistrictUI(std::vector<District>& districts) {
	if (!ImGui::CollapsingHeader("Districts"))
		return;

	int i = 0;
	for (auto& district : districts)
	{
		if (ImGui::TreeNode((district.name.value + "###" + std::to_string(i)).c_str())) {
			ImGui::Text("Name"); ImGui::SameLine();
			jsonInputText(("##district_name_" + std::to_string(i)).c_str(), district.name);

			ImGui::Text("Preset"); ImGui::SameLine();
			jsonInputText(("##district_preset_" + std::to_string(i)).c_str(), district.preset);

			ImGui::Separator();
			ImGui::TreePop();
		}
		i++;
	}
}

void Application::RenderDocument(bool* p_open) {
	ImGuiWindowFlags window_flags = 0;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;

	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin(filePath.c_str(), p_open, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	DistrictUI(city.districts.value);
	StreetUI(city.streets.value);

	ImGui::End();
}
