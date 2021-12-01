#include "ndrpch.h"
#include "Input.h"

#include "Assert.h"
#include "Events/EventDispatcher.h"

namespace NDR
{
    struct InputContext
    {
        bool initialized;
        SPointer<EventDispatcher> dispatcher;
        std::vector<SPointer<InputEvent>> inputEvents;

        UInt32Pair mousePosition;
    };
    static InputContext sContext;

    template<typename TType>
    bool InputEventExists(const std::vector<SPointer<InputEvent>>& inputEvents, EventCategory category, std::function<bool(SPointer<TType>)> predicate)
    {
        for(const auto& inputEvent : inputEvents)
        {
            if(inputEvent->GetCategory() == category)
            {
                const SPointer<TType>& typeEvent = std::dynamic_pointer_cast<TType>(inputEvent);
                if(predicate(typeEvent))
                    return true;
            }
        }
        return false;
    }

    template<typename TType>
    SPointer<TType> GetInputEvent(const std::vector<SPointer<InputEvent>>& inputEvents, EventCategory category)
    {
        for(const std::shared_ptr<InputEvent>& inputEvent : inputEvents)
        {
            if(inputEvent->GetCategory() == category)
                return std::dynamic_pointer_cast<TType>(inputEvent);
        }
        return nullptr;
    }
    
    bool Input::OnKey(Keycode key)
    {
        auto keyFunc = [key](const SPointer<KeyPressEvent> keyPressEvent){ return keyPressEvent->GetKey() == key; };
        return InputEventExists<KeyPressEvent>(sContext.inputEvents, EventCategory::KEYPRESS, keyFunc);
    }

    bool Input::OnKeyPressed(Keycode key)
    {
        auto keyDownFunc = [key](const SPointer<KeyPressEvent>& keyPressEvent){ return keyPressEvent->GetKey() == key && keyPressEvent->IsPressed(); };
        return InputEventExists<KeyPressEvent>(sContext.inputEvents, EventCategory::KEYPRESS, keyDownFunc);
    }

    bool Input::OnKeyReleased(Keycode key)
    {
        auto keyUpFunc = [key](const SPointer<KeyPressEvent>& keyPressEvent){ return keyPressEvent->GetKey() == key && !keyPressEvent->IsPressed(); };
        const bool current = InputEventExists<KeyPressEvent>(sContext.inputEvents, EventCategory::KEYPRESS, keyUpFunc);
        return current;
    }

    bool Input::OnMouseButton(MouseButton button)
    {
        auto mouseFunc = [button](const SPointer<MousePressEvent>& mousePressEvent) { return mousePressEvent->GetButton() == button; };
        return InputEventExists<MousePressEvent>(sContext.inputEvents, EventCategory::MOUSEPRESS, mouseFunc);
    }

    bool Input::OnMouseButtonDown(MouseButton button)
    {
        auto mouseDownFunc = [button](const SPointer<MousePressEvent>& mousePressEvent) { return mousePressEvent->GetButton() == button && mousePressEvent->IsPressed(); };
        return InputEventExists<MousePressEvent>(sContext.inputEvents, EventCategory::MOUSEPRESS, mouseDownFunc);
    }

    bool Input::OnMouseButtonUp(MouseButton button)
    {
        auto mouseUpFunc = [button](const SPointer<MousePressEvent>& mousePressEvent) { return mousePressEvent->GetButton() == button && !mousePressEvent->IsPressed(); };
        return InputEventExists<MousePressEvent>(sContext.inputEvents, EventCategory::MOUSEPRESS, mouseUpFunc);
    }
    
    UInt32Pair Input::GetMousePosition()
    {
        const SPointer<MouseMoveEvent> mouseMoveEvent = GetInputEvent<MouseMoveEvent>(sContext.inputEvents, EventCategory::MOUSEMOVE);
        if(mouseMoveEvent != nullptr)
            sContext.mousePosition = mouseMoveEvent->GetPosition();
        return sContext.mousePosition;
    }

    float Input::GetMouseScroll()
    {
        return 0;
    }

    void Input::Initialize(const SPointer<EventDispatcher>& dispatcher)
    {
        NDR_ASSERT(!sContext.initialized, "[Input]: Input is already initialized!");
        sContext.initialized = true;
        sContext.dispatcher = dispatcher;
        sContext.dispatcher->AddCallback(EventCategory::INPUT, NDR_BIND_STATIC_EVENTFUNC(OnEvent));
    }

    void Input::Tick()
    {
        NDR_ASSERT(sContext.initialized, "[Input]: Input is not already initialized!");
        sContext.inputEvents.clear();
    }

    void Input::Shutdown()
    {
        NDR_ASSERT(sContext.initialized, "[Input]: Input is not already initialized!");
        sContext.initialized = false;
    }

    void Input::OnEvent(const SPointer<Event>& e)
    {
        NDR_CAST_EVENT(e, InputEvent, inputEvent);
        sContext.inputEvents.push_back(inputEvent);
    }
}
