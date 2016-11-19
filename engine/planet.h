#pragma once

#include "object.h"

namespace NEngine {

    class TPlanet : public TObject {
    public:
        TPlanet(const TPoint& sunPosition);
        void Process() override;
        void SetOrbitRadius(double orbitRadius);
        void SetOrbitSpeed(double orbitSpeed);
        void SetOrbitAngle(double orbitAngle);
        std::string GetPngTextureName() const override;

    private:
        double OrbitAngle = 0;
        double OrbitSpeed = 0;
        double OrbitRadius = 0;
        TPoint SunPosition;
    };

}
