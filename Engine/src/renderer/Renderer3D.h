#pragma once

#include "core/CameraController.h"

namespace Engine
{
	class Renderer3D
	{
	public:
		static void init();
		static void shutDown();


		// start recording command buffers
		// pass objects
		// end recording

		static void beginScene();
		
		static void draw(const CameraController& camera);
		
		static void endScene();


	private:
		//std::vector<Object>

		// command buffers
	};
}