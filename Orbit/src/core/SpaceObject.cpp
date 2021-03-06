#include "pch.h"
#include "SpaceObject.h"

SpaceObject::SpaceObject(std::string& name, std::string& one, std::string& two)
	: name(name), one(one), two(two) 
{
	tleSGP4 = std::make_unique<cTle>(name, one, two);
	satSGP4 = std::make_unique<cSatellite>(*tleSGP4.get());
}

std::string SpaceObject::showName() const
{
	return name;
}
