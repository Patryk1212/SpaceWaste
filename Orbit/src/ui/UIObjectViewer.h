#pragma once

#include "SingleUIWindow.h"

class UIObjectViewer : public SingleUIWindow
{
public:
	UIObjectViewer(const UIWindowSpec& uiSpec, const std::vector<std::shared_ptr<Engine::Object>>& spaceObjectsHandle_) 
		: SingleUIWindow(uiSpec), spaceObjectsHandle(spaceObjectsHandle_) {}
	~UIObjectViewer() = default;

	virtual void onUpdate() override;

	//virtual int getValue() const override;
	//virtual UIType getType() const override;

private:
	UIType type = UIType::OBJECT_LIST;

private:
	std::vector<std::shared_ptr<Engine::Object>> spaceObjectsHandle;
};
