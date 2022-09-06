#ifndef BIGGER_MATERIAL_HPP
#define BIGGER_MATERIAL_HPP

#include <bigg.hpp>
#include <bigger/utils.hpp>
#include <string>

namespace bigger {
class Material {
  public:
    Material(const std::string &shader_name) {
        const std::string shader_dir_path =
            getShaderDirectoryPath(bgfx::getRendererType());
        const std::string vs_path =
            shader_dir_path + "/" + "vs_" + shader_name + ".bin";
        const std::string fs_path =
            shader_dir_path + "/" + "fs_" + shader_name + ".bin";

        _program = bigg::loadProgram(vs_path.c_str(), fs_path.c_str());
    }

    ~Material() { bgfx::destroy(_program); }

    virtual void submitUniforms() {}
    virtual void drawImgui() {}
    virtual void update(float dt) {}

    bgfx::ProgramHandle program() { return _program; }

  protected:
    bgfx::ProgramHandle _program;
};
} // namespace bigger

#endif // BIGGER_MATERIAL_HPP
