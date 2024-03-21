#include "Framework.h"

Synthesis::Synthesis() :Inventory()
{
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

	for (Button* synthesisSlot : synthesisSlots)
	{
		synthesisSlot->Update();
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

	int start = (page - 1) * 6;
	int end = items.size() < start + 6 ? items.size() : start + 6;

	FOR(itemSlots.size())
	{
		itemSlots[i]->PostRender();

		if (!itemSlots[i]->IsActive()) continue;

		if (start < end)
		{
			Vector2 pos = itemSlots[i]->GetGlobalPosition() + Vector2(30, -30);
			Font::Get()->RenderText(to_string(items[start].second), pos);
			start++;
		}
	}

	for (Button* synthesisSlot : synthesisSlots)
	{
		synthesisSlot->PostRender();
		synthesisSlot->RenderUI();
	}
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
		Button* synthesisSlot = new Button(path, { 215.0f + (i * 200.0f) , 580.0f }, false);
		synthesisSlots.push_back(synthesisSlot);
	}

	SetActive(false);
}
