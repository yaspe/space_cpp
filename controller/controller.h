#pragma once

namespace NController {

    enum class TEventType {
        None,
        Quite,
        MainEngineOn,
        MainEngineOff,
        LeftEngineOn,
        LeftEngineOff,
        RightEngineOn,
        RightEngineOff,
    };

    TEventType PollEvent();

}