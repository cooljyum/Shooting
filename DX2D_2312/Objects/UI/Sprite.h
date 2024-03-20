#pragma once

class Sprite : public Quad
{
public:
	Sprite();
	Sprite(wstring path, bool isAdd = false);
	Sprite(wstring path, Vector2 size, bool isAdd = false);

	void Render() override;
	void PostRender();

};