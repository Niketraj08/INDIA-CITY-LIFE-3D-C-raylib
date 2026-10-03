#pragma once
#include "raylib.h"

class Player {
public:
    Vector3 position{0, 1.0f, 18};
    Vector3 facing{0, 0, -1};
    int health = 100;
    int hunger = 100;
    int energy = 100;
    float money = 5000;
    float speed = 6.0f;

    void Update(float dt, bool blocked);
    void Draw() const;
    void ConsumeTime(float minutes);
};
