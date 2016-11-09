#pragma once

#include "point.h"

#include <string>

namespace NEngine {

    class TObject {
        friend class TEngine;
    public:

        virtual ~TObject() = default;

        virtual void Process();

        const TPoint& GetPosition() const;
        const TPoint& GetSpeed() const;
        const TPoint& GetAcc() const;
        double GetAngle() const;
        size_t GetSize() const;
        size_t GetMass() const;

        bool IsGravityDealer() const;

        void SetPosition(double x, double y);
        void SetPosition(const TPoint& point);

        virtual std::string GetPngTextureName() const = 0;

    protected:
        TPoint Position;
        TPoint Speed;
        TPoint Acc; // Acceleration
        double Angle = 0;
        double AngleSpeed = 0;
        double AngleAcc = 0;
        size_t Size = 0;
        size_t Mass = 0;
    };

}