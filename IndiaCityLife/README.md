# INDIA CITY LIFE — 3D C++ / raylib

A large-scale 3D city-simulation foundation built with C++17 and raylib.

## Implemented

- 3D procedural city
- Third-person player controller
- Walk / sprint
- Drivable car
- Car steering, acceleration, braking and fuel
- Vehicle collision / damage
- NPC pedestrians with destinations and simple AI
- Traffic cars
- Four-way traffic lights
- Traffic-light-aware vehicle stopping
- Buildings and collision
- Bank, hospital, shop, restaurant, police station and garage
- Day/night cycle
- Sunny / cloudy / rain weather
- Rain particles
- Health / hunger / energy
- Money and jobs
- Mission system
- Interaction system
- HUD
- Minimap
- Save / load
- Camera following
- CMake project

## Controls

WASD       Move / drive
SHIFT      Sprint / accelerate
SPACE      Brake / handbrake
E          Interact / enter vehicle
F          Exit vehicle
M          Toggle minimap
TAB        Toggle help
ESC        Exit

## Run the project

### Prerequisites

- CMake 3.16+
- C++17 compiler
- raylib 5.x

### Windows (Visual Studio)

From the project folder:

```bash
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

Run the game:

```bash
./build/Release/IndiaCityLife.exe
```

If you are using a different generator, make sure the final executable path matches the generated build output.

### Linux / macOS

```bash
cmake -S . -B build
cmake --build build -j
./build/IndiaCityLife
```

## Notes

The project intentionally starts with procedural raylib geometry, so it runs without requiring a large asset download. Replace/add GLTF/GLB models, PBR textures, animations, sounds and larger map data in `assets/` as the project grows.

This is a game foundation, not a claim of photorealistic AAA graphics. The systems are separated so high-quality assets and more advanced simulation can be added without rewriting the core.

## Quick run command

```bash
cd IndiaCityLife
cmake -S . -B build
cmake --build build
./build/IndiaCityLife
```

On Windows:

```powershell
cd IndiaCityLife
cmake -S . -B build
cmake --build build --config Release
./build/Release/IndiaCityLife.exe
```