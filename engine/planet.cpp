#include "planet.h"
#include <cmath>

namespace NEngine {

    TPlanet::TPlanet(const TPoint& sunPosition)
        : SunPosition(sunPosition)
    {
        Size = 240;
        Mass = 100;
    }

    void TPlanet::SetOrbitRadius(double orbitRadius) {
        OrbitRadius = orbitRadius;
    }

    void TPlanet::SetOrbitSpeed(double orbitSpeed) {
        OrbitSpeed = orbitSpeed;
    }

    void TPlanet::SetOrbitAngle(double orbitAngle) {
        OrbitAngle = orbitAngle;
    }

    void TPlanet::Process() {
        OrbitAngle += OrbitSpeed;
        Position.X = cos(OrbitAngle) * OrbitRadius + SunPosition.X;
        Position.Y = sin(OrbitAngle) * OrbitRadius + SunPosition.Y;
    }

    std::string TPlanet::GetPngTextureName() const {
        return "planet.png";
    }

}