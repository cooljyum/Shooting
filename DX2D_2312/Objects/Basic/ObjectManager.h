#pragma once

class ObjectManager : public Singleton<ObjectManager>
{
private:
	friend class Singleton;

	ObjectManager();
	~ObjectManager();

public:
	void Update();
	void Render();	

	void Add(GameObject* object);

private:
	multimap<int, GameObject*> objects;	
};