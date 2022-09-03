#ifndef BIGGER_APP_HPP
#define BIGGER_APP_HPP

#include <bigg.hpp>
#include <bigger/camera.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace bigger
{
    class SceneObject;

    class App : public bigg::Application
    {
    public:
        App(const unsigned int width = 1280, const unsigned int height = 720) : bigg::Application("", width, height)
        {
            m_camera.setPosition(glm::vec3(1.0f, 1.0f, -2.0f));
            m_camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
            m_camera.setUp(glm::vec3(0.0f, 1.0f, 0.0f));

            m_time  = 0.0f;
            m_frame = 0;
        }

        int runApp(int argc, char** argv, bgfx::RendererType::Enum type = bgfx::RendererType::Count);

        // Events to be overridden
        virtual void updateApp()              = 0;
        virtual void releaseSharedResources() = 0;

        // Events to be overridden, provided by bigg::Application
        virtual void initialize(int argc, char** argv) override = 0;
        virtual void onReset() override {}

        void setRect() { bgfx::setViewRect(0, 0, 0, uint16_t(getWidth()), uint16_t(getHeight())); }

        void setViewProj()
        {
            const glm::mat4 view_matrix = m_camera.getViewMatrix();
            const glm::mat4 proj_matrix =
                glm::perspective(glm::radians(m_camera.fov()), getAspect(), m_camera.nearClip(), m_camera.farClip());

            bgfx::setViewTransform(0, glm::value_ptr(view_matrix), glm::value_ptr(proj_matrix));
        }

        float getAspect() const { return float(getWidth()) / float(getHeight()); }

        const Camera& camera() const { return m_camera; }
        Camera&       camera() { return m_camera; }

        unsigned int                                                  m_frame;
        float                                                         m_time;
        float                                                         m_last_dt;
        std::unordered_map<std::string, std::shared_ptr<SceneObject>> m_scene_objects;

        void addSceneObject(std::shared_ptr<SceneObject> scene_object, const std::string& name = "");

    private:
        // Events provided by bigg::Application
        void update(float dt) override;
        int  shutdown() override;

        Camera m_camera;
    };
} // namespace bigger

#endif // BIGGER_APP_HPP
