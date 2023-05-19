#pragma once
#include "vector"
#include <functional>

#include "../../ExecutionManager.h"

#include "Event.h"
#include "EventTypes/ApplicationEvent.h"
#include "EventTypes/KeyEvent.h"
#include "EventTypes/MouseEvent.h"

#define GRYPHON_FUNC(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Engine {
    class RegisteredEvent {
    public:
        Event::Type event_type;
        std::function<void(Event*)> event_function;  
    public:
        bool Process(Event* event_code) {
            event_function(event_code);
        }
    };

    class EventSystem : public ExecutionSystem {
    public:
        std::vector<RegisteredEvent> events = {};

    public:
        virtual void OnStart()override;
        virtual void OnUpdate() override;
        virtual void OnEnd() override;
    public:
        template <typename T>
        void ProcessEvent(T event_code) {
            Event::Type EventType = T::GetStaticType();
            for (int i = 0; i < events.size(); i++) {
                if (events[i].event_type == EventType) 
                    events[i].Process(&event_code);
            }
        }

        template <typename Type, typename F>
        void RegisterEvent(F on_function) {
            RegisteredEvent new_event = RegisteredEvent();
            new_event.event_function = [on_function](Event* event_code) {
                Type event_type = *((Type*)event_code);
                on_function(event_type);
            };
            new_event.event_type = Type::GetStaticType();
            events.push_back(new_event);
        }
    };
}