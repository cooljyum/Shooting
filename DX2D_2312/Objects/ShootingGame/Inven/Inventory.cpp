#include "Framework.h"

Inventory::Inventory()
{
	CreateInven();
}

Inventory::~Inventory()
{
	delete invenBg;
	delete invenTitle;
	delete invenTitleTxt;
	delete closeBtn;
	delete nextBtn;
	delete prevBtn;

	for (Button* itemSlot : itemSlots)
	{
		delete itemSlot;
	}

	for (Button* equipSlot : equipSlots)
	{
		delete equipSlot;
	}

}

void Inventory::PostRender()
{
	//nextBtn->RenderUI();

	string str = "Inven CurPage : " + to_string(page);
	ImGui::Text(str.c_str());

	invenBg->PostRender();
	invenTitle->PostRender();
	invenTitleTxt->PostRender();
	closeBtn->PostRender();
	nextBtn->PostRender();
	prevBtn->PostRender();

	for (Button* itemSlot : itemSlots)
	{
		itemSlot->PostRender();
	}
	
	for (Button* equipSlot : equipSlots)
	{
		equipSlot->PostRender();
	}
}

void Inventory::SetActive(bool isActive)
{
	if (isActive) Timer::Get()->SetScale(0.0f);
	else Timer::Get()->SetScale(1.0f);

	this->isActive = isActive;
	invenBg->SetActive(isActive);
	invenTitle->SetActive(isActive);
	invenTitleTxt->SetActive(isActive);
	closeBtn->SetActive(isActive);
	nextBtn->SetActive(isActive);
	prevBtn->SetActive(isActive);

	for (Button* itemSlot : itemSlots)
	{
		itemSlot->SetActive(isActive);
		itemSlot->SetFrontImgActive(isActive);
	}

	FOR (3)
	{
		equipSlots[i]->SetActive(isActive);
		if(equipItems[i] != nullptr)
			equipSlots[i]->SetFrontImgActive(isActive);
		else 
			equipSlots[i]->SetFrontImgActive(false);
	}
	UpdateSlot();
}

void Inventory::AddItem(Item* item)
{
	items.push_back(item);
	UpdateSlot();
}

void Inventory::PageMove(int n)
{
	if (page + n > maxPage || page + n <= 0) return;

	page += n;
	UpdateSlot();
}

void Inventory::AddEquipItem(int type, Item* item)
{
	if (type > 3 || type < 0) return;
	int idx = (type - 1);

	if (item == nullptr) 
	{
		ItemData itemdata = equipItems[idx]->GetData();
		target->AddAbility(-itemdata.attack, -itemdata.defense, -itemdata.hp, -itemdata.speed);

		equipItems[idx] = nullptr;
		equipSlots[idx]->SetFrontImgActive(false);
		return;
	}

	if (equipItems[idx] != nullptr) return;

	equipItems[idx] = item;

	ItemData itemdata = item->GetData();
	equipSlots[idx]->SetFrontImg(L"Resources/Textures/Shooting3/Item/" + itemdata.textureFile);
	equipSlots[idx]->SetFrontImgActive(true);
	equipSlots[idx]->SetEvent([this, type]() { AddEquipItem(type); });

	target->AddAbility( itemdata.attack, itemdata.defense, itemdata.hp, itemdata.speed);
}

void Inventory::UpdateSlot()
{
	if (items.size() == 0) return;
	

	int startPos = (page - 1) * 6;
	int endPos;
	
	if (items.size() < page * 6)
		endPos = items.size();
	else
		endPos = startPos + 6;
	
	maxPage = (items.size() / 6) + 1;

	for (int i = 0; i < 6; i++) {
		if (startPos + i < endPos) {
			itemSlots[i]->SetFrontImgActive(isActive);
			ItemData itemdata = items[startPos + i]->GetData();
			wstring path = L"Resources/Textures/Shooting3/Item/";
			itemSlots[i]->SetFrontImg(path + itemdata.textureFile);
			itemSlots[i]->SetEvent([this, itemdata, index = startPos + i]() {
				AddEquipItem(itemdata.type, items[index]);
				});
		}
		else {
			itemSlots[i]->SetFrontImgActive(false);
			itemSlots[i]->SetEvent();
		}
	}
}


void Inventory::CreateInven()
{
	invenBg = new Sprite(L"Resources/Textures/Shooting3/UI/toggle_bg.png", { 500.0f, 500.0f });
	invenBg->SetLocalPosition({ CENTER_X, 290.0f });

	invenTitle = new Sprite(L"Resources/Textures/Shooting3/UI/bg_title.png");
	invenTitle->SetLocalPosition({ CENTER_X , 550.0f });

	invenTitleTxt = new Sprite(L"Resources/Textures/Shooting3/UI/equipTxt_B.png");
	invenTitleTxt->SetParent(invenTitle);
	invenTitleTxt->SetLocalPosition({ -5.0f , 15.0f });

	closeBtn = new Button(L"Resources/Textures/Shooting3/UI/closeBtn.png", { 950.0f , 550.0f });
	closeBtn->SetEvent([this]() {this->SetActive(false); });

	nextBtn = new Button(L"Resources/Textures/Shooting3/UI/nextBtn.png", { 730.0 , 120.0f });
	nextBtn->SetEvent([this]() { PageMove(1); });

	prevBtn = new Button(L"Resources/Textures/Shooting3/UI/prevBtn.png", { 550.0f , 120.0f });
	prevBtn->SetEvent([this]() { PageMove(-1); });

	FOR(6)
	{
		int row = i / 3;
		int col = i % 3;

		Button* itemSlot = new Button(L"Resources/Textures/Shooting3/UI/Item_Level_0.png", { 480.0f + (col * 160.0f) , 405.0f - (row * 160.0f) });
		itemSlots.push_back(itemSlot);
	}

	FOR(3)
	{
		wstring path = L"Resources/Textures/Shooting3/UI/EquipSlot_" + to_wstring(i + 1) + L".jpg";
		Button* equipSlot = new Button(path, { 300.0f , 450.0f - (i * 160.0f) });
		equipSlots.push_back(equipSlot);
	}

	equipItems.resize(3);

	SetActive(false);
}