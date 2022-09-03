#ifndef BIGGER_CAMERA_HPP
#define BIGGER_CAMERA_HPP

#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace bigger
{
    class Camera
    {
    public:
        glm::mat4 getViewMatrix() const { return glm::lookAt(m_position, m_target, m_up); }

        void drawImgui();

        const glm::vec3& position() {
            return m_position;
        }
        void setPosition(const glm::vec3& p) {
            m_position = p;
        }
        const glm::vec3& target() {
            return m_target;
        }
        void setTarget(const glm::vec3& t) {
            m_target = t;
        }
        const glm::vec3& up() {
            return m_up;
        }
        void setUp(const glm::vec3& u) {
            m_up = u;
        }
        float fov() {
            return m_fov;
        }
        void setFov(float f) {
            m_fov = f;
        }
        float nearClip() {
            return m_near_clip;
        }
        void setNearClip(float c) {
            m_near_clip = c;
        }
        float farClip() {
            return m_far_clip;
        }
        void setFarClip(float c) {
            m_far_clip = c;
        }

    private:
        glm::vec3 m_position = glm::vec3(1.0f, 1.0f, -2.0f);
        glm::vec3 m_target   = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_up       = glm::vec3(0.0f, 1.0f, 0.0f);

        float m_fov       = 60.0f;
        float m_near_clip = 0.1f;
        float m_far_clip  = 100.0f;
    };
} // namespace bigger

#endif // BIGGER_CAMERA_HPP
