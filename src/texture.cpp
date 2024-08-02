#include "texture.h"

#include <fstream>

#include <bimg/decode.h>
#include <iostream>
//#include <stb/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

Texture::Texture(const char* file)
{
    load(file);
}

void Texture::Atlas()//const char* file)
{
    //load(file);
    m_imageSize = 256;
    m_individualTextureSize = 16;
}

void Texture::load(const char* file)
{
    bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

    {

        //std::cout << "Loading texture: " << file << "\n";
        int width, height;
        stbi_uc* data = stbi_load(file, &width, &height, 0, 4);
        const bgfx::Memory* mem = bgfx::copy(data, width * height * 4);
        if (nullptr != mem)
        {
            handle = bgfx::createTexture2D(
                (uint16_t)width,
                (uint16_t)height,
                false,
                1,
                bgfx::TextureFormat::RGBA8,
                BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT,
                mem);
        }
        else
        {
            std::cerr << "Could not load texture: " << file << "\n";
        }
        stbi_image_free(data);

    }
    m_handle = handle;
}

Texture::~Texture()
{
    //bgfx::destroy(m_handle);
}

void Texture::bind()
{
    s_color = bgfx::createUniform("s_color", bgfx::UniformType::Sampler);
    bgfx::setTexture(0, s_color, m_handle);
}

std::vector<float> Texture::getSize(const glm::vec2& coords)
{
    static const float texturesPerRow = (float)m_imageSize / (float)m_individualTextureSize;
    static const float unitSize = 1.0f / texturesPerRow;
    static const float pixel = 1.0f / (float)m_imageSize;

    static float margin = 0.001f;

    float xMin = (coords.x * unitSize) + margin * pixel;
    float yMin = (coords.y * unitSize) + margin * pixel;

    float xMax = (xMin + unitSize) - margin * pixel;
    float yMax = (yMin + unitSize) - margin * pixel;

    return
    {
        xMax, yMax,
        xMin, yMax,
        xMin, yMin,
        xMax, yMin
    };
}