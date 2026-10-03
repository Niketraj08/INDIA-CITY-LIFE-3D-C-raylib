#pragma once
#include "raylib.h"
#include "Player.h"
#include "Vehicle.h"
#include "World.h"
#include "NPC.h"
#include "Traffic.h"
#include "Weather.h"
#include "Mission.h"

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    Player player;
    Vehicle playerCar;
    World world;
    std::vector<NPC> npcs;
    TrafficSystem traffic;
    WeatherSystem weather;
    MissionSystem missions;

    Camera3D camera{};
    float gameHour = 8.0f;
    bool inVehicle = false;
    bool showMap = true;
    bool showHelp = false;
    bool running = true;
    float eventTimer = 0;

    void Update(float dt);
    void Draw();
    void DrawHUD() const;
    void DrawMinimap() const;
    void HandleInteraction();
    void Save() const;
    void Load();
    void UpdateNeeds(float dt);
    Color SkyColor() const;
};
