#pragma once
#include "entity sys/component.h"
#include "gl core/core shader.h"

namespace wizm {
    class directionallight_component : public lowlevelsys::core_component {
    public:
        directionallight_component(
            glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f),
            glm::vec3 diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f)
        );
        ~directionallight_component();

        void component_preupdate();
        void component_update();
        void component_postupdate();


        //////////////////////////////////////////////////
        //////////  SERIALIZATION METHOD /////////////////
        //////////////////////////////////////////////////


        void read_saved_data(std::string parent_name, std::string index) override {
            filedata::ZER save_;
            save_.read_file_cntx();

            set_position(glm::vec3(
                save_[parent_name][index]["transform"].get_float("position")[0],
                save_[parent_name][index]["transform"].get_float("position")[1],
                save_[parent_name][index]["transform"].get_float("position")[2]
            ));
            set_rotation(glm::vec3(
                save_[parent_name][index]["transform"].get_float("rotation")[0],
                save_[parent_name][index]["transform"].get_float("rotation")[1],
                save_[parent_name][index]["transform"].get_float("rotation")[2]
            ));
            set_scale(glm::vec3(
                save_[parent_name][index]["transform"].get_float("scale")[0],
                save_[parent_name][index]["transform"].get_float("scale")[1],
                save_[parent_name][index]["transform"].get_float("scale")[2]
            ));
        
            m_ambient = glm::vec3(save_[parent_name][index]["light"].get_float("m_ambient")[0],
                save_[parent_name][index]["light"].get_float("m_ambient")[1],
                save_[parent_name][index]["light"].get_float("m_ambient")[2]
            );

            m_diffuse = glm::vec3(save_[parent_name][index]["light"].get_float("m_diffuse")[0],
                save_[parent_name][index]["light"].get_float("m_diffuse")[1],
                save_[parent_name][index]["light"].get_float("m_diffuse")[2]
            );

            m_specular = glm::vec3(save_[parent_name][index]["light"].get_float("m_specular")[0],
                save_[parent_name][index]["light"].get_float("m_specular")[1],
                save_[parent_name][index]["light"].get_float("m_specular")[2]
            );
        
        };


        void save_data(std::string parent_name, std::string index) const override {

            filedata::ZER save_;
            save_.read_file_cntx();

            save_[parent_name]["directionallight" + index]["transform"].set_float("position", { get_position().x, get_position().y, get_position().z });
            save_[parent_name]["directionallight" + index]["transform"].set_float("rotation", { get_rotation().x, get_rotation().y, get_rotation().z });
            save_[parent_name]["directionallight" + index]["transform"].set_float("scale", { get_scale().x, get_scale().y, get_scale().z });

            save_[parent_name]["directionallight" + index]["light"].set_float("m_ambient", { m_ambient.x,m_ambient.y,m_ambient.z });
            save_[parent_name]["directionallight" + index]["light"].set_float("m_diffuse", { m_diffuse.x,m_diffuse.y,m_diffuse.z });
            save_[parent_name]["directionallight" + index]["light"].set_float("m_specular", { m_specular.x,m_specular.y,m_specular.z });


            save_.save_file(save_);


        }

    public:
        core_gl_shader* shader;

        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
    };
}