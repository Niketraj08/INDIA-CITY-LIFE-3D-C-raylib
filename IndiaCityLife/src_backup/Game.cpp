#include "Game.h"
#include <fstream>
#include <cmath>

Game::Game() {
    InitWindow(1600,900,"INDIA CITY LIFE - 3D");
    SetTargetFPS(60);

    world.Create();
    traffic.Create();
    SpawnNPCs(npcs,55);

    camera.position={0,8,14};
    camera.target={0,1,0};
    camera.up={0,1,0};
    camera.fovy=60;
    camera.projection=CAMERA_PERSPECTIVE;

    missions.Start();
}

Game::~Game() {
    CloseWindow();
}

Color Game::SkyColor() const {
    return weather.SkyColor(gameHour);
}

void Game::HandleInteraction() {
    if(!IsKeyPressed(KEY_E)) return;

    if(inVehicle) return;

    if(playerCar.Near(player.position,4.5f)) {
        inVehicle=true;
        playerCar.playerDriving=true;
        player.position=playerCar.position;
        return;
    }

    const Building* b=world.NearbyBuilding(player.position,10);
    if(!b) return;

    switch(b->type) {
        case BuildingType::Bank:
            player.money += 0; // placeholder for future banking UI
            break;
        case BuildingType::Hospital:
            if(player.money>=500) { player.money-=500; player.health=100; }
            break;
        case BuildingType::Restaurant:
        case BuildingType::Shop:
            if(player.money>=100) { player.money-=100; player.hunger+=25; if(player.hunger>100)player.hunger=100; }
            break;
        case BuildingType::Garage:
            playerCar.condition=100;
            break;
        default: break;
    }
}

void Game::UpdateNeeds(float dt) {
    eventTimer += dt;
    if(eventTimer>12) {
        eventTimer=0;
        player.hunger--;
        if(player.hunger<0) player.hunger=0;
        if(player.hunger<15) player.health--;
        if(player.health<0) player.health=0;
    }
}

void Game::Save() const {
    std::ofstream f("savegame.txt");
    f << player.position.x << ' ' << player.position.y << ' ' << player.position.z << '\n';
    f << player.money << ' ' << player.health << ' ' << player.hunger << ' ' << player.energy << '\n';
    f << playerCar.position.x << ' ' << playerCar.position.y << ' ' << playerCar.position.z << '\n';
    f << playerCar.fuel << ' ' << playerCar.condition << '\n';
    f << gameHour << '\n';
}

void Game::Load() {
    std::ifstream f("savegame.txt");
    if(!f) return;
    f >> player.position.x >> player.position.y >> player.position.z;
    f >> player.money >> player.health >> player.hunger >> player.energy;
    f >> playerCar.position.x >> playerCar.position.y >> playerCar.position.z;
    f >> playerCar.fuel >> playerCar.condition;
    f >> gameHour;
}

void Game::Update(float dt) {
    if(IsKeyPressed(KEY_ESCAPE)) running=false;
    if(IsKeyPressed(KEY_M)) showMap=!showMap;
    if(IsKeyPressed(KEY_TAB)) showHelp=!showHelp;
    if(IsKeyPressed(KEY_F) && inVehicle) {
        inVehicle=false;
        playerCar.playerDriving=false;
        player.position=Vector3Add(playerCar.position,{2,0,2});
    }
    if(IsKeyPressed(KEY_F5)) Save();
    if(IsKeyPressed(KEY_F9)) Load();

    if(inVehicle) {
        Vector3 old=playerCar.position;
        playerCar.UpdatePlayer(dt,world.Collides(playerCar.position,1.8f));
        if(world.Collides(playerCar.position,1.8f)) playerCar.position=old;
        player.position=Vector3Add(playerCar.position,{0,0.7f,0});
    } else {
        Vector3 old=player.position;
        player.Update(dt,world.Collides(player.position,0.6f));
        if(world.Collides(player.position,0.6f)) player.position=old;
    }

    traffic.Update(dt);
    UpdateNPCs(npcs,dt);
    weather.Update(dt);

    gameHour += dt*0.045f;
    if(gameHour>=24) gameHour-=24;

    HandleInteraction();
    missions.Update(player.position,player.money);
    UpdateNeeds(dt);

    camera.target=Vector3Add(player.position,{0,1,0});
    camera.position=Vector3Add(player.position,{0,8,14});
}

