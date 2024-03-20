#include "Framework.h"

Sprite::Sprite() : Quad()
{
}

Sprite::Sprite(wstring path, bool isAdd) : Quad(path, isAdd)
{
}

Sprite::Sprite(wstring path, Vector2 size, bool isAdd) : Quad(path, size, isAdd)
{
}

void Sprite::Render()
{
	Quad::Render();
}

void Sprite::PostRender()
{
	Quad::Render();
}
