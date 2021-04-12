#pragma once

#include "SingleUIWindow.h"

class UIStandard : public SingleUIWindow
{
public:
	UIStandard(const UIWindowSpec& uiSpec, const std::vector<std::string>& text_);
	~UIStandard() = default;

	virtual void onUpdate() override;
	virtual void show(bool show) override;
	virtual int getValue() const override;
	virtual UIType getType() const override;

private:
	UIType type = UIType::STANDARD;

private:
	std::vector<std::string> content;
};
