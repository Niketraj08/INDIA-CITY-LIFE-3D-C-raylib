#include "Traffic.h"

void TrafficSystem::Create() {
    cars.clear();
    lights.clear();

    for(int i=0;i<18;i++) {
        Vehicle v;
        v.position={-115.0f-i*2.0f,0.75f,(float)((i%7)*30)};
        v.speed=4.0f+(i%4);
        cars.push_back(v);
    }

    for(int i=-3;i<=3;i++) {
        TrafficLight l;
        l.position={i*30.0f,3.0f,6.0f};
        l.horizontalAxis=true;
        lights.push_back(l);
    }
}

void TrafficSystem::Update(float dt) {
    cycle += dt;
    if(cycle>18) cycle=0;

    TrafficLightState state =
        cycle < 8 ? TrafficLightState::Green :
        cycle < 11 ? TrafficLightState::Yellow :
        TrafficLightState::Red;

    for(auto& l:lights) l.state=state;

    for(auto& c:cars) c.UpdateTraffic(dt,ShouldStop(c));
}

bool TrafficSystem::ShouldStop(const Vehicle& car) const {
    for(const auto& l:lights) {
        if(l.state==TrafficLightState::Red &&
           std::fabs(car.position.x-l.position.x)<8 &&
           std::fabs(car.position.z-l.position.z)<6)
            return true;
    }
    return false;
}

void TrafficSystem::Draw() const {
    for(const auto& c:cars) c.Draw((Color){GetRandomValue(60,230),GetRandomValue(60,230),GetRandomValue(60,230),255});

    for(const auto& l:lights) {
        DrawCylinder(l.position,0.25f,6,8,DARKGRAY);
        Color c= l.state==TrafficLightState::Green?GREEN:
                 l.state==TrafficLightState::Yellow?YELLOW:RED;
        DrawSphere({l.position.x,l.position.y+3,l.position.z},0.5f,c);
    }
}
