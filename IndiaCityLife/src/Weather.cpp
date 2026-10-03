#include "Weather.h"

void WeatherSystem::Update(float dt) {
    timer += dt;
    if(timer>50) {
        timer=0;
        type=(WeatherType)GetRandomValue(0,2);
    }
}

Color WeatherSystem::SkyColor(float hour) const {
    if(type==WeatherType::Rain) return {70,85,100,255};
    if(hour>=6 && hour<9) return {130,170,215,255};
    if(hour>=9 && hour<17) return SKYBLUE;
    if(hour>=17 && hour<20) return {225,135,90,255};
    return {12,18,40,255};
}

void WeatherSystem::DrawRain(Vector3 center) const {
    if(type!=WeatherType::Rain) return;
    for(int i=0;i<500;i++) {
        float x=center.x+GetRandomValue(-400,400)/10.0f;
        float y=GetRandomValue(20,300)/10.0f;
        float z=center.z+GetRandomValue(-400,400)/10.0f;
        DrawLine3D({x,y,z},{x,y-1.6f,z},SKYBLUE);
    }
}
