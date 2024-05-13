// Raylib
#include "raylib.h"
#include "raymath.h"

// Imgui
#include "imgui.h"
#include "rlImGui.h"
#include "rlImGuiColors.h"

// Genesis stuff
#include "Mechanics/FreeLookCamera.h"
#include "UI/GameMenu.h"

int main() {

	// Initialization
//--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Free Look Camera");
    SetTargetFPS(60);

    FreeLookCamera camera;
    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    GameMenu gameMenu;

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

        gameMenu.Update();
        gameMenu.DemoWindow();

        camera.BeginMode();


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
