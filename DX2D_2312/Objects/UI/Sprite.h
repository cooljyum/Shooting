#pragma once

class Sprite : public Quad
{
public:
	Sprite();
	Sprite(wstring path);
	Sprite(wstring path, Vector2 size);

	void Render() override;
	void PostRender();

};