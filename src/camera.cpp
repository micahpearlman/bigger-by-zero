#include <bigger/camera.hpp>
#include <imgui.h>
#include <bgfx/bgfx.h>
#include <glm/gtx/euler_angles.hpp>

namespace bigger {
class CameraImpl final : public Camera {
  public:
    CameraImpl(const std::string& name, int view_width, int view_height)
        : Camera(name), _view_width(view_width), _view_height(view_height) {}

    glm::mat4 viewMatrix() const override { return transform(); }

    void setViewProj() override {
        const glm::mat4 &view_matrix = transform();
        const glm::mat4  proj_matrix = glm::perspective(
             glm::radians(fov()), aspect(), nearClip(), farClip());

        bgfx::setViewTransform(0, glm::value_ptr(view_matrix),
                               glm::value_ptr(proj_matrix));
    }

    // const glm::vec3 &position() const override { return _position; }
    // void             setPosition(const glm::vec3 &p) override { _position =
    // p; } const glm::vec3 &target() const override { return _target; } void
    // setTarget(const glm::vec3 &t) override { _target = t; } const glm::vec3
    // &up() const override { return _up; } void             setUp(const
    // glm::vec3 &u) override { _up = u; }
    float fov() const override { return _fov; }
    void  setFov(float f) override { _fov = f; }
    float nearClip() const override { return _near_clip; }
    void  setNearClip(float c) override { _near_clip = c; }
    float farClip() const override { return _far_clip; }
    void  setFarClip(float c) override { _far_clip = c; }
    float aspect() const override { return float(width()) / float(height()); }
    int   width() const override { return _view_width; }
    int   height() const override { return _view_height; }

    void drawUI() override {

        ImGui::Begin("Camera");
        {

            ImGui::Text("Camera Setting");
            float roll = 0, pitch = 0, yaw = 0;
            glm::extractEulerAngleYXZ(rotationMatrix(), yaw, pitch, roll);

            // ImGui::SliderFloat3("Position", glm::value_ptr(_position), -5.0f,
            //                     5.0f);
            // ImGui::SliderFloat3("Target", glm::value_ptr(_target),
            // -2.0f, 2.0f);

            ImGui::SliderFloat("Roll", &roll, -glm::pi<float>(),
                               glm::pi<float>());
            ImGui::SliderFloat("Pitch", &pitch, -glm::pi<float>(),
                               glm::pi<float>());
            ImGui::SliderFloat("Yaw", &yaw, -glm::pi<float>(),
                               glm::pi<float>());

            glm::mat4 rotation = glm::eulerAngleYXZ(yaw, pitch, roll);
            setRotationMatrix(rotation);

            ImGui::SliderFloat("FoV (Degree)", &_fov, 10.0f, 120.0f);
        }
        ImGui::End();
    }

    void update(float dt) override { setViewProj(); }
    void draw(const glm::mat4 &parent_transform) override {}
    void destroy() override {}

  private:
    // glm::vec3 _position = glm::vec3(1.0f, 1.0f, -2.0f);
    // glm::vec3 _target = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);

    float _fov = 60.0f;
    float _near_clip = 0.1f;
    float _far_clip = 100.0f;

    int _view_width = 0;
    int _view_height = 0;
};

std::shared_ptr<Camera> Camera::create(const std::string& name, int view_width, int view_height) {
    return std::make_shared<CameraImpl>(name, view_width, view_height);
}

} // namespace bigger
