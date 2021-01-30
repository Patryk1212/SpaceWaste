#pragma once

namespace Engine
{
	class Renderer3D
	{
	public:
		static void init();
		static void shutDown();

		static void beginScene();
		static void endScene();

		static void draw();
	};
}