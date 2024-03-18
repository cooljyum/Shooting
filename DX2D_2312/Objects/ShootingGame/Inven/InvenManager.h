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

	void SetTarget(Plane* transform) { inven->SetTarget(transform); }

public:
	Button* invenBtn;
	Sprite* invenBtnTxt;

	Inventory* inven;
};