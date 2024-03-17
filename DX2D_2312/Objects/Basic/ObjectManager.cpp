#include "Framework.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	for (GameObject* object : objects)
		delete object;
}

void ObjectManager::Update()
{
	for (GameObject* object : objects)
		object->Update();
}

void ObjectManager::Render()
{
	//���� - ���̼������
	
	//��������
	//for (int i = 0; i < objects.size() - 1; i++)
	//{
	//	for (int j = 0; j < objects.size() - 1; j++)
	//	{
	//		if (objects[i]->GetDepth() > objects[i + 1]->GetDepth())
	//			swap(objects[i], objects[i + 1]);
	//	}
	//}

	//��������
	//for (int i = 0; i < objects.size() - 1; i++)
	//{
	//	for (int j = i + 1 ; j < objects.size() ; j++)
	//	{
	//		if (objects[i]->GetDepth() > objects[j]->GetDepth())
	//			swap(objects[i], objects[j]);
	//	}
	//}

	sort(objects.begin(), objects.end(), &GameObject::Compare);

	for (GameObject* object : objects)
	{
		object->Render();		
	}
}

void ObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
}