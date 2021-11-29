#pragma once
#include "ButtonCodes.h"

namespace NDR
{
    enum class EventType
    {
        KEY = 0,
        MOUSE = 1,
    };
    
    struct Event
    {
    public:
        virtual ~Event() { };
        
        virtual const char* GetName() const = 0;
        virtual EventType GetEventType() const = 0;
        bool IsHandled() const { return _handled; }
        void Consume() { _handled = true; }
    private:
        bool _handled = false;
    };

    struct KeyEvent : public Event
    {
    public:
        KeyEvent(NDRKey key, NDRButtonAction action): _key(key), _action(action) { }
        virtual ~KeyEvent() override { };
        
        virtual const char* GetName() const override { return "KeyEvent"; }
        virtual EventType GetEventType() const override { return EventType::KEY; }

        NDRKey GetKey() const { return _key; }
        NDRButtonAction GetAction() const { return _action; }
    
    private:
        NDRKey _key = 0;
        NDRButtonAction _action = 0;
    };

    struct MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(NDRMouseButton button, NDRButtonAction action): _button(button), _action(action) { }
        virtual ~MouseButtonEvent() override { };
        
        virtual const char* GetName() const override { return "MouseEvent"; }
        virtual EventType GetEventType() const override { return EventType::MOUSE; }

        NDRMouseButton GetButton() const { return _button; }
        NDRButtonAction GetAction() const { return _action; }
    private:
        NDRMouseButton _button = 0;
        NDRButtonAction _action = 0;
    };
}
