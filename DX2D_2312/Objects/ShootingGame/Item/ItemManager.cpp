#include "Framework.h"

ItemManager::ItemManager()
{
	totalObject["Exp"].resize(50);

	for (GameObject*& exp : totalObject["Exp"])
	{
		exp = new Item(ShootingDataManager::Get()->GetItemData(1));
		items.push_back((Item*)exp);
	}

	totalObject["Armor"].resize(50);

	for (GameObject*& armor : totalObject["Armor"])
	{
		armor = new Item(ShootingDataManager::Get()->GetItemData(101));
		items.push_back((Item*)armor);
	}

	totalObject["Necklace"].resize(50);

	for (GameObject*& necklace : totalObject["Necklace"])
	{
		necklace = new Item(ShootingDataManager::Get()->GetItemData(201));
		items.push_back((Item*)necklace);
	}

	totalObject["Boot"].resize(50);

	for (GameObject*& boot : totalObject["Boot"])
	{
		boot = new Item(ShootingDataManager::Get()->GetItemData(301));
		items.push_back((Item*)boot);
	}
}

void ItemManager::Update()
{


}

void ItemManager::SetTarget(Transform* transform)
{
	for (Item* item : items)
	{
		item->SetTarget(transform);
	}
}

void ItemManager::Spawn(Vector2 pos)
{
	int type = Random(0, 4);

	Item* item = nullptr;

	switch (type)
	{
	case 0:
		item = Pop("Armor");
		break;
	case 1:
		item = Pop("Necklace");
		break;
	case 2:
		item = Pop("Boot");
		break;
	case 3:
		item = Pop("Exp");
		break;
	}

	item->Spawn(pos);
}
