#pragma once
#include "raylib.h"
#include "Types.h"

class WeatherSystem {
public:
    WeatherType type = WeatherType::Sunny;
    float timer = 0;

    void Update(float dt);
    Color SkyColor(float hour) const;
    void DrawRain(Vector3 center) const;
};
