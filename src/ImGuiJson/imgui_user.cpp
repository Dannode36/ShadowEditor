#include "imgui_user.h"

#define IMGUI_DEFINE_MATH_OPERATORS

namespace ImGui {
    const ImGuiDataType JsonDataGetImType(rapidjson::Value* p_data)
    {
        if (p_data->IsInt()) { return ImGuiDataType_S32; }
        else if (p_data->IsFloat()) { return ImGuiDataType_Float; }
        else if (p_data->IsInt64()) { return ImGuiDataType_S64; }
        else if (p_data->IsDouble()) { return ImGuiDataType_Double; }
        else if (p_data->IsUint()) { return ImGuiDataType_U32; }
        else if (p_data->IsUint64()) { return ImGuiDataType_U64; }

        IM_ASSERT(0);
        return 0;
    }

    int JsonDataTypeFormatString(char* buf, int buf_size, ImGuiDataType data_type, const rapidjson::Value* p_data, const char* format)
    {
        if (data_type == ImGuiDataType_S32)
            return ImFormatString(buf, buf_size, format, (const ImU32)p_data->GetInt());
        if (data_type == ImGuiDataType_U32)
            return ImFormatString(buf, buf_size, format, p_data->GetUint());
        if (data_type == ImGuiDataType_S64)
            return ImFormatString(buf, buf_size, format, (const ImU64)p_data->GetInt64());
        if (data_type == ImGuiDataType_U64)
            return ImFormatString(buf, buf_size, format, p_data->GetUint64());
        if (data_type == ImGuiDataType_Float)
            return ImFormatString(buf, buf_size, format, p_data->GetFloat());
        if (data_type == ImGuiDataType_Double)
            return ImFormatString(buf, buf_size, format, p_data->GetDouble());
        /*if (data_type == ImGuiDataType_S8)
            return ImFormatString(buf, buf_size, format, *(const ImS8*)p_data);
        if (data_type == ImGuiDataType_U8)
            return ImFormatString(buf, buf_size, format, *(const ImU8*)p_data);
        if (data_type == ImGuiDataType_S16)
            return ImFormatString(buf, buf_size, format, *(const ImS16*)p_data);
        if (data_type == ImGuiDataType_U16)
            return ImFormatString(buf, buf_size, format, *(const ImU16*)p_data);*/
        IM_ASSERT(0);
        return 0;
    }

    bool ImGui::DataTypeClamp(ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max)
    {
        switch (data_type)
        {
        case ImGuiDataType_S32:    return DataTypeClampT<ImS32 >((ImS32*)p_data, (const ImS32*)p_min, (const ImS32*)p_max);
        case ImGuiDataType_U32:    return DataTypeClampT<ImU32 >((ImU32*)p_data, (const ImU32*)p_min, (const ImU32*)p_max);
        case ImGuiDataType_S64:    return DataTypeClampT<ImS64 >((ImS64*)p_data, (const ImS64*)p_min, (const ImS64*)p_max);
        case ImGuiDataType_U64:    return DataTypeClampT<ImU64 >((ImU64*)p_data, (const ImU64*)p_min, (const ImU64*)p_max);
        case ImGuiDataType_Float:  return DataTypeClampT<float >((float*)p_data, (const float*)p_min, (const float*)p_max);
        case ImGuiDataType_Double: return DataTypeClampT<double>((double*)p_data, (const double*)p_min, (const double*)p_max);
        case ImGuiDataType_COUNT:  break;
        }
        IM_ASSERT(0);
        return false;
    }
    
