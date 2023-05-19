#pragma once
#include "vector"
#include <functional>

#include "../../ExecutionManager.h"

#include "Event.h"
#include "EventTypes/ApplicationEvent.h"
#include "EventTypes/KeyEvent.h"
#include "EventTypes/MouseEvent.h"

// #define GRYPHON_FUNC(function) std::bind(print_num, 31337);

namespace Engine {

    class RegisteredEvent {
    public:
        Event::Type event_type;
        std::function<bool(Event)> event_function;  
    };

    class EventSystem : public ExecutionSystem {
    public:
    
    public:
        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;
    public:
        // template <typename Type>
        // void RegisterEvent(std::function<bool()> on_function) {
        //     on_function(KeyPressedEvent());
        // }
    };
}