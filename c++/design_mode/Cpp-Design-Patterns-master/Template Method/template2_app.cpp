#include "template2_lib.cpp"
#include <iostream>

using namespace std;

class Application : public Library
{
  protected:
	virtual bool Step2()
	{
		cout << "override Step2" << endl;
		return true;
	}

	virtual void Step4()
	{
		cout << "override Step4" << endl;
	}
};

int main()
{
	Library *pLib = new Application();
	pLib->Run();//run 流程在基类已经定义好了，属于不变的部分，变的部分在Step2和step3在子类重写了，更改step2 和
  //step3，  基类不用改，后期绑定的方法，实现基类函数对派生类的调用
	delete pLib;
}
