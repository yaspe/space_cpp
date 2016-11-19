#include "sun.h"

namespace NEngine {
    TSun::TSun() {
        Size = 640;
        Mass = 1000;
    }

    std::string TSun::GetPngTextureName() const {
        return "sun.png";
    }

    // Currently Sun has nothing to do, just... hm... chilling in the space
    void TSun::Process() {
    }
}