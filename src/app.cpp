#include <bigger/app.hpp>
#include <bigger/material.hpp>
#include <bigger/scene-node.hpp>
#include <bigger/screen-shot-callback.hpp>
#include <rand-util.hpp>
#include <stdexcept>

int bigger::App::runApp(int argc, char **argv, bgfx::RendererType::Enum type) {
    static ScreenShotCallback callback;
    return run(argc, argv, type, BGFX_PCI_ID_NONE, 0, &callback);
}

void bigger::App::addSceneNode(std::shared_ptr<SceneNode> node) {
    _scene.push_back(node);
}

void bigger::App::update(float dt) {
    // Update state variables
    _last_dt = dt;
    _time += dt;
    ++_frame;

    // Call the application-specific update method
    updateApp();

    // Update scene objects
    // TODO: go through recursively
    for (auto node : _scene) {
        if (node->isActive()) {
            node->update(dt);
        }
    }

    // draw UI
    // TODO: go through recursively
    for (auto node : _scene) {
        if (node->isActive()) {
            node->drawUI();
        }
    }

    // Prepare drawing

    setViewRect();
    bgfx::touch(0);

    // Draw scene objects
    // TODO: go through recursively
    for (auto node : _scene) {
        if (node->isActive() && node->isVisible()) {
            node->draw();
        }
    }
}

int bigger::App::shutdown() {
    // Release the scene objects
    _scene.clear();

    // Release the application-specific shared resources
    releaseSharedResources();

    return 0;
}
