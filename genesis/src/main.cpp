#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"
#include "rlImGuiColors.h"
#include "Mechanics/FreeLookCamera.h"
#include "UI/EditorMenu.h"

int main() {
    // Initialization
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Free Look Camera");
    SetTargetFPS(60);

    FreeLookCamera camera;
    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeScale = { 2.0f, 2.0f, 2.0f };
    Color cubeColor = BLACK;

    EditorMenu editorMenu;

    // Imgui Setup for raylib
    rlImGuiSetup(true);
    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
    ImGui::GetIO().FontGlobalScale = 1.5;

    while (!WindowShouldClose()) {
        camera.Update();

        // Draws the thing every frame
        BeginDrawing();
        ClearBackground(GRAY);
        rlImGuiBegin(); // UI Draw Begin

        editorMenu.Update();
        editorMenu.DemoWindow();
        editorMenu.CubeSettingsWindow();

        camera.BeginMode();

        cubePosition = editorMenu.cubePos;
        cubeScale = editorMenu.cubeScale;
        cubeColor = editorMenu.cubeColor;
        // Draws the geometry, should be abstracted to it's own functionality.
        DrawCube(cubePosition, cubeScale.x, cubeScale.y, cubeScale.z, cubeColor);

        // If G is down, draws a grid
        if (IsKeyDown('G')) {
            DrawCubeWires(cubePosition, cubeScale.x, cubeScale.y, cubeScale.z, DARKGRAY);
            DrawGrid(100, 0.5f);
        }

        camera.EndMode();

        rlImGuiEnd(); // End UI Draw
        EndDrawing();
    }
    rlImGuiShutdown(); // Clears UI Resources

    CloseWindow();
    return 0;
}
