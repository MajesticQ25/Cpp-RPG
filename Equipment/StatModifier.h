#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

enum class StatType
{
    Attack,
    Defense,
    Speed,
    MaxHP,
    MaxMP,
    Magic
};

struct StatModifier
{
    StatType stat;
    float value;
};

#endif