#include "Traffic.h"
#include <cmath>

void TrafficSystem::Create() {

    cars.clear();
    lights.clear();

    for (int i = 0; i < 8; i++) {

        Vehicle car;

        if (i % 2 == 0) {

            car.position = {
                (float)(-70 + i * 18),
                0.75f,
                0.0f
            };

            car.yaw = 0.0f;

        } else {

            car.position = {
                0.0f,
                0.75f,
                (float)(-70 + i * 18)
            };

            car.yaw = 1.5708f;
        }

        car.speed = 3.0f + i * 0.4f;

        cars.push_back(car);
    }

    TrafficLight light1;
    light1.position = {0, 2.5f, -8};
    light1.horizontalAxis = true;
    light1.state = TrafficLightState::Red;

    lights.push_back(light1);

    TrafficLight light2;
    light2.position = {8, 2.5f, 0};
    light2.horizontalAxis = false;
    light2.state = TrafficLightState::Green;

    lights.push_back(light2);
}

bool TrafficSystem::ShouldStop(const Vehicle& car) const {

    for (const auto& l : lights) {

        if (
            l.state == TrafficLightState::Red &&
            std::fabs(car.position.x - l.position.x) < 8.0f &&
            std::fabs(car.position.z - l.position.z) < 6.0f
        ) {
            return true;
        }
    }

    return false;
}

void TrafficSystem::Update(float dt) {

    cycle += dt;

    if (cycle >= 6.0f) {

        cycle = 0.0f;

        for (auto& l : lights) {

            if (l.state == TrafficLightState::Red)
                l.state = TrafficLightState::Green;

            else if (l.state == TrafficLightState::Green)
                l.state = TrafficLightState::Yellow;

            else
                l.state = TrafficLightState::Red;
        }
    }

    for (auto& car : cars) {

        car.UpdateTraffic(
            dt,
            ShouldStop(car)
        );
    }
}

void TrafficSystem::Draw() const {

    for (const auto& c : cars) {

        Color body = {
            (unsigned char)GetRandomValue(60, 230),
            (unsigned char)GetRandomValue(60, 230),
            (unsigned char)GetRandomValue(60, 230),
            255
        };

        c.Draw(body);
    }

    for (const auto& l : lights) {

        DrawCylinder(
            l.position,
            0.25f,
            0.25f,
            6.0f,
            8,
            DARKGRAY
        );

        Color lightColor;

        if (l.state == TrafficLightState::Red)
            lightColor = RED;
        else if (l.state == TrafficLightState::Yellow)
            lightColor = YELLOW;
        else
            lightColor = GREEN;

        DrawSphere(
            {
                l.position.x,
                l.position.y + 3.2f,
                l.position.z
            },
            0.55f,
            lightColor
        );
    }
}
