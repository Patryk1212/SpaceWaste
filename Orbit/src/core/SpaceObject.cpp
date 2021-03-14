#include "pch.h"
#include "SpaceObject.h"

SpaceObject::SpaceObject(std::string& name, std::string& one, std::string& two)
{
	tleSGP4 = std::make_unique<cTle>(name, one, two);
	satSGP4 = std::make_unique<cSatellite>(*tleSGP4.get());

	calcualateSpacePosition();
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

void SpaceObject::calcualateSpacePosition()
{
	cEciTime eci = satSGP4->PositionEci(360);
	vector<cEci> vecPos;

	vecPos.push_back(eci);

	position = { vecPos[0].Position().m_x, vecPos[0].Position().m_y, vecPos[0].Position().m_z };

	setPosition(position);

	//std::cout << "Position: " << vecPos[0].Position().m_x << std::endl;
	//std::cout << "Position: " << vecPos[0].Position().m_y << std::endl;
	//std::cout << "Position: " << vecPos[0].Position().m_z << std::endl;
	//
	//std::cout << "Velocity: " << vecPos[0].Velocity().m_x << std::endl;
	//std::cout << "Velocity: " << vecPos[0].Velocity().m_y << std::endl;
	//std::cout << "Velocity: " << vecPos[0].Velocity().m_z << std::endl;
}
