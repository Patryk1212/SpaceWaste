#pragma once

#include <Engine.h>

#include "coreLib.h"
#include "orbitLib.h"

#include "core/FileLoader.h"
#include "core/SpaceObject.h"
//#include "spacetrack/SpaceTrackData.h"

class MainLayer : public Engine::Layer
{
public:
	MainLayer(const std::string& name) : Layer(name) {}

	virtual void onAttach() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onRender() override;
	virtual void passCamera(std::unique_ptr<Engine::CameraController>& cc) override;
	virtual bool onEvent(Engine::Event& event) override;

private:
	void updateObjectsPosition(float deltaTime);

private:
	void objectsResizeZoom(Engine::Event& event);
	const float ZOOM_IN = 0.95f;
	const float ZOOM_OUT = 1.05f;
	glm::vec3 final2;

private:
	//std::unique_ptr<CSpaceTrackDownload> data;

private:
	FileLoader fileLoader;
	std::unique_ptr<Engine::CameraController> cameraController;

private:
	std::vector<std::unique_ptr<Engine::Object>> spaceObjects;
	

	
	enum class SpaceObjectType
	{
		SPECIAL_INTREST_SAT = 0,
		WEATHER_RESOURCES_SAT,
		COMMUNICATION_SAT,
		NAVIGATION_SAT,
		SCIENTIFIC_SAT,
		MISCELLANEOUS_SAT
	};
	
	//std::unordered_map<glm::vec3, std::string> colorScheme;
};
