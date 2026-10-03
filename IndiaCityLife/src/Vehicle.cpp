#include "Vehicle.h"
#include <cmath>

static Vector3 Add(Vector3 a, Vector3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

static Vector3 Scale(Vector3 v, float s) {
    return {v.x * s, v.y * s, v.z * s};
}

static float Distance(Vector3 a, Vector3 b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void Vehicle::UpdatePlayer(float dt, bool blocked) {
    const float acceleration = 18.0f;
    const float maxSpeed = 18.0f;
    const float steering = 1.8f;

    if (IsKeyDown(KEY_W))
        speed += acceleration * dt;

    if (IsKeyDown(KEY_S))
        speed -= acceleration * dt;

    if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
        speed *= 0.94f;

    if (speed > maxSpeed)
        speed = maxSpeed;

    if (speed < -maxSpeed * 0.35f)
        speed = -maxSpeed * 0.35f;

    if (IsKeyDown(KEY_A))
        yaw -= steering * dt;

    if (IsKeyDown(KEY_D))
        yaw += steering * dt;

    Vector3 direction = {
        std::sin(yaw),
        0.0f,
        std::cos(yaw)
    };

    if (std::fabs(speed) > 0.01f) {
        Vector3 next = Add(
            position,
            Scale(direction, speed * dt)
        );

        if (!blocked)
            position = next;
    }

    fuel -= std::fabs(speed) * dt * 0.003f;

    if (fuel < 0.0f)
        fuel = 0.0f;
}

void Vehicle::UpdateTraffic(float dt, bool shouldStop) {
    if (shouldStop) {
        speed *= 0.90f;
    } else {
        speed += 4.0f * dt;

        if (speed > 8.0f)
            speed = 8.0f;
    }

    Vector3 direction = {
        std::sin(yaw),
        0.0f,
        std::cos(yaw)
    };

    position = Add(
        position,
        Scale(direction, speed * dt)
    );
}

void Vehicle::Draw(Color body) const {
    DrawCube(
        position,
        1.8f,
        0.8f,
        3.4f,
        body
    );

    DrawCube(
        {position.x, position.y + 0.5f, position.z},
        1.35f,
        0.55f,
        1.65f,
        SKYBLUE
    );

    DrawSphere(
        {position.x - 0.65f, position.y - 0.45f, position.z - 1.0f},
        0.28f,
        BLACK
    );

    DrawSphere(
        {position.x + 0.65f, position.y - 0.45f, position.z - 1.0f},
        0.28f,
        BLACK
    );

    DrawSphere(
        {position.x - 0.65f, position.y - 0.45f, position.z + 1.0f},
        0.28f,
        BLACK
    );

    DrawSphere(
        {position.x + 0.65f, position.y - 0.45f, position.z + 1.0f},
        0.28f,
        BLACK
    );
}

bool Vehicle::Near(Vector3 p, float distance) const {
    return Distance(position, p) <= distance;
}
