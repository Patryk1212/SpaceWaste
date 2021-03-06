#pragma once

#include "core/SpaceObject.h"

class FileLoader
{
public:
	FileLoader() = default;
	~FileLoader() = default;

public:
	void createObjectsAndLoadTLE(std::vector<std::unique_ptr<SpaceObject>>& objects);
};