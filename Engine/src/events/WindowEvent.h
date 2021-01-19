#pragma once

#include "Event.h"

namespace Engine
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width_, unsigned int height_) : width(width_), height(height_) {}

		inline unsigned int getWidth() const { return width; }
		inline unsigned int getHeight() const { return height; }

		EVENT_CLASS_TYPE(WINDOW_RESIZE)

	private:
		unsigned int width;
		unsigned int height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WINDOW_CLOSE)
	};
}