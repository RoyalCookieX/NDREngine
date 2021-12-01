#include "ndrpch.h"
#include "Core/Input.h"

namespace NDR
{
	Int32 ToNativeKeycode(Keycode key)
	{
		return (UInt32)key;
	}

	Keycode FromNativeKeycode(Int32 nativeKeycode)
	{
		return (Keycode)nativeKeycode;
	}

	Int32 ToNativeMouseButton(MouseButton button)
	{
		return (Int32)button;
	}

	MouseButton FromNativeMouseButton(Int32 nativeMouseButton)
	{
		return (MouseButton)nativeMouseButton;
	}
}
