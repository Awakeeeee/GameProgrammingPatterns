#include <iostream>
#include <string>
#include "Subject.h"
#include "Observer.h"

using namespace std;

int main()
{
	//TODO however, finding the oberver is the part I feel confused about
	Observer* aes = new AcheivementSystem();
	Observer* efs = new EffectSystem();

	EveryDay day = EveryDay(aes);
	day.AddObserver(efs);

	string input;
	cout << "Press -quit to exit the ..game?" << endl;
	while (true)
	{
		getline(cin, input);
		if (input == "-quit")
			break;

		if (input == "wake up")
			day.notify(1);
		else if (input == "can I get your wechat")
			day.notify(2);
		else
			cout << "." << endl;
	}

	delete aes;
	delete efs;
	return 0;
}