#ifndef BIGGER_APP_HPP
#define BIGGER_APP_HPP

#include <bigg.hpp>
#include <memory>
#include <string>
#include <list>

namespace bigger {
class SceneNode;

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
    virtual void renderApp() = 0;
    virtual void releaseSharedResources() = 0;

    // Events to be overridden, provided by bigg::Application
    virtual void initialize(int argc, char **argv) override = 0;
    virtual void onReset() override {}

    void setViewRect() {
        bgfx::setViewRect(0, 0, 0, uint16_t(getWidth()), uint16_t(getHeight()));
    }


    float aspect() const { return float(getWidth()) / float(getHeight()); }


    void addSceneNode(std::shared_ptr<SceneNode> scene_object);
    

  protected:
    unsigned int _frame;
    float        _time;
    float        _last_dt;
    std::list<std::shared_ptr<SceneNode>> _scene;

  private:
    // Events provided by bigg::Application
    void update(float dt) override;
    int  shutdown() override;
    void render(float dt) override;
};
} // namespace bigger

#endif // BIGGER_APP_HPP