void Game::DrawHUD() const {
    DrawRectangle(0,0,1600,82,Fade(BLACK,0.72f));
    DrawText(TextFormat("CASH  Rs %.0f",player.money),20,16,22,WHITE);
    DrawText(TextFormat("HP %d",player.health),250,16,22,WHITE);
    DrawText(TextFormat("HUNGER %d",player.hunger),350,16,22,WHITE);
    DrawText(TextFormat("ENERGY %d",player.energy),510,16,22,WHITE);
    DrawText(TextFormat("TIME %02d:%02d",(int)gameHour,(int)((gameHour-(int)gameHour)*60)),690,16,22,WHITE);

    const char* w=weather.type==WeatherType::Sunny?"SUNNY":
                  weather.type==WeatherType::Cloudy?"CLOUDY":"RAIN";
    DrawText(w,900,16,22,WHITE);

    DrawText(inVehicle?"DRIVING":"ON FOOT",1040,16,22,inVehicle?GREEN:YELLOW);
    DrawText("WASD Move | E Enter/Interact | F Exit | F5 Save | F9 Load | M Map",20,50,17,LIGHTGRAY);

    missions.DrawHUD();

    if(showHelp) {
        DrawRectangle(1100,105,450,240,Fade(BLACK,0.82f));
        DrawText("CITY LIFE CONTROLS",1120,122,24,WHITE);
        DrawText("WASD  Walk / Drive",1120,160,19,LIGHTGRAY);
        DrawText("SHIFT Sprint / accelerate",1120,188,19,LIGHTGRAY);
        DrawText("SPACE Brake",1120,216,19,LIGHTGRAY);
        DrawText("E Enter vehicle / interact",1120,244,19,LIGHTGRAY);
        DrawText("F Exit vehicle",1120,272,19,LIGHTGRAY);
        DrawText("F5 Save   F9 Load",1120,300,19,LIGHTGRAY);
        DrawText("TAB Close help",1120,328,19,LIGHTGRAY);
    }
}

void Game::DrawMinimap() const {
    if(!showMap) return;
    int s=190,x=1390,y=690;
    DrawRectangle(x,y,s,s,Fade(BLACK,0.75f));
    DrawRectangle(x,y+s/2-4,s,8,DARKGRAY);
    DrawRectangle(x+s/2-4,y,8,s,DARKGRAY);

    float px=x+s/2+player.position.x/240.0f*s;
    float py=y+s/2+player.position.z/240.0f*s;
    DrawCircle((int)px,(int)py,5,RED);

    for(const auto& b:world.buildings) {
        float bx=x+s/2+b.position.x/240.0f*s;
        float by=y+s/2+b.position.z/240.0f*s;
        DrawCircle((int)bx,(int)by,3,GRAY);
    }
    DrawText("MINIMAP",x+10,y+10,16,WHITE);
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(SkyColor());

    BeginMode3D(camera);
    world.Draw();
    traffic.Draw();
    DrawNPCs(npcs);

    if(inVehicle) playerCar.Draw(BLUE);
    else {
        player.Draw();
        if(playerCar.Near(player.position,5)) {
            DrawText("PRESS E TO ENTER CAR",
                     GetScreenWidth()/2-110,
                     GetScreenHeight()/2+80,18,WHITE);
        }
    }

    weather.DrawRain(player.position);
    EndMode3D();

    DrawHUD();
    DrawMinimap();

    EndDrawing();
}

void Game::Run() {
    while(running && !WindowShouldClose()) {
        float dt=GetFrameTime();
        Update(dt);
        Draw();
    }
}
