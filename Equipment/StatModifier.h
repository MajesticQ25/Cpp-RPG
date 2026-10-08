#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

enum class StatType
{
	Attack,
	Defense,
	Speed,
	MaxHP,
	MaxMP,
	Magic,
	Strength,
	Agility,
	MagicAttack,
	MagicDefense
};

enum class ModifierType
{
	Flat,
	Percent
};

struct StatModifier
{
	StatType stat;
	float value;
	ModifierType modifierType;
};

#endif