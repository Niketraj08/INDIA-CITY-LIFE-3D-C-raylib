#include "Mission.h"

void MissionSystem::Start() {
    current = {"A New Start","Visit the City Bank",500,true,false};
    started=true;
}

void MissionSystem::Update(Vector3 p,float& money) {
    if(!started) Start();

    if(current.active && !current.completed) {
        // Bank location used by World.cpp
        if(Vector3Distance({p.x,0,p.z},{70,0,-65})<14) {
            current.completed=true;
            current.active=false;
            money += current.reward;
        }
    }
}

void MissionSystem::DrawHUD() const {
    if(!started) return;
    DrawRectangle(20,105,380,90,Fade(BLACK,0.72f));
    DrawText(current.title.c_str(),35,118,22,WHITE);
    DrawText(current.objective.c_str(),35,150,18,LIGHTGRAY);
    if(current.completed) DrawText("COMPLETED",35,172,18,GREEN);
}
