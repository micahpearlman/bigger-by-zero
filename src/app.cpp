#include <bigger/app.hpp>
#include <bigger/material.hpp>
#include <bigger/scene-object.hpp>
#include <bigger/screen-shot-callback.hpp>
#include <rand-util.hpp>
#include <stdexcept>

int bigger::App::runApp(int argc, char **argv, bgfx::RendererType::Enum type) {
    static ScreenShotCallback callback;
    return run(argc, argv, type, BGFX_PCI_ID_NONE, 0, &callback);
}

void bigger::App::addSceneObject(std::shared_ptr<SceneObject> scene_object,
                                 const std::string           &name) {
    if (name.empty()) {
        const std::string random_name = randutil::GenRandomString();
        _scene_objects[random_name] = scene_object;
    } else {
        const bool has_the_same_name_object =
            _scene_objects.find(name) != _scene_objects.end();
        if (has_the_same_name_object) {
            throw std::runtime_error("");
        }

        _scene_objects[name] = scene_object;
    }
}

void bigger::App::update(float dt) {
    // Update state variables
    _last_dt = dt;
    _time += dt;
    ++_frame;

    // Call the application-specific update method
    updateApp();

    // Update scene objects
    for (auto key_value : _scene_objects) {
        if (key_value.second->isActive()) {
            key_value.second->update(dt);
        }
    }

    // draw UI
    for (auto key_value : _scene_objects) {
        if (key_value.second->isActive()) {
            key_value.second->drawUI();
        }
    }

    // Prepare drawing

    setRect();
    bgfx::touch(0);

    // Draw scene objects
    for (auto key_value : _scene_objects) {
        if (key_value.second->isActive() && key_value.second->isVisible()) {
            key_value.second->draw();
        }
    }
}

int bigger::App::shutdown() {
    // Release the scene objects
    _scene_objects.clear();

    // Release the application-specific shared resources
    releaseSharedResources();

    return 0;
}