    bool TempInputScalar(const ImRect& bb, ImGuiID id, const char* label, ImGuiDataType data_type, rapidjson::Value* p_data, const char* format, const void* p_clamp_min, const void* p_clamp_max)
    {
        // FIXME: May need to clarify display behavior if format doesn't contain %.
        // "%d" -> "%d" / "There are %d items" -> "%d" / "items" -> "%d" (fallback). Also see #6405
        const ImGuiDataTypeInfo* type_info = DataTypeGetInfo(data_type);
        char fmt_buf[32];
        char data_buf[32];
        format = ImParseFormatTrimDecorations(format, fmt_buf, IM_ARRAYSIZE(fmt_buf));
        if (format[0] == 0)
            format = type_info->PrintFmt;
        JsonDataTypeFormatString(data_buf, IM_ARRAYSIZE(data_buf), data_type, p_data, format);
        ImStrTrimBlanks(data_buf);

        ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_NoMarkEdited;
        flags |= InputScalar_DefaultCharsFilter(data_type, format);

        bool value_changed = false;
        if (TempInputText(bb, id, label, data_buf, IM_ARRAYSIZE(data_buf), flags))
        {
            // Backup old value
            size_t data_type_size = type_info->Size;
            ImGuiDataTypeTempStorage data_backup;
            memcpy(&data_backup, p_data, data_type_size);

            // Apply new value (or operations) then clamp
            DataTypeApplyFromText(data_buf, data_type, p_data, format);
            if (p_clamp_min || p_clamp_max)
            {
                if (p_clamp_min && p_clamp_max && DataTypeCompare(data_type, p_clamp_min, p_clamp_max) > 0)
                    ImSwap(p_clamp_min, p_clamp_max);
                DataTypeClamp(data_type, p_data, p_clamp_min, p_clamp_max);
            }

            // Only mark as edited if new value is different
            value_changed = memcmp(&data_backup, p_data, data_type_size) != 0;
            if (value_changed)
                MarkItemEdited(id);
        }
        return value_changed;
    }

