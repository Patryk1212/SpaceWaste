#pragma once

#include "renderer/Object.h"

namespace Engine
{
	struct Message
	{
		int id = 0;
		bool status;
		int intNumber;
		int floatNumber;
		std::vector<std::shared_ptr<Object>> objects;
	};
}
