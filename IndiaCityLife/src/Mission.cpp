#include "Mission.h"
#include <cmath>

static float DistanceXZ(Vector3 a, Vector3 b) {
    float dx = a.x - b.x;
    float dz = a.z - b.z;

    return std::sqrt(dx * dx + dz * dz);
}

void MissionSystem::Start() {
    started = true;

    current.title = "Reach the Destination";
    current.objective = "Go to the marked destination";
    current.reward = 1000.0f;
    current.active = true;
    current.completed = false;
}

void MissionSystem::Update(Vector3 playerPos, float& money) {

    if (!started || !current.active || current.completed)
        return;

    Vector3 target = {
        70.0f,
        0.0f,
        -65.0f
    };

    if (DistanceXZ(playerPos, target) < 14.0f) {

        money += current.reward;

        current.completed = true;
        current.active = false;
        started = false;
    }
}

void MissionSystem::DrawHUD() const {

    if (current.completed) {

        DrawText(
            "MISSION COMPLETE! +Rs 1000",
            20,
            100,
            20,
            GREEN
        );

    } else if (current.active) {

        DrawText(
            "MISSION: Reach the destination",
            20,
            100,
            20,
            WHITE
        );
    }
}
