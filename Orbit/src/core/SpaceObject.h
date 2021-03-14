#pragma once

#include "renderer/Object.h"

#include "coreLib.h"
#include "orbitLib.h"

class SpaceObject : public Engine::Object
{
public:
	SpaceObject(std::string& name, std::string& one, std::string& two);
	~SpaceObject() = default;

	virtual std::string showName() const override;
	virtual std::string showFirstTLELine() const override;
	virtual std::string showSecondTLELine() const override;

private:
	glm::vec3 position;
	virtual void calcualateSpacePosition() override;

private:
	std::unique_ptr<cTle> tleSGP4;
	std::unique_ptr<cSatellite> satSGP4;
};