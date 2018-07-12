#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

//一个朵人游戏, 几个人站成一个连锁链, 由一个人被扇开始, 沿着链传递这个巴掌

class Actor
{
public:
	Actor() = default;
	Actor(string name) :is_slapped_this_frame(false), name(name) {};
	~Actor() {}

	void setFace(Actor* a) { _facingActor = a; }

	bool isSlapped() { return is_slapped_this_frame; }

	void getSlap() 
	{ 
		will_be_slapped_next_frame = true;
	}
	//update current frame
	void update()
	{
		if (isSlapped())
		{
			_facingActor->getSlap();
			cout << name << " is slapped by other, he's gonna slap back at " + _facingActor->name << endl;
		}
		else 
		{
			cout << name << " is not slapped by other, he's cool this frame" << endl;
		}
	}
	//prepare for next frame
	void swap()
	{
		cout << name << " states: current slapped->" << is_slapped_this_frame << " , will be slapped->" << will_be_slapped_next_frame << endl;
		is_slapped_this_frame = will_be_slapped_next_frame;
		will_be_slapped_next_frame = false; //means clear state
	}

private:
	string name;
	bool is_slapped_this_frame;	//reading state of double buffer
	bool will_be_slapped_next_frame; //writing state of double buffer
	Actor * _facingActor;
};

class Stage
{
public:
	Stage() = default;
	~Stage() = default; //TODO 我在这里delete[] buffer会报内存错误

	void update()
	{
		for (int i = 0; i < size; i++)
		{
			buffer[i]->update();
		}
		cout << "-------------------" << endl;
		for (int i = 0; i < size; i++)
		{
			buffer[i]->swap();
		}
	}

	void Add(Actor* actor, int order)
	{
		assert(order < size);
		buffer[order] = actor;
	}

private:
	static int const size = 3;
	Actor * buffer[size]; //note this is array of pointers declaration
};

int main()
{
	Stage st = Stage();
	Actor* ZhanGe = new Actor("Zhange");
	Actor* QiGe = new Actor("Qi");
	Actor* FanGe = new Actor("FanGe");
	ZhanGe->setFace(QiGe);
	QiGe->setFace(FanGe);
	FanGe->setFace(ZhanGe);

	st.Add(QiGe, 2);
	st.Add(FanGe, 0);
	st.Add(ZhanGe, 1);

	QiGe->getSlap();

	string s;
	while (true)
	{
		s = cin.get();
		cout << s << endl;
		if (s == "q")
			break;
		else
			st.update();
	}

	delete QiGe;
	delete ZhanGe;
	delete FanGe;
	return 0;
}