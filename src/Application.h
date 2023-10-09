#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <string>
#include "jsonHelpers.h"
#define WIN32_LEAN_AND_MEAN

class Application
{
public:
	int Run();
private:
	void Update();
	void Shutdown();

	void ImGuiToolbar();
private:
	const char* glsl_version = "I<3Austin";
	GLFWwindow* window;

	std::string filePath{};
	Document doc;
	
	//State
	bool documentLoaded = false;

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

