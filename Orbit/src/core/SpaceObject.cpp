#include "pch.h"
#include "SpaceObject.h"

SpaceObject::SpaceObject(const glm::vec3& pos_, const glm::vec3& scale_, const glm::vec3& color_)
{
	position = pos_;
	scale = scale_;
	color = color_;
}

SpaceObject::SpaceObject(std::string& name, std::string& one, std::string& two, const std::string& colorType)
{
	tleSGP4 = std::make_unique<cTle>(name, one, two);
	satSGP4 = std::make_unique<cSatellite>(*tleSGP4.get());

	/* position */
	cEciTime eci = satSGP4->PositionEci(650);
	cEci vecPos = eci;

	position = { vecPos.Position().m_x, vecPos.Position().m_z, vecPos.Position().m_y};
	position /= 10;

	/* velocity */
	velocity.x = vecPos.Velocity().m_x;
	velocity.y = vecPos.Velocity().m_z;
	velocity.z = vecPos.Velocity().m_y;

	setApropiateColor(colorType);
	calculateSize();
}

void SpaceObject::onUpdate(float deltaTime, int visSpeed_)
{
	//speed += 1 * deltaTime;
	//cEciTime eci = satSGP4->PositionEci(speed);
	//cEci vecPos = eci;

	position.x += velocity.x * deltaTime * (((float)visSpeed_)/speed);
	position.z += velocity.z * deltaTime * (((float)visSpeed_)/speed);
	position.y += velocity.y * deltaTime * (((float)visSpeed_)/speed);

	//std::cout << position.x << position.y << position.z << std::endl;
	//position = { vecPos.Position().m_x, vecPos.Position().m_z, vecPos.Position().m_y };
	//position /= 10;
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

void SpaceObject::setApropiateColor(const std::string& colorType)
{
	if (colorType.size() == 1)
	{
		switch (colorType[0])
		{
			case 'D': // Debris
			{
				color = { .75f, .75f, .75f }; // white
				break;
			}
			case 'A': // Active Sat
			{
				color = { .0f, 0.48f, 1.0f }; // light blue
				break;
			}
			case 'C': // Communication Sat
			{
				color = { 1.0f, 1.f, .0f }; // yellow
				break;
			}
			case 'W': // Weather and Earth Resources Sat
			{
				color = { .4f, 0.2f, .0f }; // brown
				break;
			}
			case 'N': // Navigation Sat
			{
				color = { .0f, 0.8f, .0f }; // green
				break;
			}
			case 'O': // Others
			{
				color = { .7f, .2f, .2f }; // red
				break;
			}
			default: color = { 1.0f, 0.5f, 1.0f }; break;
		}
	}
	else if (colorType.size() == 2)
	{
		switch (colorType[1])
		{
			case 'I': // Special Intrest
			{
				color = { .0f, 0.6f, 0.6f }; // dark blue
				break;
			}
			case 'A': // Scientific Sat
			{
				color = { .69f, 0.4f, 1.f }; // purple
				break;
			}
			case 'S': // Space Stations
			{
				color = { 1.0f, 0.5f, 0.0f }; // orange
				break;
			}
			default: color = { 1.0f, 0.5f, 1.0f }; break;
		}
	}
}
