#pragma once

class Inventory : public Panel
{
public:
	Inventory();
	~Inventory();

	void Update();

	void PostRender();

	void SetOwner(Plane* owner) { this->owner = owner; }

	void SetActive(bool isActive);

	void AddItem(Item* item, int cnt = 1);
	void AddEquipItem(int type, Item* item = nullptr, int cnt = NULL);

	vector<pair<Item*, int>> GetItems() { return items; }


private:
	void CreateInven();

	bool CheckIsItem(Item* checkItem);
	void EarseItem(Item* checkItem);

	void UpdateSlot();

	void PageMove(int n);

private:
	Plane* owner;

	bool isActive;
	
	int page = 1, maxPage = 1;

	Sprite* invenBg;
	Sprite* invenTitle;
	Sprite* invenTitleTxt;

	Button* closeBtn;

	Button* nextBtn;
	Button* prevBtn;

	vector<Button*> itemSlots;
	vector<Button*> equipSlots;

	vector<pair<Item*, int>> items;

	Button* synthesisBtn;

};