#include "Framework.h"

GameObject::GameObject(int depth) : depth(depth)
{
	material = new Material();
	worldBuffer = new MatrixBuffer();

	ObjectManager::Get()->Add(this);
}

GameObject::~GameObject()
{
	delete material;
	delete worldBuffer;
}
