#pragma once

class Plane : public Quad
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();
	
	CircleCollider* GetCollider() { return collider; }

private:
	void Fire();

private:
	float speed = 100.0f;

	CircleCollider* collider;
	Quad* cursor;
};