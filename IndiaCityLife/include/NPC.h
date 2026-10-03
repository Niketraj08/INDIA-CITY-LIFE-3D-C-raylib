#pragma once
#include "raylib.h"
#include <vector>

struct NPC {
    Vector3 position{};
    Vector3 target{};
    float speed = 1.7f;
    Color shirt{50, 120, 210, 255};
    int state = 0;
};

void SpawnNPCs(std::vector<NPC>& npcs, int count);
void UpdateNPCs(std::vector<NPC>& npcs, float dt);
void DrawNPCs(const std::vector<NPC>& npcs);
