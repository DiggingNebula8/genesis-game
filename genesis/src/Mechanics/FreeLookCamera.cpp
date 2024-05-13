#include "FreeLookCamera.h"

FreeLookCamera::FreeLookCamera() {
    Initialize();
}

FreeLookCamera::~FreeLookCamera() {
    // Cleanup if needed
}

void FreeLookCamera::Initialize() {
    // Initialization of camera properties
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor(); // Limit cursor to relative movement inside the window
}

void FreeLookCamera::Update() {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        UpdateCamera(&camera, CAMERA_FREE); // Pass the mode to the camera update function
    }

    if (IsKeyPressed('Z')) {
        camera.target = { 0.0f, 0.0f, 0.0f }; // Reset target to the origin
    }
}

void FreeLookCamera::BeginMode() {
    BeginMode3D(camera);
}

void FreeLookCamera::EndMode() {
    EndMode3D();
}

Camera3D FreeLookCamera::GetCamera() const {
    return camera;
}
