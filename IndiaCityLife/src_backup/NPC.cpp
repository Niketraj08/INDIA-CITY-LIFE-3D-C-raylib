#include "NPC.h"
#include <cstdlib>
#include <cmath>

static float rf(float a, float b) {
    return a + (float)GetRandomValue(0,10000)/10000.0f*(b-a);
}

void SpawnNPCs(std::vector<NPC>& npcs, int count) {
    npcs.clear();
    for (int i=0;i<count;i++) {
        NPC n;
        n.position = {rf(-100,100),1.0f,rf(-100,100)};
        n.target = {rf(-100,100),1.0f,rf(-100,100)};
        n.speed = rf(1.0f,2.4f);
        n.shirt = {(unsigned char)GetRandomValue(40,240),
                   (unsigned char)GetRandomValue(40,240),
                   (unsigned char)GetRandomValue(40,240),255};
        npcs.push_back(n);
    }
}

void UpdateNPCs(std::vector<NPC>& npcs, float dt) {
    for (auto& n : npcs) {
        Vector3 d = Vector3Subtract(n.target,n.position);
        if (Vector3Length(d) < 1.8f) {
            n.target = {rf(-105,105),1.0f,rf(-105,105)};
            continue;
        }
        d = Vector3Normalize(d);
        n.position = Vector3Add(n.position, Vector3Scale(d,n.speed*dt));
    }
}

void DrawNPCs(const std::vector<NPC>& npcs) {
    for (const auto& n : npcs) {
        DrawCylinder({n.position.x,n.position.y+0.5f,n.position.z},0.25f,1.0f,10,n.shirt);
        DrawSphere({n.position.x,n.position.y+1.15f,n.position.z},0.23f,BEIGE);
    }
}
