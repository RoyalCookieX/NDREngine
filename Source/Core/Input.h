#pragma once
#include "Defines.h"
#include "Keycodes.h"

namespace NDR
{
    struct Event;
    class EventDispatcher;
    
    class Input
    {
    public:
        friend class Engine;
        
        static bool OnKey(Keycode key);
        static bool OnKeyPressed(Keycode key);
        static bool OnKeyReleased(Keycode key);

        static bool OnMouseButton(MouseButton button);
        static bool OnMouseButtonDown(MouseButton button);
        static bool OnMouseButtonUp(MouseButton button);
        static UInt32Pair GetMousePosition();
        static float GetMouseScroll();
    private:
        static void Initialize(const SPointer<EventDispatcher>& dispatcher);
        static void Tick();
        static void Shutdown();
        static void OnEvent(const SPointer<Event>& e);
    };
}