#include "Framework.h"

Button::Button(wstring path, Vector2 pos) : Quad(path)
{
	collider = new RectCollider(size);
	collider->SetParent(this);

	SetLocalPosition(pos);

	frontImg = new Sprite(path);
	frontImg->SetActive(false);
	frontImg->SetLocalPosition(localPosition);
}

Button::~Button()
{
	delete frontImg;
	delete collider;
}

void Button::Update()
{
	if (!IsActive()) return;

	Quad::Update();
	collider->UpdateWorld();
	if (isFront)
		frontImg->UpdateWorld();

	Collision();
}

void Button::Render()
{

}

void Button::PostRender()
{
	//collider->RenderUI();

	collider->Render();

	Quad::Render();

	if(isFront)
		frontImg->PostRender();
}

void Button::Collision()
{

	if (collider->IsPointCollision(mousePos))
	{
		if (KEY->Down(VK_LBUTTON))
		{
			if(event)
				event();
		}
	}
}

