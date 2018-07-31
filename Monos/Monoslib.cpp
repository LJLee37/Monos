#include "Monoslib.h"
bool probability(int percent)
{
	for (int temp = rand() % 100; percent >= 0; percent--)
		if (temp == percent)
			return true;
	return false;
}
/*
Character::Character(char character_name[20], short char_code = 0, int hp = 100000, int mp = 100, int atk = 100, int dfs = 100, int spl = 0, int srs = 0, int crt = 10)//apply stat
{
	HP = MaxHP = hp;
	MP = MaxMP = mp;
	Atk = atk;
	Dfs = dfs;
	Spl = spl;
	Srs = srs;
	Crt = crt;//critical is 100*percent(10 = 0.1%)
	//const char name[20] = { *character_name };
	character_code = char_code;
	bool ifbase_name = false;
	//if(name == base_name)
	//	ifbase_name = true;
	pre_atk_type = 0;
	//pre_ene_dmg = 10000;
}
*/
void Character::damage_in(int damage_type, int damage)
{
	switch (damage_type)
	{
	case Fixedtype:
		Stat[HP] -= damage;
		break;
	case ADtype:
		Stat[HP] -= ((100 * damage - Dfs) / (Dfs + 1));
		break;
	case APtype:
		Stat[HP] -= ((100 * damage - Srs) / (Srs + 10));
		break;
	}
}
int Character::damage_out(int damage_type)
{
	switch(damage_type)
	{
	case ADtype:
		return (Atk * Atk + 100) / (10000 - Atk) * 10000 / Atk;
		break;
	case APtype:
		return (Spl * (Spl + 100)) / (10000 - Spl) * 10000 / Spl;
	}
}
bool Character::HealByRatio(int heal_ratio)
{
	if (status == 4)
		return false;
	Stat[HP] += Stat[MaxHP] * (heal_ratio / 100.0);
	return true;
}
bool Character::HealByAmmount(int heal_ammount)
{
	if (status == 4)
		return false;
	Stat[HP] += heal_ammount;
	return true;
}
int Character::give_HP_by_100_percent()
{
	return (int)((double)HP / (double)MaxHP * 10000.0);
}
int Character::give_status()
{
	return status;
}
void Character::calc_value(Character *Enemy)
{
	//calculaing action's value
	switch(pre_atk_type)
	{
	case ADtype:
		atk_value += (Atk * 0.1 + (pre_ene_HP - Enemy->give_HP_by_100_percent())) * (Atk * 0.3 - (pre_ene_HP - Enemy->give_HP_by_100_percent())) / abs(Atk * 0.3 - (pre_ene_HP - Enemy->give_HP_by_100_percent()));
		break;
	case APtype:
		spl_atk_value += (Spl * 0.1 + (pre_ene_HP - Enemy->give_HP_by_100_percent())) * (Spl * 2 - (pre_ene_HP - Enemy->give_HP_by_100_percent())) / abs(Spl * 2 - (pre_ene_HP - Enemy->give_HP_by_100_percent()));
		break;
	}
	if(Spl == 0)
		spl_atk_value = 0;
	if((100 * HP / MaxHP) < 30)
		heal_value = 200;
	else
		heal_value = 100;
}
void Character::Status_check()
{
	status_duration--;
	if(status_duration <= 0)
	{
		status_duration = 0;
		status = nmlStas;
	}
	if (HP == 0)
	{
		status = deadStas;
		status_duration = 999999;
	}
	if (HP > MaxHP)
		Stat[HP] = MaxHP;
}
int Character::AI_action()
{
	cout << "AI is choosing action..." << endl;//choose action by action's value
	int priority1, priority2, priority3;
	if(atk_value >= spl_atk_value)
	{
		if(atk_value >= heal_value)
		{
			if(atk_value >= run_value)
				return 1;
			else
				return 3;
		}
		else
		{
			if(heal_value >= run_value)
			{
				priority1 = 4;
				if(atk_value >= run_value)
					priority2 = 1;
				else
					priority2 = 3;
			}
			else
				return 3;
		}
	}
	else
	{
		if(spl_atk_value >= heal_value)
		{
			if(spl_atk_value >= run_value)
			{
				priority1 = 2;
				if(atk_value >= heal_value)
					{
					if(atk_value >= run_value)
						priority2 = 1;
					else
						priority2 = 3;
				}
				else
				{
					if(heal_value >= run_value)
					{
						priority2 = 4;
						if(atk_value >= run_value)
							priority3 = 1;
						else
							priority3 = 3;
					}
					else
						priority2 = 3;
				}
			}
			else
			{
				if(heal_value >= run_value)
				{
					priority1 = 4;
					if(spl_atk_value >= run_value)
					{	
						priority2 = 2;
						if(atk_value >= run_value)
							priority3 = 1;
    					else
							priority3 = 3;
					}
					else
						priority2 = 3;
				}
			else
				return 3;
			}
		}
		else
		{
			if(heal_value >= run_value)
			{
				priority1 = 4;
				if(atk_value >= run_value)
						priority2 = 1;
					else
						priority2 = 3;
			}
			else
				return 3;
		}
	}
	switch(priority1)
	{
	case 2:
		if(MP >= 20)
			return priority1;
		else
		{
			switch(priority2)
			{
			case 1:
			case 3:
				return priority2;
				break;
			case 4:
				if(MP >= 10)
					return priority2;
				else
					return priority3;
			}
		}
		break;
	case 4:
		if(MP >= 10)
			return priority1;
		else
			return priority2;
	}
}
///*
int Character::action_choose(Character *Enemy)
{
	//clear screen
	cout << "추천도:" << endl;
	cout << "공격 : " << atk_value << endl;
	cout << "마법공격 : " << spl_atk_value << endl;
	cout << "도주 : " << run_value << endl;
	cout << "자가치유 : " << heal_value << endl;
	cout << endl;
	cout << "할 행동을 선택하십시오." << endl;
	cout << "1: 공격\t2: 마법공격(마나 20)" << endl;
	cout << "3: 도주\t4: 자가치유(마나 10)" << endl;
	cout << "선택 : ";
	int action;
    cin >> action;
	return action;
}
//*/
/*
int Character::AI_test(int v1, int v2, int v4, int mp)
{
	int t1, t2, t4, tmp, tmmp, rtn;
	t1 = atk_value;
	t2 = spl_atk_value;
	t4 = heal_value;
	tmp = MP;
	tmmp = MaxMP;
	atk_value = v1;
	spl_atk_value = v2;
	heal_value = v4;
	MP = MaxMP = mp;
	rtn = AI_action();
	atk_value = t1;
	spl_atk_value = t2;
	heal_value = t4;
	MP = tmp;
	MaxMP = tmmp;
	return rtn;
}
*/
void Character::Conduct_action(bool player, Character *Enemy)
{
	int action;
	if(player)
		action = action_choose(Enemy);
	else
		action = AI_action();
	switch(action)
	{
	case 1:
		Enemy->damage_in(ADtype,damage_out(ADtype));
		break;
	case 2:
		Enemy->damage_in(APtype,damage_out(APtype));
		Stat[MP] -= 20;
		break;
	case 3:
		//cout << name << "은(는) ";
		if(probability(50))
		{
			cout << "성공적으로 도망쳤다" << endl;
			//...
		}
		else
		{
			cout << "도망에 실패했다!" << endl;
			//...
		}
	}
}

void Character::level_up()
{
    //
}