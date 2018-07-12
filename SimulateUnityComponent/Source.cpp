#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class GameObject; //inherit from Object
class Component; //inherit from Object, this holds 'gameObject' amd 'transform' on this obejct, so you can always get them from a MonoBehaviour
class Transform; //inherit from Component
class MonoBehaviour; //inherit from Component, this is actually a component base for custom scripts, and implements Update method
class PlayerHP; //inherit from MonoBehaviour

class Component
{
public:
	string name;
	GameObject* gameObject;
	Transform* transform;
	virtual void CompUpdate() { cout << "Why stop here? no Polymorphsim??" << endl; }; //TODO: Unity并没有在Component里规定Update()方法, 但是C++里我不知道怎么在Gameobject的组件列表里查找MonoBehaviour类型并Update他们
	//实际Unity中, Component也有自己的GetComponent方法, 是从自己依附的GameObject上寻找其他组件
};

class Transform : public Component
{
public:
	Transform() { name = "Transform"; posX = 0; posY = 0; }
	~Transform() {};
	float posX;
	float posY;
};

class MonoBehaviour : public Component
{
	virtual void Start() = 0;
	void CompUpdate() override { Update(); }
	virtual void Update() = 0;
};

class PlayerHP : public MonoBehaviour
{
public:
	PlayerHP() 
	{ 
		name = "PlayerHP"; 
		HP = 100; 
		cout << "PlayerHP Component Added" << endl;
	}
	void Start() { cout << "PlayerHP starts" << endl; }
	void Update() override 
	{ 
		cout << "PlayerHP updating: "<< endl;
		cout << "Current HP: " << HP << endl;
		cout << "Current Position: " << transform->posX << "," << transform->posY << endl;
	}
private:
	int HP;
};

class GameObject
{
public:
	GameObject(string name):name(name) {};
	~GameObject() { components.clear(); };

	template<class T>
	Component& GetComponent()
	{}; //TODO how to implement type search in C++

	Component* GetComponent(string comName) //C++里如果可能返回null, 得用pointer不能用reference, ref不能是null
	{
		for (vector<Component>::iterator it = components.begin(); it != components.end(); it++)
		{
			if (it->name == comName)
			{
				return &(*it);
			}
		}
		return NULL;
	}

	Component* AddComponent(Component com) //Unity在往gameObject上拖拽组件时, 可能实现类似的事情
	{
		//TODO 这里为什么没有多态???
		com.gameObject = this;
		Transform* trans = (Transform*)this->GetComponent("Transform");
		com.transform = trans;

		components.push_back(com);
		return &com;
	}

	void GameObjectUpdate()
	{
		for (vector<Component>::iterator it = components.begin(); it != components.end(); it++)
		{
			it->CompUpdate();
		}
	}

private:
	string name;
	vector<Component> components;
};

int main()
{
	//任何GameObject至少有一个Transform组件
	GameObject player = GameObject("Player");
	player.AddComponent(Transform());

	//开发者添加组件
	player.AddComponent(PlayerHP());

	//进入Game Mode, 引擎的总循环
	//使用Update Pattern更新游戏中的对象列表, 这里只有一个player
	int loop = 0;
	while (loop < 10)
	{
		loop++;

		player.GameObjectUpdate();

		Sleep(1000);
	}

	system("PAUSE");
	return 0;
}