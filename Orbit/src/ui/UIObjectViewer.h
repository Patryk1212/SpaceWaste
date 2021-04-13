#pragma once

#include "SingleUIWindow.h"

class UIObjectViewer : public SingleUIWindow
{
public:
	UIObjectViewer(const UIWindowSpec& uiSpec, const std::vector<std::shared_ptr<Engine::Object>>& spaceObjectsHandle_);
	~UIObjectViewer() = default;

	virtual void onUpdate() override;

	virtual void show(bool show) override;
	virtual int getValue() const override;
	virtual bool getBool() const override;
	virtual void setBool(bool value) override;
	virtual UIType getType() const override;

private:
	UIType type = UIType::OBJECT_LIST;
	void displayObjectsEachType(const char* prefix, int uid);

private:
	bool newObjectFocus = false;
	int currentObject = 0;
	int selectedObject = 0;
	bool detailsWindow = false;

private:
	const int numberOfDebrisTypes = 9;
	std::vector<std::string> debrisTypes;
	std::vector<std::shared_ptr<Engine::Object>> spaceObjectsHandle;
};
