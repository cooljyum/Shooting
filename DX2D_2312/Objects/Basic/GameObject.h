#pragma once

class GameObject : public Transform
{
public:
	GameObject(int depth = 0);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;

	int GetDepth() { return depth; }

protected:
	int depth;

	Material* material;
	MatrixBuffer* worldBuffer;
};