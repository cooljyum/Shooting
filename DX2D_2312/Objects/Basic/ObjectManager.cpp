#include "Framework.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	for (pair<int, GameObject*> object : objects)
		delete object.second;
}

void ObjectManager::Update()
{
	for (pair<int, GameObject*> object : objects)
		object.second->Update();
}

void ObjectManager::Render()
{
	for (pair<int, GameObject*> object : objects)
	{
		object.second->Render();		
	}
}

void ObjectManager::Add(GameObject* object)
{
	objects.insert({ object->GetDepth(), object });
}
