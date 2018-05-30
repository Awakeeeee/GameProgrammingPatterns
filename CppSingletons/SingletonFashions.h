#pragma once
#include <iostream>
#include <assert.h>

//=================original singleton
class Singleton_Original
{
public:
	static Singleton_Original& instance()
	{
		if (instance_ == NULL)
			instance_ = new Singleton_Original();
		return *instance_;
	}
	void Log()
	{
		std::cout << "Call Singleton_Origin" << std::endl;
	}

private:
	Singleton_Original() {} //private ctor make sure instancing is not possible outside
	static Singleton_Original* instance_;
};
//LNK2001 error fix: static member 如果不初始化就会报错unresolved symbol
Singleton_Original* Singleton_Original::instance_ = NULL;


//============Cpp11 thread secured(?) original fashion singleton
class Singleton_Original_Cpp11
{
public:
	static Singleton_Original_Cpp11& instance()
	{
		//C++11: 不管调用instance多少次, 方法内的静态局部变量只会初始化一次, 存于静态内存
		static Singleton_Original_Cpp11* instance_ = new Singleton_Original_Cpp11();
		return *instance_;
	}
	void Log()
	{
		std::cout << "Call Singleton_Origin_C++11" << std::endl;
	}
private:
	Singleton_Original_Cpp11() {}
};


//===========Singleton Inheritance
class FileSystem
{
public:
	static FileSystem& instance();
	virtual void Log()
	{
		std::cout << "Call Singleton : Filesystem" << std::endl;
	}
	virtual ~FileSystem() {}
protected:
	FileSystem() {}
};

class FileSystem_IOS : public FileSystem
{
public:
	void Log()
	{
		std::cout << "Call Singleton : Filesystem of IOS" << std::endl;
	}
};
class FileSystem_ANDROID : public FileSystem
{
public:
	void Log()
	{
		std::cout << "Call Singleton : Filesystem of ANDROID" << std::endl;
	}
};

//Error C2061 fix: C++代码顺序很重要, 这里用到了FileSystem_IOS, 那么他的定义必须在这一行上面出现
FileSystem& FileSystem::instance()
{
	#if defined(IOS)
	static FileSystem* instance_ = new FileSystem_IOS();
	#elif defined(ANDROID)
	static FileSystem* instance_ = new FileSystem_ANDROID();
#else
	static FileSystem* instance_ = new FileSystem();
#endif
	return *instance_;
}


//================single instance, but not static access
class Singleton_NonStatic
{
public:
	Singleton_NonStatic()
	{
		//assert: 如果里面的条件是true, 就当没有这行代码, 如果是false, 游戏停在这里, 意在告诉你处理这个问题
		assert(!_has_initialized);
		_has_initialized = true;
	}
private:
	static bool _has_initialized;
};
bool Singleton_NonStatic::_has_initialized = false;


//==============an overall manager if singletons

class A_Manager
{
public:
	void Log() { std::cout << "Manager A logs" << std::endl; }
};
class B_Manager
{
public:
	void Log() { std::cout << "Manager B logs" << std::endl; }
};
class C_Manager
{
public:
	void Log() { std::cout << "Manager C logs" << std::endl; }
};

//自己是singleton, 其包含个各个manager不是singleton
class Singleton_Manager
{
public:
	static Singleton_Manager& instance()
	{
		if (_instance == NULL)
			_instance = new Singleton_Manager();
		return *_instance;
	}
	~Singleton_Manager()
	{
		if (am != NULL)
			delete am;
		if (bm != NULL)
			delete bm;
		if (cm != NULL)
			delete cm;
	}
	A_Manager& getAM() { return *am; }
	B_Manager& getBM() { return *bm; }
	C_Manager& getCM() { return *cm; }
private:
	Singleton_Manager() 
	{
		am = new A_Manager();
		bm = new B_Manager();
		cm = new C_Manager();
	}
	static Singleton_Manager* _instance;
	A_Manager* am;
	B_Manager* bm;
	C_Manager* cm;
};
Singleton_Manager* Singleton_Manager::_instance = NULL;