#include "pch.h"
#include "UIObjectViewer.h"

static void ShowPlaceholderObject(const char* prefix, int uid)
{
    ImGui::PushID(uid);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);

    if (node_open)
    {
        static float placeholder_members[8] = { 0.0f, 0.0f, 1.0f, 3.1416f, 100.0f, 999.0f };
        for (int i = 0; i < 8; i++)
        {
            ImGui::PushID(i); 

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
            
            if (ImGui::Selectable("Field", true))
            {
                std::cout << "obejct selected" << std::endl;
            }
            
            ImGui::NextColumn();

            ImGui::PopID();
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}

void UIObjectViewer::onUpdate()
{
    ImGui::Begin("Object List");

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
    if (ImGui::BeginTable("split", 1, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
    {
        for (int obj_i = 0; obj_i < 4; obj_i++)
        {
            ShowPlaceholderObject("Object", obj_i);
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();

    ImGui::End();
}