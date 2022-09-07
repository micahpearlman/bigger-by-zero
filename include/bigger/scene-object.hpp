#ifndef BIGGER_SCENE_OBJECT_HPP
#define BIGGER_SCENE_OBJECT_HPP

#include <glm/glm.hpp>
#include <list>
#include <memory>

namespace bigger {

class SceneObject {
  public:
    virtual void update(float dt) {
        for (auto &child : _children) {
            child->update(dt);
        }
    }
    virtual void
    draw(const glm::mat4 &parent_transform_matrix = glm::mat4(1.0f)) {
        for (auto &child : _children) {
            child->draw(transform());
        }
    }

    virtual void drawUI() {
        for (auto &child : _children) {
            child->drawUI();
        }
    }

    glm::mat4 transform() const {
        return _translate_matrix * _rotate_matrix * _scale_matrix;
    }
    virtual void setRotationMatrix(const glm::mat4 &m) { _rotate_matrix = m; }
    virtual void setScaleMatrix(const glm::mat4 &m) { _scale_matrix = m; }
    virtual void setTranslateMatrix(const glm::mat4 &m) {
        _translate_matrix = m;
    }

    virtual bool isActive() { return _is_active; }
    virtual bool isVisible() { return _is_visible; }
    virtual void addChild(std::shared_ptr<SceneObject> child) {
        _children.push_back(child);
        _children.unique(); // remove any duplicates
    }
    virtual void removeChild(std::shared_ptr<SceneObject> child) {
        std::find(_children.begin(), _children.end(), child);
    }

    virtual void destroy() {
        for (auto &child : _children) {
            child->destroy();
        }
    }

  protected:
    SceneObject() = default;

    glm::mat4 _rotate_matrix = glm::mat4(1.0f);
    glm::mat4 _scale_matrix = glm::mat4(1.0f);
    glm::mat4 _translate_matrix = glm::mat4(1.0f);

    bool _is_active = true;
    bool _is_visible = true;

    std::list<std::shared_ptr<SceneObject>> _children;
};
} // namespace bigger

#endif // BIGGER_SCENE_OBJECT_HPP
