#include <bigger/app.hpp>
#include <bigger/material.hpp>
#include <bigger/scene-node.hpp>
#include <bigger/screen-shot-callback.hpp>
#include <rand-util.hpp>
#include <stdexcept>
#include <stack>

int bigger::App::runApp(int argc, char **argv, bgfx::RendererType::Enum type) {
    static ScreenShotCallback callback;
    return run(argc, argv, type, BGFX_PCI_ID_NONE, 0, &callback);
}

void bigger::App::addSceneNode(std::shared_ptr<SceneNode> node) {
    _scene.push_back(node);
}

void bigger::App::render(float dt) {
    renderApp();
    // draw UI
    for (auto node : _scene) {
        if (node->isActive()) {
            std::stack<std::shared_ptr<SceneNode>> scene_stack;
            scene_stack.push(node);
            while (scene_stack.empty() == false) {
                std::shared_ptr<SceneNode> parent = scene_stack.top();
                scene_stack.pop();
                parent->drawUI();
                for (auto child : parent->children()) {
                    scene_stack.push(child);
                }
            }
        }
    }
    // Prepare drawing
    setViewRect();
    bgfx::touch(0);

    // Draw scene objects
    // TODO: concat matrices
    for (auto node : _scene) {
        if (node->isActive()) {
            std::stack<std::shared_ptr<SceneNode>> scene_stack;
            scene_stack.push(node);
            while (scene_stack.empty() == false) {
                std::shared_ptr<SceneNode> parent = scene_stack.top();
                scene_stack.pop();
                parent->draw();
                for (auto child : parent->children()) {
                    scene_stack.push(child);
                }
            }
        }
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
    std::stack<std::shared_ptr<SceneNode>> scene_stack;

    // update hierarchuy
    for (auto node : _scene) {
        if (node->isActive()) {
            std::stack<std::shared_ptr<SceneNode>> scene_stack;
            scene_stack.push(node);
            while (scene_stack.empty() == false) {
                std::shared_ptr<SceneNode> parent = scene_stack.top();
                scene_stack.pop();
                parent->update(dt);
                for (auto child : parent->children()) {
                    scene_stack.push(child);
                }
            }
        }
    }
}

int bigger::App::shutdown() {
    addRenderFunction([this](bigg::Application::Event &event) {
        // Release the scene objects
        _scene.clear();

        // Release the application-specific shared resources
        releaseSharedResources();
    });

    return 0;
}
