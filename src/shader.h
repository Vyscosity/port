#pragma once

#include <iostream>

#include <bgfx/bgfx.h>
#include "maths.h"

class Camera;

class Shader {
public:
	Shader(const char* vertex, const char* fragment);
	~Shader();

	void loadProjViewMatrix(const glm::mat4& p, const glm::mat4& v);
	void loadModelMatrix(glm::vec3 quad);

	void loadMatrix(const Camera& camera);

	void use() const;

protected:
	bgfx::ProgramHandle program_;
};