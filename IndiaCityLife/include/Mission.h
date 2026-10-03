#pragma once
#include "Types.h"

class MissionSystem {
public:
    Mission current;
    bool started = false;

    void Start();
    void Update(Vector3 playerPos, float& money);
    void DrawHUD() const;
};
