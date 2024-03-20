#pragma once

class UIManager : public Singleton<UIManager>
{
private:
	friend class Singleton;

	UIManager();
	~UIManager();

public:
	void Update();
	void PostRender();

	Inventory* GetInVen() { return inven; }

	void SetOwner(Plane* owner) { inven->SetOwner(owner); }
	void SetSynthesis(vector<pair<Item*, int>> items) { synthesis->SetItems(items); }

public:
	Button* invenBtn;
	Sprite* invenBtnTxt;

	Inventory* inven;
	Synthesis* synthesis;

};