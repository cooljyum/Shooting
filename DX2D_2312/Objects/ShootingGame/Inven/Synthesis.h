#pragma once

class Synthesis : public Panel
{
public:
	Synthesis();
	~Synthesis();

	void Update();

	void PostRender();

	void SetOwner(Plane* owner) { this->owner = owner; }

	void SetActive(bool isActive);

	void SetItems(vector<pair<Item*, int>> items ) { this->items = items; }

	void AddItem(Item* item, int cnt = 1);
	void AddSynhesisItem(int type, Item* item = nullptr, int cnt = NULL);

private:
	void CreateInven();

	bool CheckIsItem(Item* checkItem);
	void EarseItem(Item* checkItem);
	void EarseSynhesisItem(Item* checkItem);

	void UpdateSlot();
	void UpdateSynhesisSlot();

	void PageMove(int n);

	void Excute();

	bool IsCheck();

	void UpgradeSuccess();
	void UpgradeFail();

private:
	Plane* owner;

	bool isActive;

	int page = 1, maxPage = 1;

	Sprite* itemSlotBg;
	Sprite* synthesisBg;

	Button* closeBtn;

	Button* nextBtn;
	Button* prevBtn;

	vector<Button*> itemSlots;
	vector<Button*> synthesisSlots;

	vector<pair<Item*, int>> items;
	vector<pair<Item*, int>> synthesisItems;

	Button* synthesisBtn;

	int checkKey = 0;

};