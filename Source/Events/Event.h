#pragma once

#include "Defines.h"
#include "Core/Keycodes.h"

namespace NDR
{
	enum class EventCategory
	{
		NONE			= 0,
		APPLICATION		= BIT( 0),
		WINDOW			= BIT( 1),
		WINDOWFOCUS		= BIT( 2) | WINDOW,
		WINDOWMAXIMIZE	= BIT( 3) | WINDOW,
		WINDOWMOVE		= BIT( 4) | WINDOW,
		WINDOWRESIZE	= BIT( 5) | WINDOW,
		WINDOWCLOSE		= BIT( 6) | WINDOW,
		INPUT			= BIT( 7),
		KEY				= BIT( 8) | INPUT,
		KEYPRESS		= BIT( 9) | KEY,
		MOUSE			= BIT(10) | INPUT,
		MOUSEPRESS		= BIT(11) | MOUSE,
		MOUSEMOVE		= BIT(12) | MOUSE,
		MOUSESCROLL		= BIT(13) | MOUSE,
		ANY				= (BIT(13)) - 1
	};

	struct Event
	{
	public:
		virtual ~Event() = default;

		virtual EventCategory GetCategory() const = 0;
		virtual const char* GetName() const = 0;

		bool IsCategory(EventCategory category) const { return (UInt32)GetCategory() & (UInt32)category; }
		
		void Consume() { _handled = true; }
		bool IsHandled() const { return _handled; }
	private:
		bool _handled = false;
	};

	struct ApplicationEvent : public Event
	{
	public:
		virtual EventCategory GetCategory() const override { return EventCategory::APPLICATION; }
		virtual const char* GetName() const override { return "ApplicationEvent"; }
	};

	struct WindowEvent : public Event
	{
	public:
		virtual EventCategory GetCategory() const override { return EventCategory::WINDOW; }
		virtual const char* GetName() const override { return "WindowEvent"; }
	};

	struct WindowFocusEvent : public WindowEvent
	{
	public:
		WindowFocusEvent(bool hasFocus): _hasFocus(hasFocus) { }
		virtual const char* GetName() const override { return "WindowFocusEvent"; }
		
		virtual EventCategory GetCategory() const override { return EventCategory::WINDOWFOCUS; }

		bool HasFocus() const { return _hasFocus; }
	private:
		bool _hasFocus;
	};

	struct WindowMaximizeEvent : public WindowEvent
	{
	public:
		WindowMaximizeEvent(bool hasMaximized): _hasMaximized(hasMaximized) { }
		virtual const char* GetName() const override { return "WindowMaximizeEvent"; }

		virtual EventCategory GetCategory() const override { return EventCategory::WINDOWMAXIMIZE; }

		bool HasMaximized() const { return _hasMaximized; }
	private:
		bool _hasMaximized;
	};

	struct WindowMoveEvent : public WindowEvent
	{
	public:
		WindowMoveEvent(const UInt32Pair& position): _position(position) { }
		virtual const char* GetName() const override { return "WindowMoveEvent"; }

		virtual EventCategory GetCategory() const override { return EventCategory::WINDOWMOVE; }

		UInt32Pair GetPosition() const { return _position; }
	private:
		UInt32Pair _position;
	};

	struct WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(const UInt32Pair& size): _size(size) { }
		virtual const char* GetName() const override { return "WindowResizeEvent"; }

		virtual EventCategory GetCategory() const override { return EventCategory::WINDOWRESIZE; }

		UInt32Pair GetSize() const { return _size; }
	private:
		UInt32Pair _size;
	};

	struct WindowCloseEvent : public WindowEvent
	{
	public:
		WindowCloseEvent() = default;

		virtual EventCategory GetCategory() const override { return EventCategory::WINDOWCLOSE; }
		virtual const char* GetName() const override { return "WindowCloseEvent"; }
	};

	struct InputEvent : public Event
	{
	public:
		virtual EventCategory GetCategory() const override { return EventCategory::INPUT; }
		virtual const char* GetName() const override { return "InputEvent"; }
	};

	struct KeyEvent : public InputEvent
	{
	public:
		virtual EventCategory GetCategory() const override { return EventCategory::KEY; }
		virtual const char* GetName() const override { return "KeyEvent"; }
	};

	struct KeyPressEvent : public InputEvent
	{
	public:
		KeyPressEvent(Keycode key, bool isPressed): _key(key), _isPressed(isPressed) { }

		virtual EventCategory GetCategory() const override { return EventCategory::KEYPRESS; }
		virtual const char* GetName() const override { return "KeyPressEvent"; }

		Keycode GetKey() const { return _key; }
		bool IsPressed() const { return _isPressed; }
	private:
		Keycode _key;
		bool _isPressed;
	};

	struct MouseEvent : public InputEvent
	{
	public:
		virtual EventCategory GetCategory() const override { return EventCategory::MOUSE; }
		virtual const char* GetName() const override { return "MouseEvent"; }
	};

	struct MousePressEvent : public MouseEvent
	{
	public:
		MousePressEvent(MouseButton button, bool isPressed): _button(button), _isPressed(isPressed) { }

		virtual EventCategory GetCategory() const override { return EventCategory::MOUSEPRESS; }
		virtual const char* GetName() const override { return "MousePressEvent"; }

		MouseButton GetButton() const { return _button; }
		bool IsPressed() const { return _isPressed; }
	private:
		MouseButton _button;
		bool _isPressed;
	};

	struct MouseMoveEvent : public MouseEvent
	{
	public:
		MouseMoveEvent(const UInt32Pair& position): _position(position) { }

		virtual EventCategory GetCategory() const override { return EventCategory::MOUSEMOVE; }
		virtual const char* GetName() const override { return "MouseMoveEvent"; }
		
		UInt32Pair GetPosition() const { return _position; }
	private:
		UInt32Pair _position;
	};

	struct MouseScrollEvent : public MouseEvent
	{
	public:
		MouseScrollEvent(Int32 delta): _delta(delta) { }

		virtual EventCategory GetCategory() const override { return EventCategory::MOUSESCROLL; }
		virtual const char* GetName() const override { return "MouseScrollEvent"; }

		Int32 GetDelta() const { return _delta; }
	private:
		Int32 _delta;
	};
}