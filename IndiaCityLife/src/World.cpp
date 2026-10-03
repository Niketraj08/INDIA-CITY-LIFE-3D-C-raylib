#include "World.h"
#include <cmath>

static float DistanceXZ(Vector3 a, Vector3 b) {
    float dx = a.x - b.x;
    float dz = a.z - b.z;

    return std::sqrt(dx * dx + dz * dz);
}

void World::Create() {
    buildings.clear();
    roads.clear();

    for (int x = -90; x <= 90; x += 18) {
        for (int z = -90; z <= 90; z += 18) {

            if (std::abs(x) < 25 && std::abs(z) < 25)
                continue;

            Building b;

            b.position = {
                (float)x + 4.0f,
                0.0f,
                (float)z + 4.0f
            };

            b.size = {
                8.0f,
                (float)(8 + std::abs((x + z) % 18)),
                8.0f
            };

            buildings.push_back(b);
        }
    }

    for (int r = -100; r <= 100; r += 8) {
        roads.push_back({0, 0, (float)r});
        roads.push_back({(float)r, 0, 0});
    }
}

bool World::Collides(Vector3 p, float radius) const {
    for (const auto& b : buildings) {

        float minX =
            b.position.x - b.size.x / 2.0f - radius;

        float maxX =
            b.position.x + b.size.x / 2.0f + radius;

        float minZ =
            b.position.z - b.size.z / 2.0f - radius;

        float maxZ =
            b.position.z + b.size.z / 2.0f + radius;

        if (p.x >= minX &&
            p.x <= maxX &&
            p.z >= minZ &&
            p.z <= maxZ) {
            return true;
        }
    }

    return false;
}

void World::Draw() const {
    DrawPlane(
        {0, 0, 0},
        {240, 240},
        DARKGREEN
    );

    for (int r = -100; r <= 100; r += 8) {

        DrawCube(
            {0, -0.08f, (float)r},
            240.0f,
            0.16f,
            8.0f,
            DARKGRAY
        );

        DrawCube(
            {(float)r, -0.08f, 0},
            8.0f,
            0.16f,
            240.0f,
            DARKGRAY
        );
    }

    for (const auto& b : buildings) {

        DrawCube(
            b.position,
            b.size.x,
            b.size.y,
            b.size.z,
            GRAY
        );

        DrawCube(
            {
                b.position.x,
                b.position.y + b.size.y / 2.0f + 0.3f,
                b.position.z
            },
            b.size.x + 0.4f,
            0.35f,
            b.size.z + 0.4f,
            DARKGRAY
        );

        for (
            float x = -b.size.x / 2.0f + 1.0f;
            x < b.size.x / 2.0f;
            x += 2.0f
        ) {
            DrawCube(
                {
                    b.position.x + x,
                    2.0f,
                    b.position.z - b.size.z / 2.0f - 0.03f
                },
                1.0f,
                1.1f,
                0.05f,
                SKYBLUE
            );
        }
    }
}

const Building* World::NearbyBuilding(
    Vector3 p,
    float radius
) const {
    for (const auto& b : buildings) {

        if (DistanceXZ(
                {p.x, 0, p.z},
                {b.position.x, 0, b.position.z}
            ) < radius) {

            return &b;
        }
    }

    return nullptr;
}
