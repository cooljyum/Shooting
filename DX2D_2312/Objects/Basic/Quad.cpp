#include "Framework.h"

Quad::Quad(Vector2 size) : size(size)
{
	tag = "Quad";

	mesh = new Mesh<VertexUV>();
	MakeMesh();
	mesh->CreateMesh();

	colorBuffer = new ColorBuffer();	
}

Quad::Quad(wstring textureFile)
{
	tag = "Quad";

	material->SetTexture(textureFile);
	size = material->GetTexture()->GetSize();

	mesh = new Mesh<VertexUV>();
	MakeMesh();
	mesh->CreateMesh();

	colorBuffer = new ColorBuffer();	
}

Quad::~Quad()
{
	delete mesh;
	delete colorBuffer;	
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
	colorBuffer->SetPS(0);

	material->Set();
	mesh->Draw();
}

void Quad::MakeMesh()
{
	float left = -size.x * 0.5f;
	float right = +size.x * 0.5f;
	float top = +size.y * 0.5f;
	float bottom = -size.y * 0.5f;

	vector<VertexUV>& vertices = mesh->GetVertices();

	vertices.emplace_back(left, top, 0, 0);
	vertices.emplace_back(right, top, 1, 0);
	vertices.emplace_back(left, bottom, 0, 1);
	vertices.emplace_back(right, bottom, 1, 1);

	vector<UINT>& indices = mesh->GetIndices();

	indices = { 0, 1, 2, 2, 1, 3 };
}
