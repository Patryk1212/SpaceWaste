#pragma once

#include "core/SpaceObject.h"

class FileLoader
{
public:
	FileLoader() = default;
	~FileLoader() = default;

public:
	void loadFileNames();
	void loadTLEandCreateObjects(std::vector<std::unique_ptr<SpaceObject>>& objects);

private:
	std::vector<std::string> fileNames;
};