#pragma once

#include "Event.h"

namespace Engine
{
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y) : mouse_x(x), mouse_y(y) {}

		inline float getX() const { return mouse_x; }
		inline float getY() const { return mouse_y; }

		EVENT_CLASS_TYPE(MOUSE_MOVED)

	private:
		float mouse_x;
		float mouse_y;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float x_offest_, float y_offest_) : x_offset(x_offest_), y_offset(y_offest_) {}

		inline float getXOffset() const { return x_offset; }
		inline float getYOffest() const { return y_offset; }

		EVENT_CLASS_TYPE(MOUSE_SCROLLED)

	private:
		float x_offset;
		float y_offset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton() const { return button; }

	protected:
		MouseButtonEvent(int button_) : button(button_) {}
		int button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button_) : MouseButtonEvent(button_) {}

		EVENT_CLASS_TYPE(MOUSE_PRESSED)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button_) : MouseButtonEvent(button_) {}

		EVENT_CLASS_TYPE(MOUSE_RELEASED)
	};
}