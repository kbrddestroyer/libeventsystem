#pragma once
#include "eventmanager.hpp"


namespace events {
    class EventManager;

    class EventBase {
        public:
        virtual ~EventBase() = default;
    };
}

// event.hpp
