#pragma once

namespace Engine
{
	class Time
	{
	public:
		Time() = default;
		~Time() = default;

		void onUpdate(float time) { deltaTime = time - lastFrame; lastFrame = time; }

		float getSeconds() const { return deltaTime; }
		float getDeltaTime() const { return deltaTime; }

	private:
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
	};
}