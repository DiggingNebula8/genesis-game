#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Shaders/Lights.h"

#define GLSL_VERSION 330
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

    // Use absolute paths for debugging
    const char* vertexShaderPath = "src/Shaders/Resources/glsl330/lighting/lighting.vs";
    const char* fragmentShaderPath = "src/Shaders/Resources/glsl330/lighting/lighting.fs";

    // Load shader
    Shader shader = LoadShader(vertexShaderPath, fragmentShaderPath);

    // Check if the shader files were loaded correctly
    if (shader.id == 0) {
        std::cerr << "Failed to load shaders!" << std::endl;
        return -1;
    }

    // Get some required shader locations
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    // NOTE: "matModel" location name is automatically assigned on shader loading, 
    // no need to get the location again if using that uniform name
    // shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(shader, "ambient");

    // Define the ambient light color as a separate array
    Color ambientColor = YELLOW;
    float ambientColorArray[4] = {
   (float)ambientColor.r / 255.0f,
   (float)ambientColor.g / 255.0f,
   (float)ambientColor.b / 255.0f,
   (float)ambientColor.a / 255.0f
    };
    // Set the shader value using the array
    SetShaderValue(shader, ambientLoc, &ambientColorArray, SHADER_UNIFORM_VEC4);

    // Create lights
    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, { -2, 1, -2 }, Vector3Zero(), YELLOW, shader);
    lights[1] = CreateLight(LIGHT_POINT, { 2, 1, 2 }, Vector3Zero(), RED, shader);
    lights[2] = CreateLight(LIGHT_POINT, { -2, 1, 2 }, Vector3Zero(), GREEN, shader);
    lights[3] = CreateLight(LIGHT_POINT, { 2, 1, -2 }, Vector3Zero(), BLUE, shader);

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

        // Update camera position array
        Vector3 camPosition = camera.GetCamera().position;
        float cameraPos[3] = { camPosition.x, camPosition.y, camPosition.z };
        
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        float cubeColorArray[4] = {
           (float)cubeColor.r / 255.0f,
           (float)cubeColor.g / 255.0f,
           (float)cubeColor.b / 255.0f,
           (float)cubeColor.a / 255.0f
        };
        SetShaderValue(shader, GetShaderLocation(shader, "colDiffuse"), cubeColorArray, SHADER_UNIFORM_VEC4);

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }

        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);

        // Draw the scene
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
        BeginShaderMode(shader);
   
        // Draw the geometry
        DrawCube(cubePosition, cubeScale.x, cubeScale.y, cubeScale.z, WHITE);
        EndShaderMode();

        // Draw spheres to show where the lights are
        for (int i = 0; i < MAX_LIGHTS; i++) {
            if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
            else DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
        }

        // If G is down, draw a grid
        if (IsKeyDown(KEY_G)) {
            DrawCubeWires(cubePosition, cubeScale.x, cubeScale.y, cubeScale.z, DARKGRAY);
            DrawGrid(100, 0.5f);
        }

        camera.EndMode();

        rlImGuiEnd(); // End UI Draw
        EndDrawing();
    }

    rlImGuiShutdown(); // Clear UI Resources
    UnloadShader(shader); // Unload shader
    CloseWindow(); // Close window
    return 0;
}
