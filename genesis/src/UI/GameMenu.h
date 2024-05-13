#pragma once

// Imgui
#include "imgui.h"
#include "rlImGui.h"
#include "rlImGuiColors.h"

class GameMenu
{
public:
	GameMenu();
	~GameMenu();

	void Update();
	void DemoWindow();

private:
	bool Quit = false;
	bool ImGuiDemoOpen = false;
};

