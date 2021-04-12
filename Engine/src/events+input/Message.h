#pragma once

#include "renderer/Object.h"

namespace Engine
{
	struct Message
	{
		std::vector<bool> status;
		std::vector<int> number;
		std::vector<std::unique_ptr<Object>> objects;
	};
}
