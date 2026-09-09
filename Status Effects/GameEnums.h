#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

enum class StatusType
{
	None,
	Burn,
	Stun,
	Poison,
	Freeze,
	Sleep,
	Paralysis,
	Bleed,
	Regen,
	Crit_Up,
	Heal
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
	NearbyEnemies,
	SingleAlly,
	AllAllies
};

#endif