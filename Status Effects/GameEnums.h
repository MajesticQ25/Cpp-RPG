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

enum DamageType
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

enum TargetType
{
	Self,
	Single_Enemy,
	All_Enemies,
	Multiple_Enwmies,
	Single_Ally,
	All_Allies
};

#endif