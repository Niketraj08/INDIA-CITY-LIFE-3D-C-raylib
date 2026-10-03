#include "World.h"

static void addB(std::vector<Building>& v, Vector3 p, Vector3 s,
                 BuildingType t, Color c, const char* name) {
    v.push_back({p,s,t,c,name});
}

void World::Create() {
    buildings.clear();

    addB(buildings,{-65,7,-65},{18,14,18},BuildingType::Office,GRAY,"Office");
    addB(buildings,{-30,5,-65},{16,10,16},BuildingType::Shop,ORANGE,"Super Market");
    addB(buildings,{30,12,-65},{22,24,22},BuildingType::Hospital,WHITE,"City Hospital");
    addB(buildings,{70,8,-65},{18,16,18},BuildingType::Bank,GOLD,"National Bank");

    addB(buildings,{-70,5,-25},{16,10,16},BuildingType::House,BEIGE,"House");
    addB(buildings,{-45,6,-25},{16,12,16},BuildingType::House,LIGHTGRAY,"House");
    addB(buildings,{-75,5,35},{18,10,18},BuildingType::Restaurant,ORANGE,"Restaurant");
    addB(buildings,{-48,5,35},{16,10,16},BuildingType::Shop,MAROON,"Clothing Store");

    addB(buildings,{65,12,-25},{22,24,22},BuildingType::Office,GRAY,"Business Tower");
    addB(buildings,{88,5,8},{18,10,18},BuildingType::Shop,ORANGE,"Electronics");
    addB(buildings,{68,7,58},{20,14,20},BuildingType::Police,BLUE,"Police Station");

    addB(buildings,{-70,5,75},{18,10,18},BuildingType::House,BEIGE,"House");
    addB(buildings,{-35,7,75},{18,14,18},BuildingType::Office,GRAY,"Office");
    addB(buildings,{30,5,75},{18,10,18},BuildingType::Shop,ORANGE,"Cafe");
    addB(buildings,{70,7,75},{20,14,20},BuildingType::House,LIGHTGRAY,"Apartment");

    roads.clear();
    for (int i=-3;i<=3;i++) roads.push_back({i*30.0f,0,0});
}

void World::Draw() const {
    DrawPlane({0,0,0},{240,240},Color{80,145,75,255});

    // Main and secondary roads
    for (int i=-3;i<=3;i++) {
        float r=i*30.0f;
        DrawCube({0,-0.08f,r},{240,0.16f,8},DARKGRAY);
        DrawCube({r,-0.08f,0},{8,0.16f,240},DARKGRAY);
    }

    // Road markings
    for (float i=-116;i<116;i+=8) {
        for (int r=-3;r<=3;r++) {
            float z=r*30.0f;
            DrawCube({i,0.02f,z},{4,0.03f,0.12f},YELLOW);
            DrawCube({z,0.02f,i},{0.12f,0.03f,4},YELLOW);
        }
    }

    for (const auto& b: buildings) {
        DrawCube(b.position,b.size.x,b.size.y,b.size.z,b.color);
        DrawCube({b.position.x,b.position.y+b.size.y/2+0.3f,b.position.z},
                 {b.size.x+0.4f,b.size.y*0.03f+0.35f,b.size.z+0.4f},DARKGRAY);

        // windows on front
        for(float x=-b.size.x/2+2;x<b.size.x/2;x+=3) {
            for(float y=2;y<b.size.y-1;y+=3) {
                DrawCube({b.position.x+x,y,b.position.z-b.size.z/2-0.03f},
                         {1.0f,1.1f,0.05f},SKYBLUE);
            }
        }
    }
}

bool World::Collides(Vector3 p,float radius) const {
    for(const auto& b:buildings) {
        if(p.x>b.position.x-b.size.x/2-radius &&
           p.x<b.position.x+b.size.x/2+radius &&
           p.z>b.position.z-b.size.z/2-radius &&
           p.z<b.position.z+b.size.z/2+radius) return true;
    }
    return false;
}

const Building* World::NearbyBuilding(Vector3 p,float radius) const {
    for(const auto& b:buildings)
        if(Vector3Distance({p.x,0,p.z},{b.position.x,0,b.position.z})<radius)
            return &b;
    return nullptr;
}
