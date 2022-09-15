#include <bigger/primitives/dynamic-mesh-primitive.hpp>

bigger::DynamicMeshPrimitive::DynamicMeshPrimitive(const std::vector<PositionNormalUvVertex>& vertex_data,
                                                   const std::vector<uint16_t>&               triangle_list)
{
    _vertices      = vertex_data;
    _triangle_list = triangle_list;

    initializePrimitive();
}

void bigger::DynamicMeshPrimitive::initializePrimitive()
{
    assert(!_vertices.empty());
    assert(!_triangle_list.empty());

    const bgfx::VertexLayout vertex_layout = PositionNormalUvVertex::getVertexLayout();

    m_dynamic_vertex_buffer_handle = bgfx::createDynamicVertexBuffer(
        bgfx::makeRef(_vertices.data(), sizeof(PositionNormalUvVertex) * _vertices.size()),
        vertex_layout);
    _index_buffer_handle =
        bgfx::createIndexBuffer(bgfx::makeRef(_triangle_list.data(), sizeof(uint16_t) * _triangle_list.size()));

    _is_initialized = true;
}

void bigger::DynamicMeshPrimitive::submitPrimitive(bgfx::ProgramHandle program, bool preserve_state) const
{
    assert(_is_initialized);
    assert(!_vertices.empty());
    assert(!_triangle_list.empty());

    bgfx::update(m_dynamic_vertex_buffer_handle,
                 0,
                 bgfx::makeRef(_vertices.data(), sizeof(PositionNormalUvVertex) * _vertices.size()));

    bgfx::setVertexBuffer(0, m_dynamic_vertex_buffer_handle);
    bgfx::setIndexBuffer(_index_buffer_handle);

    bgfx::submit(0, program, bgfx::ViewMode::Default, preserve_state);
}

void bigger::DynamicMeshPrimitive::destroyPrimitive()
{
    assert(_is_initialized);
    assert(!_vertices.empty());
    assert(!_triangle_list.empty());

    bgfx::destroy(m_dynamic_vertex_buffer_handle);
    bgfx::destroy(_index_buffer_handle);
}

void bigger::DynamicMeshPrimitive::updateVertexData(const std::vector<PositionNormalUvVertex>& vertex_data)
{
    assert(_vertices.size() == vertex_data.size());

    _vertices = vertex_data;
}
