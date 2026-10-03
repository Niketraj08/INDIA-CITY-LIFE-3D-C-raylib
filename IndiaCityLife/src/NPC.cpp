#include "NPC.h"
#include <cmath>
#include <cstdlib>

static Vector3 Subtract(Vector3 a, Vector3 b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

static Vector3 Add(Vector3 a, Vector3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

static Vector3 Scale(Vector3 v, float s) {
    return {v.x * s, v.y * s, v.z * s};
}

static float Length(Vector3 v) {
    return std::sqrt(
        v.x * v.x +
        v.y * v.y +
        v.z * v.z
    );
}

static Vector3 Normalize(Vector3 v) {
    float len = Length(v);

    if (len < 0.0001f)
        return {0, 0, 0};

    return {
        v.x / len,
        v.y / len,
        v.z / len
    };
}

void SpawnNPCs(std::vector<NPC>& npcs, int count) {
    npcs.clear();

    for (int i = 0; i < count; i++) {
        NPC n;

        n.position = {
            (float)((std::rand() % 180) - 90),
            0.0f,
            (float)((std::rand() % 180) - 90)
        };

        n.target = {
            (float)((std::rand() % 180) - 90),
            0.0f,
            (float)((std::rand() % 180) - 90)
        };

        n.speed = 1.2f + (std::rand() % 10) * 0.1f;

        n.shirt = {
            (unsigned char)(50 + std::rand() % 180),
            (unsigned char)(50 + std::rand() % 180),
            (unsigned char)(50 + std::rand() % 180),
            255
        };

        npcs.push_back(n);
    }
}

void UpdateNPCs(std::vector<NPC>& npcs, float dt) {
    for (auto& n : npcs) {
        Vector3 d = Subtract(n.target, n.position);

        if (Length(d) < 1.8f) {
            n.target = {
                (float)((std::rand() % 180) - 90),
                0.0f,
                (float)((std::rand() % 180) - 90)
            };
            continue;
        }

        d = Normalize(d);

        n.position = Add(
            n.position,
            Scale(d, n.speed * dt)
        );
    }
}

void DrawNPCs(const std::vector<NPC>& npcs) {
    for (const auto& n : npcs) {
        DrawCylinder(
            {n.position.x, n.position.y + 0.5f, n.position.z},
            0.25f,
            0.25f,
            1.0f,
            10,
            n.shirt
        );

        DrawSphere(
            {n.position.x, n.position.y + 1.15f, n.position.z},
            0.22f,
            BEIGE
        );
    }
}
