#pragma once

#include <Engine.h>

class MainLayer : public Engine::Layer
{
public:
	MainLayer(const std::string& name) : Layer(name) {}

	virtual void onAttach() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onRender() override;
	virtual bool onEvent(Engine::Event& event) override;

	std::unique_ptr<Engine::Camera>& getCamera();

public:

private:
	Engine::CameraController cameraController;
};