#include "Framework.h"

InvenManager::InvenManager()
{
	invenBtn = new Button(L"Resources/Textures/Shooting3/UI/bg_btn.png", {500.0f, 500.0f});
	invenBtn->SetLocalPosition({ 1169.0f,600.0f });
	invenBtn->SetEvent([this]() {inven->SetActive(true); });

	invenBtnTxt = new Sprite(L"Resources/Textures/Shooting3/UI/equipTxt_B.png");
	invenBtnTxt->SetParent(invenBtn);

	inven = new Inventory();
}

InvenManager::~InvenManager()
{
	delete invenBtn;
	delete invenBtnTxt;
	delete inven;
}

void InvenManager::PostRender()
{
	invenBtn->RenderUI();
	invenBtn->PostRender();
	invenBtnTxt->PostRender();
	inven->PostRender();
}
