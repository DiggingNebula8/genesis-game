#include "EditorMenu.h"

EditorMenu::EditorMenu() {
}

EditorMenu::~EditorMenu() {
}

void EditorMenu::Update() {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                Quit = true;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")) {
            ImGui::MenuItem("ImGui Demo", nullptr, &ImGuiDemoOpen);
            ImGui::MenuItem("Cube Settings Window", nullptr, &ImGuiCubeSettingsOpen);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    ImGui::PopStyleVar();
}

void EditorMenu::DemoWindow() {
    if (ImGuiDemoOpen) {
        ImGui::ShowDemoWindow(&ImGuiDemoOpen);
    }
}

void EditorMenu::CubeSettingsWindow() {
    if (ImGuiCubeSettingsOpen) {
        ImGui::Begin("Cube Settings");

        ImGui::DragFloat3("Position", (float*)&cubePos);

        ImGui::DragFloat3("Scale", (float*)&cubeScale);

        // Convert your Color type to float array
        float color[4] = { cubeColor.r / 255.0f, cubeColor.g / 255.0f, cubeColor.b / 255.0f, cubeColor.a / 255.0f };

        // Call ImGui::ColorEdit4 with the float array
        if (ImGui::ColorEdit4("Color", color)) {
            // Update cubeColor if the color was edited
            cubeColor.r = (unsigned char)(color[0] * 255);
            cubeColor.g = (unsigned char)(color[1] * 255);
            cubeColor.b = (unsigned char)(color[2] * 255);
            cubeColor.a = (unsigned char)(color[3] * 255);
        }

        ImGui::End();
    }
}
