#pragma once
#include "raylib.h"
#include <string>

enum class BuildingType { House, Shop, Bank, Hospital, Police, Office, Restaurant, Garage };
enum class WeatherType { Sunny, Cloudy, Rain };
enum class TrafficLightState { Red, Yellow, Green };

struct Building {
    Vector3 position{};
    Vector3 size{};
    BuildingType type{};
    Color color{};
    std::string name;
};

struct TrafficLight {
    Vector3 position{};
    bool horizontalAxis = true;
    TrafficLightState state = TrafficLightState::Red;
};

struct Mission {
    std::string title;
    std::string objective;
    float reward = 0;
    bool active = false;
    bool completed = false;
};
