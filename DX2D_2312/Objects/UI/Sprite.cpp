#include "Framework.h"

Sprite::Sprite() : Quad()
{
}

Sprite::Sprite(wstring path) : Quad(path)
{
}

Sprite::Sprite(wstring path, Vector2 size) : Quad(path, size)
{
}

void Sprite::Render()
{
}

void Sprite::PostRender()
{
	Quad::Render();
}
