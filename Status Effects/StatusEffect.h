#ifndef STATUS_EFFECTS_H
#define STATUS_EFFECTS_H
#include <string>
#include "GameEnums.h"

class StatusEffect
{
  private:
	std::string name;
	std::string description;
	int duration;
	int damagePerTurn;
	int attackModifier;
	int defenseModifier;

	StatusType type;

	bool preventsAction;

  public:
	StatusEffect(std::string statusName,
				 std::string statusDescription,
				 int turns,
				 int damage,
				 int atkMod,
				 int defMod,
				 StatusType statusType,
				 bool stopAction)
	{
		name = statusName;
		description = statusDescription;
		duration = turns;
		damagePerTurn = damage;
		attackModifier = atkMod;
		defenseModifier = defMod;
		type = statusType;
		preventsAction = stopAction;
	}

	std::string getName() const
	{
		return name;
	}

	std::string getDescription() const
	{
		return description;
	}

	int getDuration() const
	{
		return duration;
	}

	int getAttackModifier() const
	{
		return attackModifier;
	}

	int getDefenseModifier() const
	{
		return defenseModifier;
	}

	StatusType getType() const
	{
		return type;
	}

	int getDamagePerTurn() const
	{
		return damagePerTurn;
	}

	bool doesPreventAction() const
	{
		return preventsAction;
	}

	bool dealsDamage() const
	{
		return damagePerTurn > 0;
	}

	void reduceDuration()
	{
		if (duration > 0)
		{
			duration--;
		}
	}

	bool hasExpired() const
	{
		return duration <= 0;
	}
};

#endif