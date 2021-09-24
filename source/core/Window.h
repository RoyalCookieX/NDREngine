#pragma once

namespace NDR
{
    struct WindowProps
    {
    public:
        int width;
        int height;
        std::string name;
        bool isVsync;

        WindowProps(int width, int height, const std::string& name, bool isVsync)
            : width(width),
              height(height),
              name(name),
              isVsync(isVsync)
        {
        }
    };
    
    class Window
    {
    public:
        Window(const WindowProps& properties);
        ~Window();

        void SetContextCurrent() const;
        void SetVSync(bool vSync);
        bool Active() const;
        void Close();

        void SwapBuffers() const;
        void PollEvents() const;

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
    
    private:
        GLFWwindow* _window;
        WindowProps _properties;
        bool _active;
        
        inline static uint32_t _windowCount = 0;
    };
}
