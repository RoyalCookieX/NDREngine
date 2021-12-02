#pragma once
#include "Core/Window.h"

namespace NDR
{
    class EventDispatcher;
    
    class Win32Window : public Window
    {
    public:
        Win32Window(const WindowProperties& properties, const SPointer<EventDispatcher>& dispatcher);
        virtual ~Win32Window() override;

        Win32Window(const Win32Window&) = delete;
        Win32Window& operator=(const Win32Window&) = delete;

        explicit operator GLFWwindow*() const { return _window; }

        virtual UInt32Pair GetSize() const override { return _properties.size; }
        virtual bool IsActive() const override { return _active; }
        virtual const SPointer<EventDispatcher>& GetDispatcher() override { return _dispatcher; }
        
        virtual void SetContextCurrent() const override;
        virtual void SetVSync(bool vSync) override;
        virtual void Close() override;
        virtual void SwapBuffers() const override;
        virtual void PollEvents() const override;

    private:
        virtual void OnEvent(const SPointer<Event>& e) override;
        
        GLFWwindow* _window;
        WindowProperties _properties;
        SPointer<EventDispatcher> _dispatcher;
        bool _active;
    };
}
