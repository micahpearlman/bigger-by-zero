#ifndef BIGGER_APP_HPP
#define BIGGER_APP_HPP

#include <bigg.hpp>
// #include <bigger/camera.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace bigger {
class SceneObject;

class App : public bigg::Application {
  public:
    App(const unsigned int width = 1280, const unsigned int height = 720)
        : bigg::Application("", width, height) {
        _time = 0.0f;
        _frame = 0;
    }

    int runApp(int argc, char **argv,
               bgfx::RendererType::Enum type = bgfx::RendererType::Count);

    // Events to be overridden
    virtual void updateApp() = 0;
    virtual void releaseSharedResources() = 0;

    // Events to be overridden, provided by bigg::Application
    virtual void initialize(int argc, char **argv) override = 0;
    virtual void onReset() override {}

    void setRect() {
        bgfx::setViewRect(0, 0, 0, uint16_t(getWidth()), uint16_t(getHeight()));
    }


    float aspect() const { return float(getWidth()) / float(getHeight()); }

    // const Camera &camera() const { return m_camera; }
    // Camera       &camera() { return m_camera; }

    void addSceneObject(std::shared_ptr<SceneObject> scene_object,
                        const std::string           &name = "");

  protected:
    unsigned int _frame;
    float        _time;
    float        _last_dt;
    std::unordered_map<std::string, std::shared_ptr<SceneObject>>
        _scene_objects;

  private:
    // Events provided by bigg::Application
    void update(float dt) override;
    int  shutdown() override;
};
} // namespace bigger

#endif // BIGGER_APP_HPP
