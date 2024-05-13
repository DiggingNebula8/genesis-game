#include "raylib.h"

// Imgui
#include "imgui.h"
#include "rlImGui.h" // Raylib bindings for Imgui

// Genesis stuff
#include "Mechanics/FreeLookCamera.h"

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Free Look Camera");

    SetTargetFPS(60);

    // Camera Stuff, abstracted to it's own class
    FreeLookCamera camera;
    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };

    // Imgui Setup for raylib
    rlImGuiSetup(true);

    while (!WindowShouldClose()) {
        // Updates camera each frame
        camera.Update();

        // Draws the thing every frame
        BeginDrawing();
        rlImGuiBegin(); // UI Draw Begin
        ClearBackground(GRAY);
        camera.BeginMode();

        // show ImGui Content
        bool open = true; // is UI check  
        ImGui::ShowDemoWindow(&open); // draws demo UI

        // Draws the geometry, should be abstracted to it's own funtionality.
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, BLACK);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, DARKGRAY);

        // If G is down, draws a grid
        if (IsKeyDown('G')) {
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
