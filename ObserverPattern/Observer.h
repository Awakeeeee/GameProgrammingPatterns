#pragma once
#include <iostream>
#include <windows.h>

//Linked list style observer
class Observer
{
friend class Subject; //subject can access my private memebers

private:
	Observer* next;
	virtual void onNotify(int eventID) = 0;
public:
	Observer() = default;
};

class AcheivementSystem : public Observer
{
private:
	void onNotify(int eventID)
	{
		if (eventID == 1)
			std::cout << "Acheivement 1 accomplish: Sleep till mid day, fucker!" << std::endl;
		else if (eventID == 2)
			std::cout << "Acheivement 2 accomplush: Meet a girl on the bus!" << std::endl;
	}
};

class EffectSystem : public Observer
{
private:
	void onNotify(int eventID)
	{
		if (eventID == 1)
		{
			Beep(523, 500);
			std::cout << "open eye with @_@ effect" << std::endl;
		}
		else if (eventID == 2)
		{
			Beep(666, 500);
			std::cout << "pump! pump! pump! screen shake with blush" << std::endl;
		}
	}
};
