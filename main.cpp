#include <iostream>
#include <ctime>
#include "/workspaces/Cpp-RPG/Battle System/BattleSystem.h"

int main()
{
	srand(time(0));

	Entity player;
	Entity enemy;

	player.setName("Hero");
	player.setHp(100);
	player.setSp(80);
	player.setAtk(40);
	player.setDef(30);

	enemy.setName("Drake");
	enemy.setHp(100);
	enemy.setSp(60);
	enemy.setAtk(20);
	enemy.setDef(50);

	Move flamethrower("Flamethrower", 40, 90, EFFECT_BURN);
	Move starlight("Starlight Flash", 30, 85, EFFECT_NONE);
	Move airShred("Air Shredder", 35, 80, EFFECT_STUN);
	Move crash("Crash Into", 50, 50, EFFECT_NONE);
	Move healingLight("Healing Light", 0, 100, EFFECT_HEAL);

	player.addMove(flamethrower);
	player.addMove(starlight);
	player.addMove(healingLight);

	enemy.addMove(airShred);
	enemy.addMove(crash);

	BattleSystem battle;

	battle.startBattle(player, enemy);

	return 0;
}