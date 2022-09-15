#ifndef BIGGER_SPHERE_PRIMITIVE_HPP
#define BIGGER_SPHERE_PRIMITIVE_HPP

#include <bigger/primitive.hpp>
#include <glm/ext.hpp>

namespace bigger
{
    class SpherePrimitive : public Primitive
    {
    public:
        SpherePrimitive()
        {
            constexpr float pi                   = glm::pi<float>();
            constexpr int   latitude_resolution  = 20;
            constexpr int   longitude_resolution = 30;

            _vertices.resize(latitude_resolution * longitude_resolution * 6);
            _triangle_list.resize(latitude_resolution * longitude_resolution * 6);

            for (int i = 0; i < longitude_resolution; ++i)
            {
                const float theta_xy_1 =
                    2.0 * static_cast<float>(i + 0) * pi / static_cast<float>(longitude_resolution);
                const float theta_xy_2 =
                    2.0 * static_cast<float>(i + 1) * pi / static_cast<float>(longitude_resolution);
                const float x_1 = std::cos(theta_xy_1);
                const float x_2 = std::cos(theta_xy_2);
                const float y_1 = std::sin(theta_xy_1);
                const float y_2 = std::sin(theta_xy_2);

                for (int j = 0; j < latitude_resolution; ++j)
                {
                    const float theta_z_1 = static_cast<float>(j + 0) * pi / static_cast<float>(latitude_resolution);
                    const float theta_z_2 = static_cast<float>(j + 1) * pi / static_cast<float>(latitude_resolution);
                    const float cos_1     = std::cos(theta_z_1);
                    const float cos_2     = std::cos(theta_z_2);
                    const float sin_1     = std::sin(theta_z_1);
                    const float sin_2     = std::sin(theta_z_2);

                    const int offset = i * latitude_resolution * 6 + j * 6;

                    const glm::vec3 vertex_0 = {sin_2 * x_1, sin_2 * y_1, cos_2};
                    const glm::vec3 vertex_1 = {sin_2 * x_2, sin_2 * y_2, cos_2};
                    const glm::vec3 vertex_2 = {sin_1 * x_2, sin_1 * y_2, cos_1};
                    const glm::vec3 vertex_3 = {sin_2 * x_1, sin_2 * y_1, cos_2};
                    const glm::vec3 vertex_4 = {sin_1 * x_2, sin_1 * y_2, cos_1};
                    const glm::vec3 vertex_5 = {sin_1 * x_1, sin_1 * y_1, cos_1};

                    _vertices[offset + 0] = {vertex_0, vertex_0};
                    _vertices[offset + 1] = {vertex_1, vertex_1};
                    _vertices[offset + 2] = {vertex_2, vertex_2};
                    _vertices[offset + 3] = {vertex_3, vertex_3};
                    _vertices[offset + 4] = {vertex_4, vertex_4};
                    _vertices[offset + 5] = {vertex_5, vertex_5};
                }
            }

            for (int i = 0; i < _triangle_list.size(); ++i)
            {
                _triangle_list[i] = static_cast<uint16_t>(i);
            }

            Primitive::initializePrimitive();
        }
    };
} // namespace bigger

#endif // BIGGER_SPHERE_PRIMITIVE_HPP
