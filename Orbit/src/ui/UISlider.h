#pragma once

#include "SingleUIWindow.h"

class UISlider : public SingleUIWindow
{
public:
	UISlider(const UIWindowSpec& uiSpec, const std::string& text_, int min_, int max_);
	UISlider(const UIWindowSpec& uiSpec, const std::string& text_, int min_, int max_, std::unique_ptr<UIButton>& button_);
	~UISlider() = default;

	virtual void onUpdate() override;
	
	virtual int getValue() const override;
	virtual UIType getType() const override;
	virtual bool isButtonClicked() const override;

	virtual void show(bool show) override;

private:
	UIType type = UIType::SLIDER;

private:
	std::unique_ptr<UIButton> button;
	std::string text;
	int value = 1;
	int min = 0;
	int max = 0;
};
