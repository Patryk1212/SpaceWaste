#include "pch.h"
#include "SpaceObject.h"

SpaceObject::SpaceObject(const glm::vec3& pos_, const glm::vec3& scale_, const glm::vec3& color_)
{
	position = pos_;
	scale = scale_;
	color = color_;
	rotation = 0.0f;
}

SpaceObject::SpaceObject(std::string& name, std::string& one, std::string& two)
{
	tleSGP4 = std::make_unique<cTle>(name, one, two);
	satSGP4 = std::make_unique<cSatellite>(*tleSGP4.get());

	cEciTime eci = satSGP4->PositionEci(360);
	vector<cEci> vecPos;

	vecPos.push_back(eci);

	position = { vecPos[0].Position().m_x, vecPos[0].Position().m_z, vecPos[0].Position().m_y};
	position /= 7;
	scale *= 2;
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
