#include "Framework.h"

UIManager::UIManager()
{
	invenBtn = new Button(L"Resources/Textures/Shooting3/UI/bg_btn.png", false);
	invenBtn->SetLocalPosition( 690.0f, 90.0f);
	invenBtn->SetEvent([this]() {inven->SetActive(true); });

	invenBtnTxt = new Sprite(L"Resources/Textures/Shooting3/UI/equipTxt_B.png", false);
	invenBtnTxt->SetParent(invenBtn);

	inven = new Inventory();

	synthesis = new Synthesis();
}

UIManager::~UIManager()
{
	delete invenBtn;
	delete invenBtnTxt;

	delete inven;

	delete synthesis;
}

void UIManager::Update()
{
	invenBtn->Update();
	invenBtnTxt->Update();

	inven->Update();

	synthesis->Update();
}

void UIManager::PostRender()
{
	//invenBtn->RenderUI();

	invenBtn->Render();
	invenBtnTxt->Render();

	inven->PostRender();

	synthesis->PostRender();
}
