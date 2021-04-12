#pragma once

#include "renderer/Object.h"

namespace Engine
{
	struct Message
	{
		std::vector<bool> status;
		std::vector<int> intNumber;
		std::vector<int> floatNumber;
		std::vector<std::shared_ptr<Object>> objects;
	};
}
