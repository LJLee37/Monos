//Monos Battle System
//2018.05.07 20:30(rewrite date) GMT +9
#include "Monoslib.h"
#line 1 "Monos_Battle.cpp"
/*
bool runtime_test()
{
	//func_code & func_time
	Character t1, t2("monster",2);
	runtime_test = true;
	cout << "런타임 테스트중...";
}*/
int battle(Character *C1, Character *C2)
{
	try
	{
		//...
	}
	catch(int exception)
	{
		ofstream log;
		log.open("Monos_Battle_log.txt");
		log.close();
		cout << "Log writing complete. Exiting..." << endl;
		return 0;
	}
}
int main()
{
	/*if(runtime_test())
	{
		cout << "런타임 테스트 성공!" << endl;
		battle();
	}
	return 0;*/
}
