#pragma once
#include "raylib.h"
#include "Types.h"
#include "Vehicle.h"
#include <vector>

class TrafficSystem {
public:
    std::vector<Vehicle> cars;
    std::vector<TrafficLight> lights;
    float cycle = 0;

    void Create();
    void Update(float dt);
    void Draw() const;
    bool ShouldStop(const Vehicle& car) const;
};
