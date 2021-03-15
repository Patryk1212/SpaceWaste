#pragma once

#include <Engine.h>

class UILayer : public Engine::Layer
{
public:
	UILayer(const std::string& name) : Layer(name) {}

	virtual void onAttach() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onRender() override;
	virtual void passCamera(std::unique_ptr<Engine::CameraController>& cc) override;
	virtual bool onEvent(Engine::Event& event) override;

private:


};