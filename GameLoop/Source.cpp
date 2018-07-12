#include <iostream>
#include <string>

#include <ctime> //clock_t, sec level measurement
#include <chrono>
#include <windows.h> //Sleep method

using namespace std;

void FixedFrameTimeLoop(double targetFromeTimeMilliSec)
{
	int i = 0;
	int playerSpeed = 500;
	int playerPosition = 0;
	while (i < 10)
	{
		chrono::steady_clock::time_point start = chrono::steady_clock::now();
		
		//update
		i++;
		
		cout << "---------\r\n" << "loop update" << endl;
		chrono::steady_clock::time_point realEnd = chrono::steady_clock::now();
		double realFrame = chrono::duration_cast<chrono::nanoseconds>(realEnd - start).count();
		playerPosition += playerSpeed * realFrame * 0.000000001;

		Sleep(targetFromeTimeMilliSec);
		chrono::steady_clock::time_point fixedEnd = chrono::steady_clock::now();
		double fixedFrame = chrono::duration_cast<chrono::nanoseconds>(fixedEnd - start).count();

		cout << "read frame time needed to update: " << realFrame << " nano-sec" << endl;
		cout << "fixed frame time: " << fixedFrame << " nano-sec\r\n" << "----------" << endl;
	}

	cout << "player final position: " << playerPosition << endl;
}

void CheckLoopInterval()
{
	int i = 0;
	while (i < 10)
	{
		//time point = clock.now
		chrono::steady_clock::time_point start = chrono::steady_clock::now(); //static method now()

		i++;
		cout << "---------\r\n" << "loop update" << endl;

		chrono::steady_clock::time_point end = chrono::steady_clock::now();

		//generic function
		//nano sec = 10^-9 sec
		double elapse = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

		cout << elapse  << " nano-sec" << "\r\n" << "----------" << endl;
	}
}

int main()
{
	FixedFrameTimeLoop(20); //0.02s
	//CheckLoopInterval();

	system("PAUSE");
	return 0;
}