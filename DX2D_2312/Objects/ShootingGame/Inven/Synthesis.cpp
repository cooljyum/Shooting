#include "Framework.h"

Synthesis::Synthesis()
{
	CreateInven();

	Observer::Get()->AddEvent("SynthesisOpen", bind(&Synthesis::SetActive, this, true));
	
}

Synthesis::~Synthesis()
{
	delete itemSlotBg;
	delete synthesisBg;
	delete closeBtn;
	delete nextBtn;
	delete prevBtn;

	for (Button* itemSlot : itemSlots)
	{
		delete itemSlot;
	}

	for (Button* equipSlot : synthesisSlots)
	{
		delete equipSlot;
	}

	for (const auto& pair : items) {
		delete pair.first;
	}
}

void Synthesis::Update()
{
	itemSlotBg->Update();
	synthesisBg->Update();
	closeBtn->Update();
	nextBtn->Update();
	prevBtn->Update();

	for (Button* itemSlot : itemSlots)
	{
		itemSlot->Update();
	}

	for (Button* equipSlot : synthesisSlots)
	{
		equipSlot->Update();
	}
}

void Synthesis::PostRender()
{
	closeBtn->RenderUI();

	string str = "Synthsis CurPage : " + to_string(page);
	ImGui::Text(str.c_str());

	itemSlotBg->PostRender();
	synthesisBg->PostRender();

	closeBtn->PostRender();
	nextBtn->PostRender();
	prevBtn->PostRender();

	for (Button* itemSlot : itemSlots)
	{
		itemSlot->PostRender();
	}

	for (Button* equipSlot : synthesisSlots)
	{
		equipSlot->PostRender();
		equipSlot->RenderUI();
	}
}

void Synthesis::SetActive(bool isActive)
{
	if (isActive) Timer::Get()->SetScale(0.0f);
	else Timer::Get()->SetScale(1.0f);

	this->isActive = isActive;
	itemSlotBg->SetActive(isActive);
	itemSlotBg->SetActive(isActive);
	synthesisBg->SetActive(isActive);
	closeBtn->SetActive(isActive);
	nextBtn->SetActive(isActive);
	prevBtn->SetActive(isActive);

	FOR(6)
	{
		itemSlots[i]->SetActive(isActive);
		if (!isActive)
			itemSlots[i]->SetFrontImgActive(isActive);
	}

	FOR(3)
	{
		synthesisSlots[i]->SetActive(isActive);
		if (owner)
			if (owner->GetEuipItems()[i].first != nullptr)
				synthesisSlots[i]->SetFrontImgActive(isActive);
			else
				synthesisSlots[i]->SetFrontImgActive(false);
	}
	UpdateSlot();
}

void Synthesis::AddItem(Item* item, int cnt)
{
}

void Synthesis::AddEquipItem(int type, Item* item, int cnt)
{
}

void Synthesis::CreateInven()
{
	itemSlotBg = new Sprite(L"Resources/Textures/Shooting3/UI/toggle_bg.png", { 775.0f, 500.0f }, false);
	itemSlotBg->SetLocalPosition({ CENTER_X, 175.0f });
	
	synthesisBg = new Sprite(L"Resources/Textures/Shooting3/UI/SynthesisBg.png", false);
	synthesisBg->SetLocalPosition({ CENTER_X, 745.0f });

	closeBtn = new Button(L"Resources/Textures/Shooting3/UI/closeBtn.png", { 745.0f , 345.0f }, false);
	closeBtn->SetEvent([this]() {this->SetActive(false); });

	nextBtn = new Button(L"Resources/Textures/Shooting3/UI/nextBtn.png", { CENTER_X + 150.0f , 40.0f }, false);
	nextBtn->SetEvent([this]() { PageMove(1); });

	prevBtn = new Button(L"Resources/Textures/Shooting3/UI/prevBtn.png", { CENTER_X - 150.0f , 40.0f }, false);
	prevBtn->SetEvent([this]() { PageMove(-1); });

	FOR(6)
	{
		int row = i / 3;
		int col = i % 3;

		Button* itemSlot = new Button(L"Resources/Textures/Shooting3/UI/Item_Level_0.png", { (CENTER_X - 160.f) + (col * 160.0f) , 315.0f - (row * 160.0f) }, false);
		itemSlots.push_back(itemSlot);
	}

	FOR(3)
	{
		wstring path = L"Resources/Textures/Shooting3/UI/Item_Level_0.png";
		Button* equipSlot = new Button(path, { 215.0f + (i * 200.0f) , 580.0f }, false);
		synthesisSlots.push_back(equipSlot);
	}

	SetActive(false);
}

bool Synthesis::CheckIsItem(Item* checkItem)
{
    return false;
}

void Synthesis::EarseItem(Item* checkItem)
{
}

void Synthesis::UpdateSlot()
{
	if (items.size() == 0)
	{
		itemSlots[0]->SetFrontImgActive(false);
		itemSlots[0]->SetEvent();
		return;
	}

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
			Item* item = items[startPos + i].first;
			ItemData itemdata = item->GetData();
			wstring path = L"Resources/Textures/Shooting3/Item/";
			itemSlots[i]->SetFrontImg(path + itemdata.textureFile);
			itemSlots[i]->SetEvent([this, itemdata, index = startPos + i, item, itemSlot = itemSlots[i]]() {
				AddEquipItem(itemdata.type, items[index].first, items[index].second);
				EarseItem(item);

				});
		}
		else {
			itemSlots[i]->SetFrontImgActive(false);
			itemSlots[i]->SetEvent();
		}
	}
}

void Synthesis::PageMove(int n)
{
}
