#ifndef BIGGER_SCENE_OBJECT_HPP
#define BIGGER_SCENE_OBJECT_HPP

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <list>
#include <memory>
#include <string>
#include <functional>

namespace bigger {

class SceneNode {
  public:
    virtual void update(float dt) = 0;
    virtual void
    draw(const glm::mat4 &parent_transform_matrix = glm::mat4(1.0f)) = 0;
    virtual void drawUI() = 0;

    virtual void postRender() {}

    glm::mat4 transform() const {
        return _translate_matrix * _rotate_matrix * _scale_matrix;
    }
    virtual void setRotationMatrix(const glm::mat4 &m) { _rotate_matrix = m; }
    virtual const glm::mat4 &rotationMatrix() const { return _rotate_matrix; }
    virtual void setScaleMatrix(const glm::mat4 &m) { _scale_matrix = m; }
    virtual void setTranslateMatrix(const glm::mat4 &m) {
        _translate_matrix = m;
    }
    virtual void setPosition(const glm::vec3 &pos) {
        _translate_matrix = glm::translate(_translate_matrix, pos);
    }
    virtual glm::vec3 position() const {
        return glm::vec3(_translate_matrix[3]);
    }
    virtual bool isActive() { return _is_active; }
    virtual bool isVisible() { return _is_visible; }
    virtual void addChild(std::shared_ptr<SceneNode> child) {
        _children.push_back(child);
        _children.unique(); // remove any duplicates
    }
    virtual void removeChild(std::shared_ptr<SceneNode> child) {
        std::remove(_children.begin(), _children.end(), child);
    }

    std::list<std::shared_ptr<SceneNode>> &children() { return _children; }

    virtual void destroy() = 0;

    const std::string &name() const { return _name; }

    bool isDrawUI() const { return _is_draw_ui; }
    void setDrawUI(bool draw_ui) { _is_draw_ui = draw_ui; }

  protected:
    SceneNode(const std::string &name) : _name(name) {}

    glm::mat4 _rotate_matrix = glm::mat4(1.0f);
    glm::mat4 _scale_matrix = glm::mat4(1.0f);
    glm::mat4 _translate_matrix = glm::mat4(1.0f);

    bool _is_active = true;
    bool _is_visible = true;
    bool _is_draw_ui = true;

    std::list<std::shared_ptr<SceneNode>> _children;

    std::string _name;
};
} // namespace bigger

#endif // BIGGER_SCENE_OBJECT_HPP
