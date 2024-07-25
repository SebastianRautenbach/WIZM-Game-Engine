#include "layers/project_modifiers_layer.h"
#include "scene.h"

wizm::project_modifier::project_modifier(core_scene* scene)
	:m_scene(scene)
{
}

wizm::project_modifier::~project_modifier()
{
}

void wizm::project_modifier::OnAttach()
{
}

void wizm::project_modifier::OnDetach()
{
}

void wizm::project_modifier::update(float delta_time)
{
    static bool show_save_popup = false;
    static char map_name[128] = "";


	ImGui::Begin("file");

    if (ImGui::Button("Save")) {
        show_save_popup = true;
    }

    if (show_save_popup) {
        ImGui::OpenPopup("Save Map As");
    }

    if (ImGui::BeginPopupModal("Save Map As", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Enter the map name:");
        ImGui::InputText("##map_name", map_name, IM_ARRAYSIZE(map_name));

        if (ImGui::Button("OK", ImVec2(120, 0))) {
            
            std::string new_map_name = map_name;

            if (new_map_name.size() > 3) {
                new_map_name = "GAME/";
                new_map_name += map_name;
                new_map_name += ".zer";

                m_scene->save_map_data(new_map_name);

                show_save_popup = false;
            }

            

            
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            show_save_popup = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

	ImGui::End();
}
