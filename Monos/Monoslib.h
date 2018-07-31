//Monos library
//2018.05.07 20:40
#ifndef MONOS_LIB1
#define MONOS_LIB1
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
using namespace std;
extern const char base_name[] = "Mona" ;
extern bool dev_mode = false;
enum {Fixedtype = 0, ADtype, APtype};
bool probability(int percent);
enum Action_type {Phs_attack = 1, Mgc_attack, Escape, Self_heal};
enum stats {HP = 0, MaxHP, MP, MaxMP, Atk, Dfs, Spl, Srs, Crt};//Attack, Defense, Spell Power, Spell Resistence, Critical
enum status_type {nmlStas = 0, slowStas, parzStas, stunStas, deadStas};//normal, slow, paralize, stun, dead
enum char_code {Player = 0, NPC, Monster};
class Character
{
protected:
	int Stat[9];//Attack, Defense, Spell Power, Spell Resistence, Critical
	int atk_value = 100, spl_atk_value = 100, heal_value = 100, run_value = 100;//value of action
	status_type status = nmlStas;
	short status_duration = 0;//each number is each turn
	char_code character_code = Player;
	int pre_atk_type = 0, pre_ene_HP = 10000;
public:
	Character(char character_name[20], char_code charac_code = Player, int hp = 100000, int mp = 100, int atk = 100, int dfs = 100, int spl = 0, int srs = 0, int crt = 10);//apply stat
	
	void damage_in(int damage_type, int damage);
	
	int damage_out(int damage_type);
	
	bool HealByRatio(int heal_ratio);
	
	bool HealByAmmount(int heal_ammount);
	
	int give_HP_by_100_percent();
	
	int give_status();
	
	void calc_value(Character *Enemy);
	
	void Status_check();
	
	int AI_action();

	int action_choose(Character *Enemy);
	
	int AI_test(int v1, int v2, int v4, int mp);
	
	void Conduct_action(bool player, Character *Enemy);
	
    void level_up();
};

#endif