#include "model.h"

#include "constants.h"
#include <iostream>
#include <types.h>

bgfx::VertexLayout Vertex::ms_layout;

Model::Model(size_t reserve)
{
	setupObjects(reserve);
}

Model::Model(const Mesh& mesh)
{
	setupObjects();
	addData(mesh); // for some reason this is not called it is instead in the chunkmesh
}

void Model::bind() const
{
	if (bgfx::isValid(vbh_)) {
		bgfx::setVertexBuffer(0, vbh_);
	}
	
	if (bgfx::isValid(ibh_)) {
		bgfx::setIndexBuffer(ibh_);

	}
}

Model Model::createCube()
{
	Mesh mesh;
	float w = 1;
	float h = 1;
	float d = 1;
	mesh.vertices =
	{
		// Front
		w, h, d, 0, h, d, 0, 0, d, w, 0, d,
		// Left
		0, h, d, 0, h, 0, 0, 0, 0, 0, 0, d,
		// Back
		0, h, 0, w, h, 0, w, 0, 0, 0, 0, 0,
		// Right
		w, h, 0, w, h, d, w, 0, d, w, 0, 0,
		// Top
		w, h, 0, 0, h, 0, 0, h, d, w, h, d,
		// Bottom
		0, 0, 0, w, 0, 0, w, 0, d, 0, 0, d,
	};
	
	for (int itr = 0, i = 0; itr < 6; itr++)
	{
		mesh.indices.push_back(i);
		mesh.indices.push_back(i + 1);
		mesh.indices.push_back(i + 2);
		mesh.indices.push_back(i + 2);
		mesh.indices.push_back(i + 3);
		mesh.indices.push_back(i);
		i += 4;
	}

	for (int i = 0; i < 6; i++) {
		mesh.uv.insert(mesh.uv.end(),
			{ 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f });
	}
	mesh_ = mesh;
	Model model;
	model.addData({ mesh_.vertices, mesh_.vertices, mesh_.indices });
	return model;
}

void Model::clear()
{
	vertices_.clear();
	//indices_.clear();

	mesh_.clear();

	indexCount_ = 0;

	if (bgfx::isValid(vbh_)) {
		bgfx::destroy(vbh_);
	}
	if (bgfx::isValid(ibh_)) {
		bgfx::destroy(ibh_);
	}

	if (bgfx::isValid(program_)) {
		bgfx::destroy(program_);
	}

	vbh_ = BGFX_INVALID_HANDLE;
	ibh_ = BGFX_INVALID_HANDLE;

	program_ = BGFX_INVALID_HANDLE;

}

void Model::addFace(const Face& face, const glm::ivec3 chunkPos, const glm::ivec3 blockPos)
{
	int index = 0;
	for (int i = 0; i <= 3; i++)
	{
		//mesh_.vertices.push_back(face.vertices[index++] + chunkPos.x * World::chunkSize + blockPos.x);
		//mesh_.vertices.push_back(face.vertices[index++] + chunkPos.y * World::chunkSize + blockPos.y);
		//mesh_.vertices.push_back(face.vertices[index++] + chunkPos.z * World::chunkSize + blockPos.z);


		/*mesh_.vertices.push_back(face.vertices.at(index++) + chunkPos.x * World::chunkSize + blockPos.x);
		mesh_.vertices.push_back(face.vertices.at(index++) + chunkPos.y * World::chunkSize + blockPos.y);
		mesh_.vertices.push_back(face.vertices.at(index++) + chunkPos.z * World::chunkSize + blockPos.z);*/
		mesh_.vertices.push_back(face.vertices.at(index++) + blockPos.x);
		mesh_.vertices.push_back(face.vertices.at(index++) + blockPos.y);
		mesh_.vertices.push_back(face.vertices.at(index++) + blockPos.z);
	}
	mesh_.uv.insert(mesh_.uv.end(), { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f });

	mesh_.indices.push_back(indexCount_);
	mesh_.indices.push_back(indexCount_ + 1);
	mesh_.indices.push_back(indexCount_ + 2);
	mesh_.indices.push_back(indexCount_ + 2);
	mesh_.indices.push_back(indexCount_ + 3);
	mesh_.indices.push_back(indexCount_);
	indexCount_ += 4;
}


void Model::buffer(Model* model)
{
	model->addData(mesh_);
}

void Model::addData(const Mesh& mesh)
{

	Vertex::init();

	const int numVertices = mesh.vertices.size() / 3;

	for (int i = 0; i < numVertices; ++i)
	{
		Vertex vertex;
		vertex.x = mesh.vertices[i * 3];
		vertex.y = mesh.vertices[i * 3 + 1];
		vertex.z = mesh.vertices[i * 3 + 2];
		vertex.u = mesh.uv[i * 2] * 0x7fff;
		vertex.v = mesh.uv[i * 2 + 1] * 0x7fff;
		vertices_.push_back(vertex);
	}

	//indices_ = mesh.indices;
	std::vector<u16> indices = mesh.indices;

	vbh_ = bgfx::createVertexBuffer(bgfx::makeRef(vertices_.data(), vertices_.size() * sizeof(Vertex)), Vertex::ms_layout);
	ibh_ = bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), indices.size() * sizeof(uint16_t)));

}

void Model::setupObjects(size_t reserve)
{

	vbh_ = BGFX_INVALID_HANDLE;
	ibh_ = BGFX_INVALID_HANDLE;
	program_ = BGFX_INVALID_HANDLE;

}