#include "ndrpch.h"
#include "Window.h"

#include "Log.h"
#include "API/Platform/Win32/Window_Win32.h"

namespace NDR
{
    UPointer<Window> Window::Create(const WindowProperties& properties, const SPointer<EventDispatcher>& dispatcher)
    {
#if NDR_PLATFORM_WINDOWS
        return CreateUnique<Win32Window>(properties, dispatcher);
#else
        NDR_LOGFATAL("[Window]: Failed to create Window!");
        return {};
#endif
    }
}
