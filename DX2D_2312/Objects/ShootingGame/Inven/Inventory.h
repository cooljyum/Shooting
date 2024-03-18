#pragma once

class Inventory 
{
public:
	Inventory();
	~Inventory();

	void PostRender();

	void SetTarget(Plane* transform) { target = transform; }

	void SetActive(bool isActive);

	void AddItem(Item* item);
	void AddEquipItem(int type, Item* item = nullptr);

private:
	void CreateInven();

	void UpdateSlot();

	void PageMove(int n);

private:
	Plane* target;

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

	vector<Item*> items;
	vector<Item*> equipItems;

};