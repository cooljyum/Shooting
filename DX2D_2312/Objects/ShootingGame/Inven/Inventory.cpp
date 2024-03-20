#include "Framework.h"

Inventory::Inventory()
{
	CreateInven();

	Observer::Get()->AddEvent("InventoryGetItems", bind(&Inventory::GetItems, this));
}

Inventory::~Inventory()
{
	delete invenBg;
	delete invenTitle;
	delete invenTitleTxt;
	delete closeBtn;
	delete nextBtn;
	delete prevBtn;
	delete synthesisBtn;

	for (Button* itemSlot : itemSlots)
	{
		delete itemSlot;
	}

	for (Button* equipSlot : equipSlots)
	{
		delete equipSlot;
	}

	for (const auto& pair : items) {
		delete pair.first; 
	}

}

void Inventory::Update()
{
	invenBg->Update();
	invenTitle->Update();
	invenTitleTxt->Update();
	closeBtn->Update();
	nextBtn->Update();
	prevBtn->Update();
	synthesisBtn->Update();


	for (Button* itemSlot : itemSlots)
	{
		itemSlot->Update();
	}

	for (Button* equipSlot : equipSlots)
	{
		 equipSlot->Update();
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
	synthesisBtn->PostRender();

	synthesisBtn->RenderUI();

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
	synthesisBtn->SetActive(isActive);

	FOR(6)
	{
		itemSlots[i]->SetActive(isActive);
		if(!isActive)
			itemSlots[i]->SetFrontImgActive(isActive);
	}

	FOR (3)
	{
		equipSlots[i]->SetActive(isActive);
		if(owner)
			if(owner->GetEuipItems()[i].first != nullptr)
				equipSlots[i]->SetFrontImgActive(isActive);
			else 
				equipSlots[i]->SetFrontImgActive(false);
	}
	UpdateSlot();
}

void Inventory::AddItem(Item* item, int cnt)
{
	if (CheckIsItem(item)) return;

	items.push_back(make_pair(item, cnt));
	UpdateSlot();
}

void Inventory::PageMove(int n)
{
	if (page + n > maxPage || page + n <= 0) return;

	page += n;
	UpdateSlot();
}

void Inventory::AddEquipItem(int type, Item* item, int cnt)
{
	if (type > 3 || type < 0) return;
	int idx = (type - 1);

	if (item == nullptr) 
	{
		Item* item = owner->GetEuipItems()[idx].first;
		int cnt = owner->GetEuipItems()[idx].second;
		ItemData itemdata = item->GetData();

		owner->SetEuipItems(idx, nullptr);
		equipSlots[idx]->SetFrontImgActive(false);
		
		AddItem(item, cnt);
		
		owner->AddAbility(-itemdata.attack, -itemdata.defense, -itemdata.hp, -itemdata.speed);
		return;
	}

	if (owner->GetEuipItems()[idx].first != nullptr) return;

	owner->SetEuipItems(idx, item, cnt);

	ItemData itemdata = item->GetData();
	equipSlots[idx]->SetFrontImg(L"Resources/Textures/Shooting3/Item/" + itemdata.textureFile);
	equipSlots[idx]->SetFrontImgActive(true);
	equipSlots[idx]->SetEvent([this, type]() { AddEquipItem(type); });

	owner->AddAbility( itemdata.attack, itemdata.defense, itemdata.hp, itemdata.speed);
}

void Inventory::UpdateSlot()
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


void Inventory::CreateInven()
{
	invenBg = new Sprite(L"Resources/Textures/Shooting3/UI/toggle_bg.png", { 500.0f, 500.0f },false);
	invenBg->SetLocalPosition({ CENTER_X, 300.0f });

	invenTitle = new Sprite(L"Resources/Textures/Shooting3/UI/bg_title.png", false);
	invenTitle->SetLocalPosition({ CENTER_X , 560.0f });

	invenTitleTxt = new Sprite(L"Resources/Textures/Shooting3/UI/equipTxt_B.png", false);
	invenTitleTxt->SetParent(invenTitle);
	invenTitleTxt->SetLocalPosition({ -5.0f , 25.0f });

	closeBtn = new Button(L"Resources/Textures/Shooting3/UI/closeBtn.png", { CENTER_X + 305.0f , 560.0f }, false);
	closeBtn->SetEvent([this]() {this->SetActive(false); });

	nextBtn = new Button(L"Resources/Textures/Shooting3/UI/nextBtn.png", { CENTER_X + 150.0f , 130.0f }, false);
	nextBtn->SetEvent([this]() { PageMove(1); });

	prevBtn = new Button(L"Resources/Textures/Shooting3/UI/prevBtn.png", { CENTER_X - 150.0f , 130.0f }, false);
	prevBtn->SetEvent([this]() { PageMove(-1); });

	synthesisBtn = new Button(L"Resources/Textures/Shooting3/UI/SynthesisBtn.png", { 710.0f, 850.0f }, false);
	synthesisBtn->SetEvent([this]() { UIManager::Get()->SetSynthesis(items);  this->SetActive(false); Observer::Get()->ExcuteEvent("SynthesisOpen");  });

	FOR(6)
	{
		int row = i / 3;
		int col = i % 3;

		Button* itemSlot = new Button(L"Resources/Textures/Shooting3/UI/Item_Level_0.png", { (CENTER_X - 160.f) + (col * 160.0f) , 415.0f - (row * 160.0f) }, false);
		itemSlots.push_back(itemSlot);
	}

	FOR(3)
	{
		wstring path = L"Resources/Textures/Shooting3/UI/EquipSlot_" + to_wstring(i + 1) + L".jpg";
		Button* equipSlot = new Button(path, { 230.0f + (i * 160.0f) , 730.0f }, false);
		equipSlots.push_back(equipSlot);
	}

	SetActive(false);
}

bool Inventory::CheckIsItem(Item* checkItem)
{
	for ( auto& item : items)
	{
		if (item.first->GetData().name == checkItem->GetData().name)
		{
			item.second++;
			return true;
		}
			
	}

	vector<pair<Item*, int>> equipItems = owner->GetEuipItems();
	for (int idx = 0; idx < equipItems.size(); ++idx) {
		auto& itemPair = equipItems[idx];
		if (itemPair.first == nullptr) continue; 
		if (itemPair.first->GetData().name == checkItem->GetData().name) {
			owner->SetEuipItems(idx, itemPair.first, itemPair.second + 1);
			return true;
		}
	}

	return false;
}

void Inventory::EarseItem(Item* checkItem)
{

	for (auto iter = items.begin(); iter != items.end();)
	{
		if (iter->first->GetData().name != checkItem->GetData().name)
			iter++;
		else 
			iter = items.erase(iter);
	}

	UpdateSlot();
}
