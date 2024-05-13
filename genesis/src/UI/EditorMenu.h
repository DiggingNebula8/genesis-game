#pragma once

#include "imgui.h"
#include "rlImGui.h"
#include "rlImGuiColors.h"

class EditorMenu {
public:
    EditorMenu();
    ~EditorMenu();

    void Update();
    void DemoWindow();
    void CubeSettingsWindow();

    Vector3 cubePos = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeScale = { 2.0f, 2.0f, 2.0f };
    Color cubeColor = BLACK;

private:
    bool Quit = false;
    bool ImGuiDemoOpen = false;
    bool ImGuiCubeSettingsOpen = false;
};
