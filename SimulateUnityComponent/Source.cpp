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
	virtual void CompUpdate() { cout << "Why stop here? no Polymorphsim??" << endl; }; //TODO: Unity��û����Component��涨Update()����, ����C++���Ҳ�֪����ô��Gameobject������б������MonoBehaviour���Ͳ�Update����
	//ʵ��Unity��, ComponentҲ���Լ���GetComponent����, �Ǵ��Լ�������GameObject��Ѱ���������
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

	Component* GetComponent(string comName) //C++��������ܷ���null, ����pointer������reference, ref������null
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

	Component* AddComponent(Component com) //Unity����gameObject����ק���ʱ, ����ʵ�����Ƶ�����
	{
		//TODO ����Ϊʲôû�ж�̬???
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
	//�κ�GameObject������һ��Transform���
	GameObject player = GameObject("Player");
	player.AddComponent(Transform());

	//������������
	player.AddComponent(PlayerHP());

	//����Game Mode, �������ѭ��
	//ʹ��Update Pattern������Ϸ�еĶ����б�, ����ֻ��һ��player
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