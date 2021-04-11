#pragma once

#include <Engine.h>

#include "ui/UISlider.h"
#include "ui/UIStandard.h"
#include "ui/UIButtonList.h"

class UILayer : public Engine::Layer
{
public:
	UILayer(const std::string& name) : Layer(name) {}

	virtual void onAttach() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onRender() override {}
	virtual void passCamera(std::unique_ptr<Engine::CameraController>& cc) override {}
	virtual bool onEvent(Engine::Event& event) override;

private:
	std::vector<std::unique_ptr<SingleUIWindow>> uiWindows;
	void initImGuiSettings();

private:
	void initSlider();
	void initControls();
	void initGeneralInfo();
	void initObjectList();
	void initMenu();
};
