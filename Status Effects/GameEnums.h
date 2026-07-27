#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

enum class StatusType
{
	Burn,
	Stun,
	Poison,
	Freeze,
	Sleep,
	Paralysis,
	Bleed,
	Regen
};

enum class DamageType
{
	Physical,
	Fire,
	Water,
	Wind,
	Earth,
	Light,
	Umbra,
	Spirit
};

enum class TargetType
{
	Self,
	SingleEnemy,
	AllEnemies,
	MultipleEnemies,
	Nearby enemies,
	SingleAlly,
	AllAllies
};

#endif