    bool ImGui::DragBehavior(ImGuiID id, ImGuiDataType data_type, void* p_v, float v_speed, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
    {
        // Read imgui.cpp "API BREAKING CHANGES" section for 1.78 if you hit this assert.
        IM_ASSERT((flags == 1 || (flags & ImGuiSliderFlags_InvalidMask_) == 0) && "Invalid ImGuiSliderFlags flags! Has the 'float power' argument been mistakenly cast to flags? Call function with ImGuiSliderFlags_Logarithmic flags instead.");

        ImGuiContext& g = *GImGui;
        if (g.ActiveId == id)
        {
            // Those are the things we can do easily outside the DragBehaviorT<> template, saves code generation.
            if (g.ActiveIdSource == ImGuiInputSource_Mouse && !g.IO.MouseDown[0])
                ClearActiveID();
            else if ((g.ActiveIdSource == ImGuiInputSource_Keyboard || g.ActiveIdSource == ImGuiInputSource_Gamepad) && g.NavActivatePressedId == id && !g.ActiveIdIsJustActivated)
                ClearActiveID();
        }
        if (g.ActiveId != id)
            return false;
        if ((g.LastItemData.InFlags & ImGuiItemFlags_ReadOnly) || (flags & ImGuiSliderFlags_ReadOnly))
            return false;

        switch (data_type)
        {
        case ImGuiDataType_S32:    return DragBehaviorT<ImS32, ImS32, float >(data_type, (ImS32*)p_v, v_speed, p_min ? *(const ImS32*)p_min : IM_S32_MIN, p_max ? *(const ImS32*)p_max : IM_S32_MAX, format, flags);
        case ImGuiDataType_U32:    return DragBehaviorT<ImU32, ImS32, float >(data_type, (ImU32*)p_v, v_speed, p_min ? *(const ImU32*)p_min : IM_U32_MIN, p_max ? *(const ImU32*)p_max : IM_U32_MAX, format, flags);
        case ImGuiDataType_S64:    return DragBehaviorT<ImS64, ImS64, double>(data_type, (ImS64*)p_v, v_speed, p_min ? *(const ImS64*)p_min : IM_S64_MIN, p_max ? *(const ImS64*)p_max : IM_S64_MAX, format, flags);
        case ImGuiDataType_U64:    return DragBehaviorT<ImU64, ImS64, double>(data_type, (ImU64*)p_v, v_speed, p_min ? *(const ImU64*)p_min : IM_U64_MIN, p_max ? *(const ImU64*)p_max : IM_U64_MAX, format, flags);
        case ImGuiDataType_Float:  return DragBehaviorT<float, float, float >(data_type, (float*)p_v, v_speed, p_min ? *(const float*)p_min : -FLT_MAX, p_max ? *(const float*)p_max : FLT_MAX, format, flags);
        case ImGuiDataType_Double: return DragBehaviorT<double, double, double>(data_type, (double*)p_v, v_speed, p_min ? *(const double*)p_min : -DBL_MAX, p_max ? *(const double*)p_max : DBL_MAX, format, flags);
        case ImGuiDataType_COUNT:  break;
        }
        IM_ASSERT(0);
        return false;
    }

    bool DragScalar(const char* label, rapidjson::Value* p_data, float v_speed, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
    {
        ImGuiDataType data_type = JsonDataGetImType(p_data);
        IM_ASSERT(p_data->IsNumber());

        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const float w = CalcItemWidth();

        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
        const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

        const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
        ItemSize(total_bb, style.FramePadding.y);
        if (!ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
            return false;

        // Default format string when passing NULL
        if (format == NULL)
            format = DataTypeGetInfo(data_type)->PrintFmt;

            const bool hovered = ItemHoverable(frame_bb, id, g.LastItemData.InFlags);
            bool temp_input_is_active = temp_input_allowed && TempInputIsActive(id);
            if (!temp_input_is_active)
            {
                // Tabbing or CTRL-clicking on Drag turns it into an InputText
                const bool input_requested_by_tabbing = temp_input_allowed && (g.LastItemData.StatusFlags & ImGuiItemStatusFlags_FocusedByTabbing) != 0;
                const bool clicked = hovered && IsMouseClicked(0, id);
                const bool double_clicked = (hovered && g.IO.MouseClickedCount[0] == 2 && TestKeyOwner(ImGuiKey_MouseLeft, id));
                const bool make_active = (input_requested_by_tabbing || clicked || double_clicked || g.NavActivateId == id);
                if (make_active && (clicked || double_clicked))
                    SetKeyOwner(ImGuiKey_MouseLeft, id);
                if (make_active && temp_input_allowed)
                    if (input_requested_by_tabbing || (clicked && g.IO.KeyCtrl) || double_clicked || (g.NavActivateId == id && (g.NavActivateFlags & ImGuiActivateFlags_PreferInput)))
                        temp_input_is_active = true;

                // (Optional) simple click (without moving) turns Drag into an InputText
                if (g.IO.ConfigDragClickToInputText && temp_input_allowed && !temp_input_is_active)
                    if (g.ActiveId == id && hovered && g.IO.MouseReleased[0] && !IsMouseDragPastThreshold(0, g.IO.MouseDragThreshold * DRAG_MOUSE_THRESHOLD_FACTOR))
                    {
                        g.NavActivateId = id;
                        g.NavActivateFlags = ImGuiActivateFlags_PreferInput;
                        temp_input_is_active = true;
                    }

                if (make_active && !temp_input_is_active)
                {
                    SetActiveID(id, window);
                    SetFocusID(id, window);
                    FocusWindow(window);
                    g.ActiveIdUsingNavDirMask = (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
                }
            }

            if (temp_input_is_active)
            {
                // Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
                const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0 && (p_min == NULL || p_max == NULL || DataTypeCompare(data_type, p_min, p_max) < 0);
                return TempInputScalar(frame_bb, id, label, data_type, p_data, format, is_clamp_input ? p_min : NULL, is_clamp_input ? p_max : NULL);
            }

            // Draw frame
            const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
            RenderNavHighlight(frame_bb, id);
            RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, style.FrameRounding);

            // Drag behavior
            const bool value_changed = DragBehavior(id, data_type, p_data, v_speed, p_min, p_max, format, flags);
            if (value_changed)
                MarkItemEdited(id);

            // Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
            char value_buf[64];
            const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
            if (g.LogEnabled)
                LogSetNextTextDecoration("{", "}");
            RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

            if (label_size.x > 0.0f)
                RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | (temp_input_allowed ? ImGuiItemStatusFlags_Inputable : 0));
            return value_changed;
    }
}