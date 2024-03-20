#pragma once

class Panel : public Quad
{
public:
	Panel(wstring textureFile);
	~Panel();

	void Update() override;
	void Render() override;

private:
	void Drag();

private:
	RectCollider* collider;

	Vector2 offset;
};