#ifndef BIGGER_UTILS_HPP
#define BIGGER_UTILS_HPP

#include <bgfx/bgfx.h>
#include <string>

namespace bigger
{
    std::string getShaderDirectoryPath(const bgfx::RendererType::Enum renderer_type);
    void setShaderDirectoryPathPrefix(const std::string& prefix);

    /// \brief Load texture data from a texture image file.
    /// \details This is a wrapper function for using utility functions in bgfx's examples.
    /// \param file_path A file path to the texture image data.
    bgfx::TextureHandle loadTexture(const std::string& texture_path, bgfx::TextureInfo* info = nullptr);
} // namespace bigger

#endif // BIGGER_UTILS_HPP
