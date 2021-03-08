#pragma once

#include "coreLib.h"
#include "orbitLib.h"

class SpaceObject
{
public:
	SpaceObject(std::string& name, std::string& one, std::string& two);
	~SpaceObject() = default;

	std::string showName() const;
	std::string showFirstTLELine() const;
	std::string showSecondTLELine() const;

private:
	std::unique_ptr<cTle> tleSGP4;
	std::unique_ptr<cSatellite> satSGP4;
};