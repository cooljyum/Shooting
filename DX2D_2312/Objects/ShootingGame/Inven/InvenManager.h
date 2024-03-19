#pragma once

class InvenManager : public Singleton<InvenManager>
{
private:
	friend class Singleton;

	InvenManager();
	~InvenManager();

public:
	void PostRender();

	Inventory* GetInVen() { return inven; }

	void SetOwner(Plane* owner) { inven->SetOwner(owner); }

public:
	Button* invenBtn;
	Sprite* invenBtnTxt;

	Inventory* inven;
};