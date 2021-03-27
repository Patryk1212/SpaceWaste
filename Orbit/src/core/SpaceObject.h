#pragma once

#include "coreLib.h"
#include "orbitLib.h"

#include "renderer/Object.h"
#include "ObjectConstVar.h"

class SpaceObject : public Engine::Object
{
public:
	SpaceObject() = default;
	SpaceObject(const glm::vec3& pos_, const glm::vec3& scale_, const glm::vec3& color_);
	SpaceObject(std::string& name, std::string& one, std::string& two);
	~SpaceObject() = default;

	virtual std::string showName() const override;
	virtual std::string showFirstTLELine() const override;
	virtual std::string showSecondTLELine() const override;

	virtual inline glm::vec3 getPos() const override { return position; }
	virtual inline glm::vec3 getScale() const override { return scale; }
	virtual inline glm::vec3 getColor() const override { return color; }
	virtual inline float getRotation()  const override { return rotation; }

	virtual inline void setPos(const glm::vec3& pos_) override { position = pos_; }
	virtual inline void setScale(const glm::vec3& scale_) override { scale = scale_; }
	virtual void resize(float scalar) override;
	virtual inline void setColor(const glm::vec3& color_) override { color = color_; }
	virtual inline void setRotation(float rot) override { rotation = rot; }

	virtual bool checkInside(const glm::vec3& point) override
	{
		glm::vec3 min{ position.x - scale.x / 2, position.y - scale.y / 2, position.z + scale.z / 2 };
		glm::vec3 max{ position.x + scale.x / 2, position.y + scale.y / 2, position.z - scale.z / 2 };

		return (point.x >= min.x && point.x <= max.x) &&
			(point.y >= min.y && point.y <= max.y);//&&
			   //(point.z >= min.z && point.z <= max.z);

	};

private:
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 3.0f, 3.0f, 3.0f };
	glm::vec3 color = { 1.0f, 1.0f, 1.0f };
	float rotation = 0.0f;

private:
	float MIN_SIZE = 0.f;
	float MAX_SIZE = 0.f;
	void calculateSize();

private:
	std::unique_ptr<cTle> tleSGP4;
	std::unique_ptr<cSatellite> satSGP4;
};
