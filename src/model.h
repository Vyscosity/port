#pragma once

#include <vector>
#include <array>

#include <bgfx/bgfx.h>

#include "maths.h"

#include "types.h"

struct Vertex
{
	float x;
	float y;
	float z;
	uint16_t u;
	uint16_t v;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
			.end();
	}
	static bgfx::VertexLayout ms_layout;
};


struct Face
{
	std::array<float, 12> vertices;
};

const Face FRONT_FACE = { {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1} };
const Face LEFT_FACE = { {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1} };
const Face BACK_FACE = { {0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0} };
const Face RIGHT_FACE = { {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0} };
const Face TOP_FACE = { {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1} };
const Face BOTTOM_FACE = { {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1} };

class Model
{
public:
	struct Mesh
	{
		std::vector<float> vertices;
		std::vector<float> uv;
		std::vector<u16> indices;

		void clear()
		{
			vertices.clear();
			uv.clear();
			indices.clear();

			vertices.shrink_to_fit();
			uv.shrink_to_fit();
			indices.shrink_to_fit();

		}
	};
	Model(size_t reserve = 0);

	Model(const Mesh& mesh);

	void addData(const Mesh& mesh);

	void bind() const;

	//static Model createCube();
	Model createCube();

	void clear();

	void addFace(const Face& face, const glm::ivec3 chunkPos, const glm::ivec3 blockPos);

	int indexCount() const { return indexCount_; }

	void buffer(Model* model);

private:
	bgfx::ProgramHandle program_;

	bgfx::VertexBufferHandle vbh_;
	bgfx::IndexBufferHandle ibh_;

	std::vector<Vertex> vertices_;
	//std::vector<u16> indices_;

	Mesh mesh_;

	int indexCount_ = 0;

	void setupObjects(size_t reserve = 0);
};