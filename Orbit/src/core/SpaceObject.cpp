#include "pch.h"
#include "SpaceObject.h"

SpaceObject::SpaceObject(const glm::vec3& pos_, const glm::vec3& scale_, const glm::vec3& color_)
{
	position = pos_;
	scale = scale_;
	color = color_;
}

SpaceObject::SpaceObject(std::string& name, std::string& one, std::string& two, const std::string& colorType, int id_)
	: name(name), firstLine(one), secondLine(two), unique_id(id_)
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

	/* other data */
	setDisplayableData();
	setApropiateColorAndType(colorType);
	calculateSize();
}

void SpaceObject::onUpdate(float deltaTime, int visSpeed_)
{
	position.x += velocity.x * deltaTime * (((float)visSpeed_) / speed);
	position.z += velocity.z * deltaTime * (((float)visSpeed_) / speed);
	position.y += velocity.y * deltaTime * (((float)visSpeed_) / speed);
}

std::string SpaceObject::showName() const
{
	return name;
}

std::string SpaceObject::showFirstTLELine() const
{
	return firstLine;
}

std::string SpaceObject::showSecondTLELine() const
{
	return secondLine;
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
	float tempDis = glm::distance({ .0f, .0f, .0f }, position);

	if (tempDis < CLOSE) // close to earth
	{
		scale.x = MAX_SIZE_LOW;
		scale.y = MAX_SIZE_LOW;
		scale.z = MAX_SIZE_LOW;

		MIN_SIZE = MIN_SIZE_LOW;
		MAX_SIZE = MAX_SIZE_LOW;
	}
	else if (tempDis < MID) // middle way
	{
		scale.x = MAX_SIZE_MIDDLE;
		scale.y = MAX_SIZE_MIDDLE;
		scale.z = MAX_SIZE_MIDDLE;

		MIN_SIZE = MIN_SIZE_MIDDLE;
		MAX_SIZE = MAX_SIZE_MIDDLE;
	}
	else if (tempDis < FAR)// far away from earth
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

void SpaceObject::setDisplayableData()
{
	for (int i = 3; i <= 7; i++)
	{
		catalogNumber += firstLine[i];
	}

	for (int i = 10; i <= 11; i++)
	{
		launchYear += firstLine[i];
	}

	for (int i = 12; i <= 14; i++)
	{
		launchNumberOfTheYear += firstLine[i];
	}
}

void SpaceObject::setApropiateColorAndType(const std::string& colorType)
{
	if (colorType.size() == 1)
	{
		switch (colorType[0])
		{
			case 'D':
			{
				type = "Debris";
				color = { .75f, .75f, .75f }; // white
				break;
			}
			case 'A':
			{
				type = "Active";
				color = { .0f, 0.48f, 1.0f }; // light blue
				break;
			}
			case 'C':
			{
				type = "Communication";
				color = { 1.0f, 1.f, .0f }; // yellow
				break;
			}
			case 'W':
			{
				type = "Weather & Earth Resources";
				color = { .4f, 0.2f, .0f }; // brown
				break;
			}
			case 'N':
			{
				type = "Navigation";
				color = { .0f, 0.8f, .0f }; // green
				break;
			}
			case 'O':
			{
				type = "Other";
				color = { .7f, .2f, .2f }; // red
				break;
			}
		}
	}
	else if (colorType.size() == 2)
	{
		switch (colorType[1])
		{
			case 'I':
			{
				type = "Special Intrest";
				color = { .0f, 0.6f, 0.6f }; // dark blue
				break;
			}
			case 'A':
			{
				type = "Scientific";
				color = { .69f, 0.4f, 1.f }; // purple
				break;
			}
			case 'S':
			{
				type = "Space Station";
				color = { 1.0f, 0.5f, 0.0f }; // orange
				break;
			}
		}
	}
}
