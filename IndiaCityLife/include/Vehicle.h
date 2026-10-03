#pragma once
#include "raylib.h"

class Vehicle {
public:
    Vector3 position{0, 0.75f, 8};
    float yaw = 0;
    float speed = 0;
    float fuel = 70;
    float maxFuel = 70;
    float condition = 100;
    bool playerDriving = false;

    void UpdatePlayer(float dt, bool blocked);
    void UpdateTraffic(float dt, bool shouldStop);
    void Draw(Color body = RED) const;
    bool Near(Vector3 p, float distance) const;
};
