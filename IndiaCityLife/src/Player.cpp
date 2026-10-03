#include "Player.h"
#include <cmath>

static float VecLength(Vector3 v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

static Vector3 VecNormalize(Vector3 v) {
    float len = VecLength(v);
    if (len <= 0.0001f) return {0, 0, 0};
    return {v.x / len, v.y / len, v.z / len};
}

static Vector3 VecAdd(Vector3 a, Vector3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

static Vector3 VecScale(Vector3 v, float s) {
    return {v.x * s, v.y * s, v.z * s};
}

void Player::Update(float dt, bool blocked) {
    Vector3 move{0, 0, 0};

    if (IsKeyDown(KEY_W)) move.z -= 1.0f;
    if (IsKeyDown(KEY_S)) move.z += 1.0f;
    if (IsKeyDown(KEY_A)) move.x -= 1.0f;
    if (IsKeyDown(KEY_D)) move.x += 1.0f;

    if (VecLength(move) > 0.01f) {
        move = VecNormalize(move);

        float actual =
            IsKeyDown(KEY_LEFT_SHIFT) ? speed * 1.65f : speed;

        Vector3 next = VecAdd(
            position,
            VecScale(move, actual * dt)
        );

        if (!blocked) {
            position = next;
            facing = move;
        }

        energy -=
            (IsKeyDown(KEY_LEFT_SHIFT) ? 5.0f : 1.5f) * dt;

        if (energy < 0)
            energy = 0;
    }
}

void Player::Draw() const {
    DrawCylinder(
        {position.x, position.y + 0.55f, position.z},
        0.32f,
        0.32f,
        1.1f,
        12,
        BLUE
    );

    DrawSphere(
        {position.x, position.y + 1.25f, position.z},
        0.25f,
        BEIGE
    );
}
