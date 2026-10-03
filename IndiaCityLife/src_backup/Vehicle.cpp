#include "Vehicle.h"
#include <cmath>

void Vehicle::UpdatePlayer(float dt, bool blocked) {
    float accel = 0;
    if (IsKeyDown(KEY_W)) accel += 15.0f;
    if (IsKeyDown(KEY_S)) accel -= 10.0f;

    speed += accel * dt;
    if (IsKeyDown(KEY_SPACE)) speed *= 0.90f;

    speed *= (1.0f - 0.8f * dt);
    if (speed > 22) speed = 22;
    if (speed < -7) speed = -7;

    if (std::fabs(speed) > 0.2f) {
        float steer = 0;
        if (IsKeyDown(KEY_A)) steer -= 1;
        if (IsKeyDown(KEY_D)) steer += 1;
        yaw += steer * 1.8f * dt * (speed >= 0 ? 1 : -1);

        Vector3 dir{std::sin(yaw), 0, std::cos(yaw)};
        Vector3 next = Vector3Add(position, Vector3Scale(dir, speed * dt));
        if (!blocked) position = next;
        else speed *= -0.25f;
    }

    fuel -= std::fabs(speed) * dt * 0.012f;
    if (fuel < 0) { fuel = 0; speed = 0; }
    condition -= std::fabs(speed) * dt * 0.0015f;
    if (condition < 0) condition = 0;
}

void Vehicle::UpdateTraffic(float dt, bool shouldStop) {
    if (shouldStop) {
        speed *= 0.94f;
    } else {
        speed += 5.0f * dt;
        if (speed > 9.0f) speed = 9.0f;
    }
    position.x += speed * dt;
    if (position.x > 125) position.x = -125;
}

void Vehicle::Draw(Color body) const {
    DrawCube(position, 3.2f, 0.8f, 1.7f, body);
    DrawCube({position.x, position.y + 0.55f, position.z}, 1.6f, 0.65f, 1.3f, SKYBLUE);
    DrawSphere({position.x - 1.1f, position.y - 0.45f, position.z - 0.7f}, 0.32f, BLACK);
    DrawSphere({position.x + 1.1f, position.y - 0.45f, position.z - 0.7f}, 0.32f, BLACK);
}

bool Vehicle::Near(Vector3 p, float distance) const {
    return Vector3Distance(position, p) <= distance;
}
