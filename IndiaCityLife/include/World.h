#pragma once
#include "raylib.h"
#include "Types.h"
#include <vector>

class World {
public:
    std::vector<Building> buildings;
    std::vector<Vector3> roads;

    void Create();
    void Draw() const;
    bool Collides(Vector3 p, float radius = 0.7f) const;
    const Building* NearbyBuilding(Vector3 p, float radius) const;
};
