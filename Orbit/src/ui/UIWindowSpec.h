#pragma once

#include <Engine.h>

#include "UIEnums.h"

struct UIWindowSpec
{
    UIWindowInstance type = UIWindowInstance::NONE;
    std::string title = "test";
    ImVec2 position{ 0.f, 0.f };
    ImVec2 size{ 0.f, 0.f };
    float transparency = 1.f;
    bool fixedPos = false;
    bool noResize = false;
    bool noTitleBar = false;
    bool noMinimize = false;
    bool open = true;

    UIWindowSpec(const UIWindowInstance& type_, const std::string& title_, const ImVec2& pos, const ImVec2& size_)
        : type(type_), title(title_), position(pos), size(size_) {}

    UIWindowSpec(const UIWindowInstance& type_, const std::string& title_, const ImVec2& pos, const ImVec2& size_, float transparency_)
        : type(type_), title(title_), position(pos), size(size_), transparency(transparency_) {}

    UIWindowSpec(const UIWindowInstance& type_, const std::string& title_, const ImVec2& pos, const ImVec2& size_, float transparency_, bool fixedPos_,
        bool noResize_, bool noTitleBar_, bool noMinimize_)
        : type(type_), title(title_), position(pos), size(size_), transparency(transparency_), fixedPos(fixedPos_),
        noResize(noResize_), noTitleBar(noTitleBar_), noMinimize(noMinimize_) {}
};