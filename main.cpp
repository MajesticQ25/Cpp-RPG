#include <iostream>
#include <ctime>
#include "/workspaces/Cpp-RPG/Entity/Entity.h"
#include "/workspaces/Cpp-RPG/Battle System/BattleSystem.h"
#include "/workspaces/Cpp-RPG/Status Effects/StatusEffect.h"
#include "/workspaces/Cpp-RPG/Database/StatusDatabase.h"

int main()
{
	srand(time(0));

	Entity player;
	Entity enemy;

	player.setName("Hero");
	player.setHp(100);
	player.setMp(150);
	player.setSp(80);
	player.setAtk(40);
	player.setDef(30);

	enemy.setName("Drake");
	enemy.setHp(100);
	enemy.setMp(150);
	enemy.setSp(60);
	enemy.setAtk(20);
	enemy.setDef(50);

	enemy.setExpReward(100);

	Move flamethrower(
		"Flamethrower",
		40, // power
		90, // accuracy
		10, // mp cost
		StatusType::Burn);

	Move starlight(
		"Starlight Flash",
		30, // power
		85, // accuracy
		20, // mp cost
		StatusType::None);

	Move airShred(
		"Air Shredder",
		35, // power
		80, // accuracy
		10, // mp cost
		StatusType::None);

	Move crash(
		"Crash Into",
		50, // power
		50, // accuracy
		10, // mp cost
		StatusType::None);

	Move healingLight(
		"Healing Light",
		0,	 // power
		100, // accuracy
		10,	 // mp cost
		StatusType::Heal);

	player.addMove(flamethrower);
	player.addMove(starlight);
	player.addMove(healingLight);

	StatusType type = flamethrower.getStatusType();

	StatusEffect effect =
		StatusDatabase::getStatus(type);

	enemy.addMove(airShred);
	enemy.addMove(crash);

	BattleSystem battle;

	battle.startBattle(player, enemy);

	return 0;
}