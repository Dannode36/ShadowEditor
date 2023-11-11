#pragma once
#include <string>
#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define IMGUI_INCLUDE_IMGUI_USER_INL
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "jsonHelpers.h"
#include "ImGuiJson/CityData.h"

#define SOD_VERSION_MAJOR 33
#define SOD_VERSION_MINOR 7
#define DBG_SAVING true

class Application
{
public:
    int Run();
private:
    void Update();
    void Shutdown();
    bool LoadDocument(std::string path);

    void ImGuiToolbar();
    void RenderDocument(bool* isOpen);
    inline void StreetUI(std::vector<Street>& streets);
    inline void DistrictUI(std::vector<District>& districts);
private:
    const char* glsl_version = "I<3Austin";
    GLFWwindow* window;

    std::string filePath{};
    Document doc;
    City city;

    //State
    bool documentLoaded = false;
    bool unsaved_document = true;

    bool showJsonEditorWindow = true;
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
