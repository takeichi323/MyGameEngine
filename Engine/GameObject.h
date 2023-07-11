#pragma once

#include <list>
#include "Transform.h"
#include <string>


using std::list;

class GameObject
{
	bool IsDead();

	//struct OBJECT_STATE
	//{
	//	
	//	unsigned dead : 1;			//çÌèúÇ∑ÇÈÇ©
	//};
	//OBJECT_STATE state_;
protected:
	list <GameObject*>             childList_;
	Transform	                   transform_;
	GameObject*                    pParent_;
	std::string                    objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() =0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();
	void KillMe();
	
	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}
};

