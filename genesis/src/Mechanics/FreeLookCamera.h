#pragma once

#include "raylib.h"

class FreeLookCamera {
public:
    FreeLookCamera();
    ~FreeLookCamera();

    void Update();
    void BeginMode();
    void EndMode();

    Camera3D GetCamera() const;

private:
    Camera3D camera;
    int cameraMode;

    void Initialize();
};
