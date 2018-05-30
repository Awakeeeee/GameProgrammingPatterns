#define ANDROID

#include <iostream>
#include <string>
#include "SingletonFashions.h"
using namespace std;

int main()
{
	Singleton_Original::instance().Log();
	Singleton_Original_Cpp11::instance().Log();
	FileSystem::instance().Log();

	Singleton_NonStatic sn = Singleton_NonStatic();
	//Singleton_NonStatic sn2 = Singleton_NonStatic(); //assert fail

	Singleton_Manager::instance().getAM().Log();
	Singleton_Manager::instance().getBM().Log();
	Singleton_Manager::instance().getCM().Log();

	system("PAUSE");
	return 0;
}