#pragma once

#include "SingleUIWindow.h"

class UIButtonList : public SingleUIWindow
{
public:
	UIButtonList(const UIWindowSpec& uiSpec, const std::vector<UIButton>& buttons);
	~UIButtonList() = default;

	virtual void onUpdate() override;

	virtual void show(bool show) override;
	virtual float getValue() const override;
	virtual UIType getType() const override;

	virtual std::vector<UIButton> getButtons() const override;

private:
	UIType type = UIType::BUTTON_LIST;

private:
	std::vector<UIButton> content;
};
