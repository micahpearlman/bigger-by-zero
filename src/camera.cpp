#include <bigger/camera.hpp>
#include <imgui.h>
#include <bgfx/bgfx.h>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>
namespace bigger {
class CameraImpl final : public Camera {
  public:
    CameraImpl(const std::string &name, int view_width, int view_height)
        : Camera(name), _view_width(view_width), _view_height(view_height) {}

    glm::mat4 viewMatrix() const override { return transform(); }
    glm::mat4 projectionMatrix() const override {
        return glm::perspective(glm::radians(fov()), aspect(), nearClip(),
                                farClip());
    }

    void setViewProj(bgfx::ViewId viewId) override {
        const glm::mat4 &view_matrix = viewMatrix();
        const glm::mat4 &proj_matrix = projectionMatrix();

        bgfx::setViewTransform(viewId, glm::value_ptr(view_matrix),
                               glm::value_ptr(proj_matrix));
    }

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

            // check if we are dragging the mouse with left button down outside
            // any window
            if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) == true &&
                ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) == false) {
                _is_mouse_look = true;
                ImVec2 mouse_delta =
                    ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
                ImVec2 delta = {mouse_delta.x - _last_mouse_delta.x,
                                mouse_delta.y - _last_mouse_delta.y};
                _last_mouse_delta = mouse_delta;

                float normalized_x = (float)delta.x / (float)_view_width;
                float normalized_y = (float)delta.y / (float)_view_height;
                _yaw += (normalized_x * _mouse_speed);
                _pitch += (normalized_y * _mouse_speed);

            } else {
                if (_is_mouse_look == true) {
                    _last_mouse_delta = {0, 0};
                }
                _is_mouse_look = false;
            }

            ImGui::SliderFloat("Roll", &_roll, -glm::pi<float>(),
                               glm::pi<float>());
            ImGui::SliderFloat("Pitch", &_pitch, -glm::pi<float>() * 0.5f,
                               glm::pi<float>() * 0.5f);
            ImGui::SliderFloat("Yaw", &_yaw, -glm::pi<float>(),
                               glm::pi<float>());

            if (ImGui::Button("Reset") == true) {
                _pitch = _yaw = 0;
            }

            _yaw = glm::clamp(_yaw, -glm::pi<float>(), glm::pi<float>());
            _pitch = glm::clamp(_pitch, -glm::pi<float>() * 0.5f,
                                glm::pi<float>() * 0.5f);
            _roll = glm::clamp(_roll, -glm::pi<float>(), glm::pi<float>());

            glm::mat4 yaw_mat = glm::rotate(glm::mat4(1), _yaw, {0, 1, 0});
            glm::vec3 right = glm::inverse(yaw_mat) * glm::vec4(1, 0, 0, 0);
            glm::mat4 pitch_mat = glm::rotate(glm::mat4(1), _pitch, right);
            glm::mat4 rotation = yaw_mat * pitch_mat;
            glm::vec3 forward = glm::inverse(rotation) * glm::vec4(0, 0, 1, 0);
            glm::mat4 roll_mat = glm::rotate(glm::mat4(1), _roll, forward);
            rotation = rotation * roll_mat;

            setRotationMatrix(rotation);

            ImGui::SliderFloat("FoV (Degree)", &_fov, 10.0f, 120.0f);
        }
        ImGui::End();
    }

    void update(float dt) override {}
    void draw(const glm::mat4 &parent_transform) override {
        setViewProj(_view_id);
    }
    void destroy() override {}

    bgfx::ViewId viewId() const override { return _view_id; }
    void         setViewId(bgfx::ViewId vid) override { _view_id = vid; };

  private:
    float _fov = 60.0f;
    float _near_clip = 0.1f;
    float _far_clip = 100.0f;

    int _view_width = 0;
    int _view_height = 0;

    float _roll = 0;
    float _pitch = 0;
    float _yaw = 0;

    ImVec2 _last_mouse_delta = {0, 0};
    float  _mouse_speed = 8.5f;
    bool   _is_mouse_look = false;

    bgfx::ViewId _view_id = 0;
};

std::shared_ptr<Camera> Camera::create(const std::string &name, int view_width,
                                       int view_height) {
    return std::make_shared<CameraImpl>(name, view_width, view_height);
}

} // namespace bigger
