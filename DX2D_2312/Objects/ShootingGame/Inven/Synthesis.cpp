#include "Framework.h"

Synthesis::Synthesis() : Panel(L"Resources/Textures/Shooting3/UI/toggle_bg.png")
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
	delete synthesisBtn;

	for (Button* itemSlot : itemSlots)
	{
		delete itemSlot;
	}

	for (Button* synthesisSlot : synthesisSlots)
	{
		delete synthesisSlot;
	}

	for (const auto& pair : items) {
	//	delete pair.first;
	}
}

void Synthesis::Update()
{
	itemSlotBg->Update();
	synthesisBg->Update();
	closeBtn->Update();
	nextBtn->Update();
	prevBtn->Update();
	synthesisBtn->Update();

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

	synthesisBtn->PostRender();

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
	synthesisBtn->SetActive(isActive);

	FOR(6)
	{
		itemSlots[i]->SetActive(isActive);
		if (!isActive)
			itemSlots[i]->SetFrontImgActive(isActive);
	}

	FOR(3)
	{
		synthesisSlots[i]->SetActive(isActive);

		if (i < synthesisItems.size()) 
		{
			if (synthesisItems[i].first != nullptr)
				synthesisSlots[i]->SetFrontImgActive(isActive);
			else
				synthesisSlots[i]->SetFrontImgActive(false);
		}
	}
	UpdateSlot();
}

void Synthesis::AddItem(Item* item, int cnt)
{
	if (CheckIsItem(item)) return;

	items.push_back(make_pair(item, cnt));
	UpdateSlot();
}

void Synthesis::AddSynhesisItem(int type, Item* item, int cnt)
{
	if (synthesisItems.size()>=3) return;

	int idx = type;
	
	if (item == nullptr)
	{
		Item* item = synthesisItems[idx].first;
		int cnt = synthesisItems[idx].second;
		ItemData itemdata = item->GetData();

		EarseSynhesisItem(item);

		//synthesisSlots[idx]->SetFrontImgActive(false);
		//synthesisSlots[idx]->SetEvent();

		AddItem(item, cnt);

		UpdateSynhesisSlot();
		
		return;
	}
	synthesisItems.push_back({ item,cnt });

	//ItemData itemdata = item->GetData();
	//synthesisSlots[idx]->SetFrontImg(L"Resources/Textures/Shooting3/Item/" + itemdata.textureFile);
	//synthesisSlots[idx]->SetFrontImgActive(true);
	//synthesisSlots[idx]->SetEvent([this, type]() { AddSynhesisItem(type); });

	UpdateSynhesisSlot();

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

	synthesisBtn = new Button(L"Resources/Textures/Shooting3/UI/SynthesisBtn.png", { 710.0f, 850.0f }, false);
	synthesisBtn->SetEvent([this]() { Excute();  });


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

bool Synthesis::CheckIsItem(Item* checkItem)
{
	for (auto& item : items)
	{
		if (item.first->GetData().name == checkItem->GetData().name)
		{
			item.second++;
			return true;
		}
	}

    return false;
}

void Synthesis::EarseItem(Item* checkItem)
{
	for (auto iter = items.begin(); iter != items.end();)
	{
		if (iter->first->GetData().name != checkItem->GetData().name)
			iter++;
		else
		{
			if (iter->second > 1)
			{
				iter->second -= 1;
				break;
			}
			else
				iter = items.erase(iter);
		}
	}

	UpdateSlot();
}

void Synthesis::EarseSynhesisItem(Item* checkItem)
{
	for (auto iter = synthesisItems.begin(); iter != synthesisItems.end();)
	{
		if (iter->first->GetData().name != checkItem->GetData().name)
		{
			iter++;
			
		}
		else
		{
			iter = synthesisItems.erase(iter);
			break;
		}
	}

	UpdateSynhesisSlot();
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
				AddSynhesisItem(synthesisItems.size(), items[index].first, items[index].second);
				EarseItem(item);

				});
		}
		else {
			itemSlots[i]->SetFrontImgActive(false);
			itemSlots[i]->SetEvent();
		}
	}
}

void Synthesis::UpdateSynhesisSlot()
{
	FOR(3)
	{
		if (i < synthesisItems.size()) {
			synthesisSlots[i]->SetFrontImgActive(isActive);
			Item* item = synthesisItems[i].first;
			ItemData itemdata = item->GetData();
			wstring path = L"Resources/Textures/Shooting3/Item/";
			synthesisSlots[i]->SetFrontImg(path + itemdata.textureFile);
			synthesisSlots[i]->SetEvent([this,  item]() {
				AddItem(item, 1);
				EarseSynhesisItem(item);
				});
		}
		else {
			synthesisSlots[i]->SetFrontImgActive(false);
			synthesisSlots[i]->SetEvent();
		}
	}
}

void Synthesis::PageMove(int n)
{
	if (page + n > maxPage || page + n <= 0) return;

	page += n;
	UpdateSlot();
}

void Synthesis::Excute()
{
	//1. items안에 있는 아이템의 키값이 다 같은지 체크
	//2. 실패든 성공이든 일단 무조껀 조합창 아이템 다 빼기
	//3. 성공->인벤토리 있는 아이템 다 감소시키고 레벨 1높은 아이템 획득    
	//4. 실패면 인벤토리 창에 아이템 카운트 증가

	FOR(synthesisItems.size())
	{
		Item* item = synthesisItems[i].first;
		AddItem(item, 1);
		synthesisSlots[i]->SetFrontImgActive(false);
	}
	
	if (IsCheck())
		UpgradeSuccess();
	else
		UpgradeFail();

	synthesisItems.clear();
}

bool Synthesis::IsCheck()
{
	//if (count < items.size())
	//	return false;
	checkKey = synthesisItems[0].first->GetData().key;

	FOR(synthesisItems.size())
	{
		Item* item = synthesisItems[i].first;
		if (item->GetData().key != checkKey)
			return false;
	}

	return true;
}

void Synthesis::UpgradeSuccess()
{
	Inventory* inventory = (Inventory*)GetParent();

	inventory->CreateItem(checkKey + 1,1);

	//count = 0;

	//inventory->Clear();
}

void Synthesis::UpgradeFail()
{
//	for (Item* item : items)
	//	RemoveItem(item);
}
