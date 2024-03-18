#pragma once

class Collider : public Transform
{
protected:
	enum class Type
	{
		RECT, CIRCLE
	};

public:
	Collider();
	~Collider();

	void Render();

	bool IsCollision(Collider* collider, Vector2* overlap = nullptr);

	virtual bool IsPointCollision(Vector2 point) = 0;
	virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) = 0;
	virtual bool IsCircleCollision(class CircleCollider* circle) = 0;

	static void OnDraw() { isDraw = !isDraw; }

	ColorBuffer* GetColor() { return material->GetColor(); }

protected:
	Type type;
	
	Mesh<Vertex>* mesh;
	
	static bool isDraw;

private:
	Material* material;
	MatrixBuffer* worldBuffer;

};