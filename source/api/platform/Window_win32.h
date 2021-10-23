#pragma once
#include "core/Window.h"

namespace NDR
{
    class Window_win32 : public Window
    {
    public:
        Window_win32(const WindowProps& properties);
        virtual ~Window_win32() override;
        
        explicit operator GLFWwindow*() const;

        virtual void AddCallback(EventFunc callback) override;
        virtual void SetContextCurrent() const override;
        virtual void SetVSync(bool vSync) override;
        virtual bool Active() const override;
        virtual void Close() override;
        virtual void SwapBuffers() const override;
        virtual void PollEvents() const override;
        virtual uint32_t GetWidth() const override;
        virtual uint32_t GetHeight() const override;
    
    protected:
        virtual void Dispatch(Event* event) const override;
    private:
        GLFWwindow* _window;
        WindowProps _properties;
        bool _active;
        std::vector<EventFunc> _callbacks;
        
        inline static uint32_t _windowCount = 0;
    };
}
