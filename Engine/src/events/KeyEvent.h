#pragma once

#include "Event.h"

namespace Engine
{
	class KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return key_code; }

	protected:
		KeyEvent(int key_code) : key_code(key_code) {}
		int key_code;
	};

	class KeyPressedEvent : KeyEvent
	{
	public:
		KeyPressedEvent(int key_code) : KeyEvent(key_code) {}

		EVENT_CLASS_TYPE(KEY_PRESSED)
	};

	class KeyReleasedEvent : KeyEvent
	{
	public:
		KeyReleasedEvent(int key_code) : KeyEvent(key_code) {}

		EVENT_CLASS_TYPE(KEY_RELEASED)
	};

	class KeyTypedEvent : KeyEvent
	{
	public:
		KeyTypedEvent(int key_code) : KeyEvent(key_code) {}

		EVENT_CLASS_TYPE(KEY_TYPED)
	};
}