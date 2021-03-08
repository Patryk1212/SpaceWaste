#include "pch.h"
#include "Renderer3D.h"

namespace Engine
{
	const std::vector<Vertex> vertices =
	{
			{{-1.0f, -1.0f, -1.0f}, {0.6f, 0.75f, 0.9f}},
			{{ 1.0f, -1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},
			{{-1.0f,  1.0f, -1.0f}, {0.6f, 0.75f, 0.9f}},
			{{ 1.0f,  1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},

			{{-1.0f, -1.0f,  1.0f}, {1.13f, 0.3f, 0.4f}},
			{{ 1.0f, -1.0f,  1.0f}, {1.6f, 0.75f, 0.9f}},
			{{-1.0f,  1.0f,  1.0f}, {1.13f, 0.3f, 0.4f}},
			{{ 1.0f,  1.0f,  1.0f}, {1.6f, 0.75f, 0.9f}},

			{{-1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.4f}},
			{{ 1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.9f}},
			{{-1.0f, -1.0f, -1.0f}, {1.f, 1.f, 0.4f}},
			{{-1.0f, -1.0f,  1.0f}, {1.f, 1.f, 0.9f}},

			{{ 1.0f, -1.0f, -1.0f}, {0.13f, 0.3f, 0.4f}},
			{{ 1.0f, -1.0f,  1.0f}, {0.6f, 0.75f, 0.9f}}
	};

	const std::vector<uint16_t> indices =
	{
		0,2,1,   2,3,1,
		4,8,5,   5,8,9,
		2,6,3,   3,6,7,
		4,5,7,   4,7,6,
		2,10,11, 2,11,6,
		12,3,7,  12,7,13
	};

	struct Renderer3DData
	{
		std::unique_ptr<VulkanVertexBuffer> vertexBuffer;
		std::unique_ptr<VulkanIndexBuffer> indexBuffer;

		std::vector<std::unique_ptr<Cube>> objects;
		/*
		- cubes
		- cmd buffers
		- 
		*/
	};

	static Renderer3DData data;

	void Renderer3D::init()
	{
	}

	void Renderer3D::shutDown()
	{
	}

	void Renderer3D::beginScene()
	{
	}

	void Renderer3D::draw(const CameraController& camera)
	{
	}

	void Renderer3D::endScene()
	{
	}
}