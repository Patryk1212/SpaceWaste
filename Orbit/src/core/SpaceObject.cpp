#include "pch.h"
#include "SpaceObject.h"

SpaceObject::SpaceObject(const glm::vec3& pos)
{
	setScale({ 100.f, 100.f, 100.f });
}

SpaceObject::SpaceObject(std::string& name, std::string& one, std::string& two)
{
	tleSGP4 = std::make_unique<cTle>(name, one, two);
	satSGP4 = std::make_unique<cSatellite>(*tleSGP4.get());

	cEciTime eci = satSGP4->PositionEci(1234);
	vector<cEci> vecPos;

	vecPos.push_back(eci);


	setPosition({ vecPos[0].Position().m_x, vecPos[0].Position().m_y, vecPos[0].Position().m_z });
}

std::string SpaceObject::showName() const
{
	return satSGP4->Name().c_str();
}

std::string SpaceObject::showFirstTLELine() const
{
	return satSGP4->Orbit().TleLine1().c_str();
}

std::string SpaceObject::showSecondTLELine() const
{
	return satSGP4->Orbit().TleLine1().c_str();
}
