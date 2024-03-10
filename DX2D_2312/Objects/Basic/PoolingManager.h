#pragma once

template <typename T>
class PoolingManager
{
protected:
	PoolingManager() = default;
	~PoolingManager() = default;

public:
	void CreateObjects(string key, UINT poolSize, wstring filePath = L"");
	T* Pop(string key);

protected:
	map<string, vector<GameObject*>> totalObject;
};

template<typename T>
inline void PoolingManager<T>::CreateObjects(string key, UINT poolSize, wstring filePath)
{
	vector<GameObject*> objects(poolSize);

	for (GameObject*& object : objects)
		if (filePath != L"")
			object = new T(filePath);
		else
			object = new T();

	totalObject[key] = objects;
}

template<typename T>
inline T* PoolingManager<T>::Pop(string key)
{
	for (GameObject* object : totalObject[key])
	{
		if (!object->IsActive())
		{
			return (T*)object;
		}
	}

	return nullptr;
}
