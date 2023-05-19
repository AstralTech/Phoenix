#pragma once


namespace Engine {

#define EVENT_CLASS_TYPE(type) static Event::Type GetStaticType() { return Event::Type::type; }\
								virtual Event::Type GetType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

    class Event {
    public:
        enum class Type {
            WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
            AppTick, AppUpdate, AppRender,
            KeyPressed, KeyReleased, KeyTyped,
            MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
        };
    public:
        bool Handled = false;
    public:
        virtual Type GetType() const = 0;
        virtual const char* GetName() const = 0;
    };
}
