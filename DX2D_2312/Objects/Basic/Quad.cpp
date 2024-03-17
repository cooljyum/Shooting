#include "Framework.h"

Quad::Quad(Vector2 size, bool isAdd) : size(size), GameObject(isAdd)
{
	tag = "Quad";

	mesh = new Mesh<VertexUV>();
	MakeMesh();
	mesh->CreateMesh();
}

Quad::Quad(wstring textureFile, bool isAdd) : GameObject(isAdd)
{
	tag = "Quad";

	material->SetTexture(textureFile);
	size = material->GetTexture()->GetSize();

	mesh = new Mesh<VertexUV>();
	MakeMesh();
	mesh->CreateMesh();
}

Quad::~Quad()
{
	delete mesh;
}

void Quad::Update()
{
	UpdateWorld();
}

void Quad::Render()
{
	if (!IsActive()) return;

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	material->Set();
	mesh->Draw();
}

void Quad::SetTexture(wstring textureFile)
{
	material->SetTexture(textureFile);
	size = material->GetTexture()->GetSize();
	MakeMesh();
	mesh->UpdateVertices();
}

void Quad::MakeMesh()
{
	float left = -size.x * 0.5f;
	float right = +size.x * 0.5f;
	float top = +size.y * 0.5f;
	float bottom = -size.y * 0.5f;

	vector<VertexUV>& vertices = mesh->GetVertices();

	vertices.clear();
	vertices.emplace_back(left, top, 0, 0);
	vertices.emplace_back(right, top, 1, 0);
	vertices.emplace_back(left, bottom, 0, 1);
	vertices.emplace_back(right, bottom, 1, 1);

	vector<UINT>& indices = mesh->GetIndices();

	indices = { 0, 1, 2, 2, 1, 3 };
}
