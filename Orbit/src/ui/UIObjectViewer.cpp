#include "pch.h"
#include "UIObjectViewer.h"

UIObjectViewer::UIObjectViewer(const UIWindowSpec& uiSpec, const std::vector<std::shared_ptr<Engine::Object>>& spaceObjectsHandle_)
    : SingleUIWindow(uiSpec), spaceObjectsHandle(spaceObjectsHandle_)
{
    debrisTypes.push_back("Debris");
    debrisTypes.push_back("Active");
    debrisTypes.push_back("Communication");
    debrisTypes.push_back("Weather & Earth Resources");
    debrisTypes.push_back("Navigation");
    debrisTypes.push_back("Special Intrest");
    debrisTypes.push_back("Scientific");
    debrisTypes.push_back("Space Station");
    debrisTypes.push_back("Other");
}

void UIObjectViewer::onUpdate()
{
    if (specification.open)
    {
        ImGui::SetNextWindowBgAlpha(specification.transparency);
        ImGui::SetNextWindowPos(specification.position);
        ImGui::SetNextWindowSize(specification.size);

        ImGui::Begin(specification.title.c_str());

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
        if (ImGui::BeginTable("split", 1))
        {
            for (int i = 0; i < numberOfDebrisTypes; i++)
            {
                displayObjectsEachType(debrisTypes[i].c_str(), i);
            }
            ImGui::EndTable();
        }
        ImGui::PopStyleVar();

        ImGui::End();

        if (detailsWindow)
        {
            ImVec2 pos(specification.position.x, specification.position.y + specification.size.y + 20);
            ImVec2 size(specification.size.x, 215.f);
            ImGui::SetNextWindowBgAlpha(specification.transparency);
            ImGui::SetNextWindowPos(pos);
            ImGui::SetNextWindowSize(size);

            ImGui::Begin("Details");

            ImGui::Separator();

            std::string name = "Name: " + spaceObjectsHandle[currentObject]->showName();
            ImGui::Text(name.c_str());

            std::string categoryN = "Category No.: " + spaceObjectsHandle[currentObject]->getCatalogNo();
            ImGui::Text(categoryN.c_str());

            std::string launchYear = "Launch Year: " + spaceObjectsHandle[currentObject]->getLaunchYear();
            ImGui::Text(launchYear.c_str());

            std::string launchNo = "Launch No. This Year: " + spaceObjectsHandle[currentObject]->getNumberOfLaunch();
            ImGui::Text(launchNo.c_str());

            ImGui::Separator();
            ImGui::Spacing();

            ImGui::PushID(0);
            if (ImGui::Button("Follow Object"))
            {
                selectedObject = currentObject;
                newObjectFocus = true;
            }
            ImGui::PopID();

            ImGui::PushID(1);
            if (ImGui::Button("    Reset    "))
            {
                selectedObject = 0;
                newObjectFocus = true;
            }
            ImGui::PopID();

            ImGui::PushID(2);
            if (ImGui::Button("    Close    "))
            {
                selectedObject = 0;
                currentObject = 0;
                newObjectFocus = true;
                detailsWindow = false;
            }
            ImGui::PopID();

            ImGui::End();
        }
    }
}

void UIObjectViewer::show(bool show)
{
    specification.open = show;
}

int UIObjectViewer::getValue() const
{
    return selectedObject;
}

bool UIObjectViewer::getBool() const
{
    return newObjectFocus;
}

void UIObjectViewer::setBool(bool value)
{
    newObjectFocus = value;
}

UIType UIObjectViewer::getType() const
{
    return type;
}

void UIObjectViewer::displayObjectsEachType(const char* prefix, int uid)
{
    ImGui::PushID(uid);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool node_open = ImGui::TreeNode(prefix);

    if (node_open)
    {
        int id = 0;
        int numberInVector = 0;
        for (const auto& object : spaceObjectsHandle)
        {
            if (object->getType() == (std::string)prefix)
            {
                ImGui::PushID(id);

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::AlignTextToFramePadding();
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;

                if (ImGui::Selectable(object->showName().c_str(), true))
                {
                    currentObject = numberInVector;
                    selectedObject = numberInVector;
                    detailsWindow = true;
                }

                ImGui::NextColumn();

                ImGui::PopID();
                id++;
            }

            numberInVector++;
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}