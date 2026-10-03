#include "Player.h"
#include <cmath>

void Player::Update(float dt, bool blocked) {
    Vector3 move{0,0,0};
    if (IsKeyDown(KEY_W)) move.z -= 1;
    if (IsKeyDown(KEY_S)) move.z += 1;
    if (IsKeyDown(KEY_A)) move.x -= 1;
    if (IsKeyDown(KEY_D)) move.x += 1;

    if (Vector3Length(move) > 0.01f) {
        move = Vector3Normalize(move);
        float actual = IsKeyDown(KEY_LEFT_SHIFT) ? speed * 1.65f : speed;
        Vector3 next = Vector3Add(position, Vector3Scale(move, actual * dt));
        if (!blocked) {
            position = next;
            facing = move;
        }
        energy -= (IsKeyDown(KEY_LEFT_SHIFT) ? 5.0f : 1.5f) * dt;
        if (energy < 0) energy = 0;
    }
}

void Player::Draw() const {
    DrawCylinder({position.x, position.y + 0.55f, position.z}, 0.32f, 1.1f, 12, BLUE);
    DrawSphere({position.x, position.y + 1.25f, position.z}, 0.28f, BEIGE);
}

void Player::ConsumeTime(float minutes) {
    hunger -= (int)(minutes / 60.0f * 4.0f);
    energy -= (int)(minutes / 60.0f * 3.0f);
    if (hunger < 0) hunger = 0;
    if (energy < 0) energy = 0;
}
