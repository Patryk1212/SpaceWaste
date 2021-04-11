#include "pch.h"
#include "SingleUIWindow.h"

SingleUIWindow::SingleUIWindow(const UIWindowSpec& uiSpec)
    : specification(uiSpec)
{
    if (uiSpec.fixedPos) window_flags |= ImGuiWindowFlags_NoMove; 
    if (uiSpec.noMinimize) window_flags |= ImGuiWindowFlags_NoCollapse;
    if (uiSpec.noResize) window_flags |= ImGuiWindowFlags_NoResize;
    if (uiSpec.noTitleBar) window_flags |= ImGuiWindowFlags_NoTitleBar;
}
