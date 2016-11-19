#include "ai.h"

namespace NEngine {

    void ThinkThenDo(TShip& ship, const std::vector<TShip*>& targetShips) {
        /*ship.SetLeftEngineStatus(false);
        ship.SetRightEngineStatus(false);

        auto targetPtr = targetShips[0];
        auto targetPosition = CalcRelativePosition(*targetPtr);
        auto selfPosition = CalcRelativePosition(ship);
        auto targetAngle = asin((selfPosition.Y - targetPosition.Y) / (selfPosition - targetPosition).Straight()) * 180.0;
        std::cout << targetAngle << " vs " << ship.GetAngle() << std::endl;
        if (abs(static_cast<int>(ship.Angle - targetAngle)) < 10) {

        } else if (ship.Angle < targetAngle) {
            ship.SetLeftEngineStatus(true);
        } else {
            ship.SetRightEngineStatus(true);
        }*/

        ship.Shoot();
    }

}