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

	cEciTime eci = satSGP4->PositionEci(720);
	vector<cEci> vecPos;

	vecPos.push_back(eci);

	position = { vecPos[0].Position().m_x, vecPos[0].Position().m_z, vecPos[0].Position().m_y};
	position /= 10;

	//std::cout << position.x << std::endl;
	//std::cout << position.y << std::endl;
	//std::cout << position.z << std::endl;

	color = { 1.0f, 0.7f, 0.9f };
	calculateSize();
}

void SpaceObject::onUpdate(float deltaTime)
{
	speed += 1 * deltaTime;
	cEciTime eci = satSGP4->PositionEci(speed);
	cEci vecPos = eci;

	position = { vecPos.Position().m_x, vecPos.Position().m_z, vecPos.Position().m_y };
	position /= 10;
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

void SpaceObject::resize(float scalar)
{
	if (scale.x >= MIN_SIZE && scale.x <= MAX_SIZE)
	{
		scale *= scalar;

		if (scale.x >= MAX_SIZE)
		{
			scale.x = MAX_SIZE - 0.1f;
			scale.y = MAX_SIZE - 0.1f;
			scale.z = MAX_SIZE - 0.1f;
		}

		if (scale.x <= MIN_SIZE)
		{
			scale.x = MIN_SIZE + 0.1f;
			scale.y = MIN_SIZE + 0.1f;
			scale.z = MIN_SIZE + 0.1f;
		}
	}
}

void SpaceObject::calculateSize()
{
	float x = glm::distance({ .0f, .0f, .0f }, position);

	if (x < CLOSE) // close to earth
	{
		scale.x = MAX_SIZE_LOW;
		scale.y = MAX_SIZE_LOW;
		scale.z = MAX_SIZE_LOW;

		MIN_SIZE = MIN_SIZE_LOW;
		MAX_SIZE = MAX_SIZE_LOW;
	}
	else if (x < MID) // middle way
	{
		scale.x = MAX_SIZE_MIDDLE;
		scale.y = MAX_SIZE_MIDDLE;
		scale.z = MAX_SIZE_MIDDLE;

		MIN_SIZE = MIN_SIZE_MIDDLE;
		MAX_SIZE = MAX_SIZE_MIDDLE;
	}
	else if (x < FAR)// far away from earth
	{
		scale.x = MAX_SIZE_HIGH;
		scale.y = MAX_SIZE_HIGH;
		scale.z = MAX_SIZE_HIGH;

		MIN_SIZE = MIN_SIZE_HIGH;
		MAX_SIZE = MAX_SIZE_HIGH;
	}
	else
	{
		scale.x = SIZE_THE_FURTHEST;
		scale.y = SIZE_THE_FURTHEST;
		scale.z = SIZE_THE_FURTHEST;
	}
}
