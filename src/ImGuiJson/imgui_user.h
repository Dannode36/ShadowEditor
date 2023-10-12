#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_internal.h"
#include "rapidjson/pointer.h"
namespace ImGui {
	bool DragScalar(const char* label, rapidjson::Value* p_data, float v_speed, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);
	const ImGuiDataType JsonDataGetImType(rapidjson::Value* p_data);
	int JsonDataTypeFormatString(char* buf, int buf_size, ImGuiDataType data_type, const rapidjson::Value* p_data, const char* format);
	static inline ImGuiInputTextFlags InputScalar_DefaultCharsFilter(ImGuiDataType data_type, const char* format);
}