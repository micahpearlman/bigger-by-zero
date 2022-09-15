#ifndef BIGGER_PRIMITIVE_HPP
#define BIGGER_PRIMITIVE_HPP

#include <bgfx/bgfx.h>
#include <cassert>
#include <glm/glm.hpp>
#include <vector>

namespace bigger {
struct PositionNormalUvVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;

    static bgfx::VertexLayout getVertexLayout() {
        bgfx::VertexLayout vertex_layout;
        vertex_layout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();
        return vertex_layout;
    }
};

class Primitive {
  public:
    Primitive() : _is_initialized(false) {}
    virtual ~Primitive() { destroyPrimitive(); }

    virtual void submitPrimitive(bgfx::ProgramHandle program,
                                 bool preserve_state = false) const {
        assert(_is_initialized);
        bgfx::setVertexBuffer(0, _vertex_buffer_handle);
        bgfx::setIndexBuffer(_index_buffer_handle);

        bgfx::submit(0, program, bgfx::ViewMode::Default, preserve_state);
    }

  protected:
    std::vector<PositionNormalUvVertex> _vertices;
    std::vector<uint16_t>               _triangle_list;

    bool _is_initialized;

    bgfx::VertexBufferHandle _vertex_buffer_handle;
    bgfx::IndexBufferHandle  _index_buffer_handle;

    virtual void initializePrimitive() {
        assert(!_vertices.empty());
        assert(!_triangle_list.empty());

        const bgfx::VertexLayout vertex_layout =
            PositionNormalUvVertex::getVertexLayout();

        _vertex_buffer_handle = bgfx::createVertexBuffer(
            bgfx::makeRef(_vertices.data(),
                          sizeof(PositionNormalUvVertex) * _vertices.size()),
            vertex_layout);
        _index_buffer_handle = bgfx::createIndexBuffer(bgfx::makeRef(
            _triangle_list.data(), sizeof(uint16_t) * _triangle_list.size()));

        _is_initialized = true;
    }

  private:
    virtual void destroyPrimitive() {
        assert(_is_initialized);

        if (bgfx::isValid(_vertex_buffer_handle)) {
            bgfx::destroy(_vertex_buffer_handle);
        }

        if (bgfx::isValid(_index_buffer_handle)) {
            bgfx::destroy(_index_buffer_handle);
        }
    }
};
} // namespace bigger

#endif // BIGGER_PRIMITIVE_HPP
