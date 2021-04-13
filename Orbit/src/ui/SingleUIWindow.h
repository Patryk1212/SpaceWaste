#pragma once

#include "UIWindowSpec.h"
#include "UIBUtton.h"

class SingleUIWindow
{
public:
	SingleUIWindow(const UIWindowSpec& uiSpec);
	virtual ~SingleUIWindow() = default;

    /* for all classes that inherit */
    virtual void onUpdate() {}
    virtual UIWindowInstance getInstanceType() const { return specification.type; }
    
    /* class implementation specific */
    virtual void show(bool show) {}
    virtual int getValue() const { return 0.f; }
    virtual UIType getType() const { return UIType::NONE; }
    virtual bool isButtonClicked() const { return false; }

public:
    virtual std::vector<UIButton> getButtons() const { std::vector<UIButton> empty; return empty; }

protected:
    ImGuiWindowFlags window_flags = 0;
    UIWindowSpec specification;
};