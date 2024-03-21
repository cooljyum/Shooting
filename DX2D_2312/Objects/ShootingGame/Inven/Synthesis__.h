#pragma once
class Synthesis : public Inventory
{
public:
	Synthesis();

	void Update();

	void PostRender() override;

private:
	void CreateInven() override;

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
};