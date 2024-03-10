#pragma once

class Plane : public Quad
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();
	
	CircleCollider* GetCollider() { return collider; }

	void Collision();

private:
	void Fire();

private:
	float speed = 100.0f;

	CircleCollider* collider;
	Quad* cursor;

public:
	static int health;
};