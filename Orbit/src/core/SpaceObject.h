#pragma once

#include "coreLib.h"
#include "orbitLib.h"

#include "renderer/Object.h"
#include "ObjectConstVar.h"

//enum class SpaceObjectType
//{
//	DEBRIS = 0,
//	ACTIVE_SAT,
//	COMMUNICATION_SAT,
//	SPECIAL_INTREST_SAT,
//	WEATHER_RESOURCES_SAT,
//	NAVIGATION_SAT,
//	SCIENTIFIC_SAT,
//	SPACE_STATIONS,
//	OTHER
//};

class SpaceObject : public Engine::Object
{
public:
	SpaceObject() = default;
	SpaceObject(const glm::vec3& pos_, const glm::vec3& scale_, const glm::vec3& color_);
	SpaceObject(std::string& name, std::string& one, std::string& two, const std::string& colorType, int id_);
	~SpaceObject() = default;

	virtual void onUpdate(float deltaTime, int visSpeed_) override;

	virtual std::string showName() const override;
	virtual std::string showFirstTLELine() const override;
	virtual std::string showSecondTLELine() const override;

	virtual inline glm::vec3 getPos() const override { return position; }
	virtual inline glm::vec3 getScale() const override { return scale; }
	virtual inline glm::vec3 getColor() const override { return color; }

	virtual inline std::string getType() const override { return type; }
	virtual inline std::string getCatalogNo() const override { return catalogNumber; }
	virtual inline std::string getLaunchYear() const override { return launchYear; }
	virtual inline std::string getNumberOfLaunch() const override { return launchNumberOfTheYear; }

	virtual inline void setPos(const glm::vec3& pos_) override { position = pos_; }
	virtual inline void setScale(const glm::vec3& scale_) override { scale = scale_; }
	virtual void resize(float scalar) override;
	virtual inline void setColor(const glm::vec3& color_) override { color = color_; }

	/* test */
	virtual bool checkInside(const glm::vec3& point) override
	{
		glm::vec3 min{ position.x - scale.x , position.y - scale.y , position.z - scale.z };
		glm::vec3 max{ position.x + scale.x , position.y + scale.y , position.z + scale.z };

		return (point.x >= min.y && point.x <= max.y) &&
			(point.y >= min.z && point.y <= max.z);//&&
			   //(point.z >= min.z && point.z <= max.z);
	};

private:
	const float speed = 10.f;
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 3.0f, 3.0f, 3.0f };
	glm::vec3 color = { 1.0f, 0.5f, 1.0f };
	glm::vec3 velocity = { 0.f, 0.f, 0.f };

private:
	float MIN_SIZE = 0.f;
	float MAX_SIZE = 0.f;
	void calculateSize();

private:
	void setDisplayableData();
	void setApropiateColorAndType(const std::string& colorType);
	
	std::string type;
	std::string catalogNumber;
	std::string launchYear;
	std::string launchNumberOfTheYear;
	int unique_id = 0;

private:
	std::string name;
	std::string firstLine;
	std::string secondLine;

	std::unique_ptr<cTle> tleSGP4;
	std::unique_ptr<cSatellite> satSGP4;
};
