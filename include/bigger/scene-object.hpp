#ifndef BIGGER_SCENE_OBJECT_HPP
#define BIGGER_SCENE_OBJECT_HPP

#include <glm/glm.hpp>
#include <memory>

namespace bigger
{
    class Material;

    class SceneObject
    {
    public:
        SceneObject() {}

        virtual void update(float dt) {}
        virtual void draw(const glm::mat4& parent_transform_matrix = glm::mat4(1.0f)) {}

        glm::mat4 transform() const { return m_translate_matrix * m_rotate_matrix * m_scale_matrix; }
        void setRotationMatrix(const glm::mat4& m) {
            m_rotate_matrix = m;
        }
        void setScaleMatrix(const glm::mat4& m) {
            m_scale_matrix = m;
        }
        void setTranslateMatrix(const glm::mat4& m) {
            m_translate_matrix = m;
        }

        bool isActive() {
            return m_is_active;
        }
        bool isVisible() {
            return m_is_visible;
        }

        

    protected:
        glm::mat4 m_rotate_matrix    = glm::mat4(1.0f);
        glm::mat4 m_scale_matrix     = glm::mat4(1.0f);
        glm::mat4 m_translate_matrix = glm::mat4(1.0f);

        bool m_is_active  = true;
        bool m_is_visible = true;

    };
} // namespace bigger

#endif // BIGGER_SCENE_OBJECT_HPP
