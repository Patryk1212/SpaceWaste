#pragma once

namespace Engine
{
	enum class EventType
	{
		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE,
		KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
		MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
	};
	
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

	class Event
	{
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string getNameString() const { return getName(); }

		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : event(event) {}

		template<typename T>
		bool dispatch(EventFn<T> function)
		{
			if (event.getEventType() == T::getStaticType())
			{
				event.handled = function(*(T*)&event);
				return true;
			}
		}

	private:
		Event& event; // reference
	};
}