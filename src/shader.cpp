#include "shader.h"

#include <iostream>
#include <stdexcept>
#include <fstream>

#include <bx/math.h>
#include <bx/string.h>
#include <bgfx/platform.h>

#include <glm/glm.hpp>

#include "camera.h"


// shader things
#include <bgfx/embedded_shader.h>
#include <vs_cubes.sc.glsl.bin.h>
#include <vs_cubes.sc.essl.bin.h>
#include <vs_cubes.sc.spv.bin.h>
#include <fs_cubes.sc.glsl.bin.h>
#include <fs_cubes.sc.essl.bin.h>
#include <fs_cubes.sc.spv.bin.h>
#if defined(_WIN32)
//#include <vs_cubes.sc.dx9.bin.h>
#include <vs_cubes.sc.dx11.bin.h>
//#include <fs_cubes.sc.dx9.bin.h>
#include <fs_cubes.sc.dx11.bin.h>
#endif //  defined(_WIN32)
#if __APPLE__
#include <vs_cubes.sc.mtl.bin.h>
#include <fs.sc.mtl.bin.h>
#endif // __APPLE__

static const bgfx::EmbeddedShader shaders_[] =
{
    BGFX_EMBEDDED_SHADER(vs_cubes), BGFX_EMBEDDED_SHADER(fs_cubes), BGFX_EMBEDDED_SHADER_END()
};



Shader::Shader(const char* vertex, const char* fragment)
    //: program_(loadShaders(vertex, fragment))
{
    bgfx::RendererType::Enum type = bgfx::getRendererType();

    program_ = bgfx::createProgram(
        bgfx::createEmbeddedShader(shaders_, type, "vs_cubes"),
        bgfx::createEmbeddedShader(shaders_, type, "fs_cubes"), true);
}

Shader::~Shader()
{
    //bgfx::destroy(program_); no need
}

void Shader::use() const
{
    bgfx::submit(0, program_);
}

void Shader::loadProjViewMatrix(const glm::mat4& p, const glm::mat4& v)
{
    bgfx::setViewTransform(0, &v[0][0], &p[0][0]);
}

void Shader::loadModelMatrix(glm::vec3 quad)
{
    glm::mat4 m = glm::identity<glm::mat4>();

    m = glm::translate(m, quad);

    bgfx::setTransform(&m[0][0]);
}

void Shader::loadMatrix(const Camera& camera)
{
    loadProjViewMatrix(camera.getProjectionMatrix(), camera.getViewMatrix());
}

