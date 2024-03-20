#include "Framework.h"

Panel::Panel(wstring textureFile) : Quad(textureFile, false)
{
	collider = new RectCollider(size);
	collider->SetParent(this);
}

Panel::~Panel()
{
	delete collider;
}

void Panel::Update()
{
	if (!IsActive()) return;

	Drag();

	UpdateWorld();
	collider->UpdateWorld();
}

void Panel::Render()
{
	if (!IsActive()) return;

	Quad::Render();
	collider->Render();
}

void Panel::Drag()
{
	if (!collider->IsPointCollision(mousePos)) return;

	if (KEY->Down(VK_LBUTTON))
		offset = mousePos - GetGlobalPosition();

	if (KEY->Press(VK_LBUTTON))
		localPosition = mousePos - offset;
}
