#include "Framework.h"

Button::Button(wstring path) : Quad(path)
{
	collider = new RectCollider(size);
	collider->SetParent(this);
}

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

	ClickEvent();

	UpdateWorld();
	collider->UpdateWorld();

	if (isFront)
		frontImg->UpdateWorld();

	//Collision();
}

void Button::Render()
{

}

void Button::PostRender()
{
	//collider->RenderUI();
	Quad::Render();
	collider->Render();

	if(isFront)
		frontImg->PostRender();
}

void Button::Collision()
{

	if (collider->IsPointCollision(mousePos))
	{
		if (KEY->Down(VK_LBUTTON))
		{
			if(clickEvent)
				clickEvent();
		}
	}
}

void Button::ClickEvent()
{
	if (collider->IsPointCollision(mousePos)) 
	{

		if (KEY->Down(VK_LBUTTON))
			isDownCheck = true;

		if (KEY->Down(VK_LBUTTON))
		{
			state = DOWN;
		}
		else
		{
			state = OVER;
		}
		if (isDownCheck && KEY->Up(VK_LBUTTON)) 
		{
			if (clickEvent)
				clickEvent();
			
			isDownCheck = true;
		}

	}
	else 
	{
		state = NORMAL;

		if (KEY->Up(VK_LBUTTON))
			isDownCheck = false;
	}

	switch (state)
	{
	case Button::NORMAL:
		material->GetColor()->SetColor(NORMAL_COLOR);
		break;
	case Button::OVER:
		material->GetColor()->SetColor(OVER_COLOR);
		break;
	case Button::DOWN:
		material->GetColor()->SetColor(DOWN_COLOR);
		break;
	default:
		break;
	}
}

