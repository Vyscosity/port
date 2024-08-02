#pragma once

#include <vector>

#include <bgfx/bgfx.h>

#include "maths.h"

class Texture
{
public:
	Texture() = default;
	Texture(const char* file);
	void Atlas();//const char* file);

	~Texture();

	void load(const char* file);
	void bind();

	bgfx::TextureHandle getHandle() { return m_handle; }

	std::vector<float> getSize(const glm::vec2& coords);
private:

	bgfx::TextureHandle m_handle;
	bgfx::UniformHandle s_color;

	int m_imageSize;
	int m_individualTextureSize;
};