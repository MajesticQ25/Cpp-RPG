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

	std::string getName()
	{
		return name;
	}

	std::string getDescription()
	{
		return description;
	}

	int getDuration()
	{
		return duration;
	}

	int getAttackModifier()
	{
		return attackModifier;
	}

	int getDefenseModifier()
	{
		return defenseModifier;
	}

	StatusType getType()
	{
		return type;
	}

	int getDamagePerTurn()
	{
		return damagePerTurn;
	}

	bool doesPreventAction()
	{
		return preventsAction;
	}
};

#endif