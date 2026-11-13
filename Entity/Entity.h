#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include "../Moves/Move.h"
#include <cstdlib>
#include "../Status Effects/StatusEffect.h"
#include "../Database/StatusDatabase.h"
#include "../Equipment/Equipment.h"
#include <optional>

class Entity
{
private:
	std::string name;

	int hp;
	int maxHp;
	int mp;
	int maxMp;
	int sp;

	int level;
	int exp;
	int maxExp;
	int expReward;

	int atkPow;
	int defPow;

	std::vector<StatusEffect> activeEffects;
	std::vector<Move> moves;
	std::optional<Equipment> equippedWeapon;
	std::optional<Equipment> equippedArmor;

	void collectEquipmentModifiers(
		const Equipment &item,
		StatType stat,
		float &flatBonus,
		float &percentBonus) const;

public:
	Entity()
	{

		hp = 0;
		maxHp = 0;
		mp = 0;
		maxMp = 0;
		sp = 0;

		level = 1;
		exp = 0;
		maxExp = 100;
		expReward = 0;

		atkPow = 0;
		defPow = 0;
	}

	bool isAlive()
	{
		return hp > 0;
	}

	void setName(std::string n)
	{
		name = n;
	}

	void setHp(int value)
	{
		hp = value;
		maxHp = value;
	}

	void setMp(int value)
	{
		mp = value;
		maxMp = value;
	}

	void setSp(int value)
	{
		sp = value;
	}

	void setAtk(int value)
	{
		atkPow = value;
	}

	void setDef(int value)
	{
		defPow = value;
	}

	void setMaxExp(int value)
	{
		maxExp = value;
	}

	void setExpReward(int value)
	{
		expReward = value;
	}

	std::string getName()
	{
		return name;
	}

	int getHp()
	{
		return hp;
	}

	int getMaxHp()
	{
		return maxHp;
	}

	int getMp()
	{
		return mp;
	}

	int getMaxMp()
	{
		return maxMp;
	}

	int getSp()
	{
		return sp;
	}

	int getAtk()
	{
		return atkPow;
	}

	int getEffectiveAtk();

	int getDef()
	{
		return defPow;
	}

	int getEffectiveDef();

	int getLevel()
	{
		return level;
	}

	int getExp()
	{
		return exp;
	}

	int getMaxExp()
	{
		return maxExp;
	}

	int getExpReward()
	{
		return expReward;
	}

	int getMoveCount()
	{
		return moves.size();
	}

	void equipWeapon(const Equipment &weapon);
	void equipArmor(const Equipment &armor);
	const Equipment *getEquippedArmor() const;
	void unequipArmor();
	void unequipWeapon();

	const Equipment *getEquippedWeapon() const;

	void addMove(Move move)
	{
		moves.push_back(move);
	}

	void showMoves();

	void useMove(int index, Entity &target)
	{
		Move move = moves[index];
		StatusType type = move.getStatusType();

		StatusEffect effect = StatusDatabase::getStatus(type);

		if (mp < move.getMpCost())
		{
			std::cout << "Not enough MP!\n";
			return;
		}

		mp -= move.getMpCost();

		//-----------------/
		// Accuracy Check   /
		//-----------------/

		int roll = rand() % 100;

		if (roll >= move.getAccuracy())
		{
			std::cout << name << " used "
					  << move.getName()
					  << " but missed!\n";
			return;
		}

		//------------------/
		// Healing Effect    /
		//------------------/

		if (type == StatusType::Heal)
		{
			int healAmount = 20;

			hp += healAmount;
			if (hp > maxHp)
				hp = maxHp;

			std::cout << name << " healed for "
					  << healAmount << " HP !\n";

			return;
		}
		//--------------------/
		// Critical hit check/
		//------------------/

		bool isCrit = (rand() % 100) < 10;

		int damage = (getEffectiveAtk() + move.getPower()) - target.getEffectiveDef();

		if (isCrit)
			damage *= 2;

		if (damage < 1)
			damage = 1;

		std::cout << name << " used "
				  << move.getName() << "!\n";

		if (isCrit)
			std::cout << "Critical Hit!\n";

		std::cout << "It dealt "
				  << damage << " damage!\n";

		target.takeDamage(damage);

		std::cout << target.getName()
				  << " HP: " << target.getHp()
				  << "/" << target.getMaxHp() << "\n";

		//------------------/
		// Effects          /
		//------------------/

		if (effect.getType() != StatusType::None)
		{
			target.addStatusEffect(effect);
		}
	}

	//-------------------
	// Damage Calc
	//-------------------

	void takeDamage(int dmg)
	{
		hp -= dmg;

		if (hp < 0)
			hp = 0;
	}

	void applyStatus()
	{
		for (auto it = activeEffects.begin(); it != activeEffects.end();)
		{
			if (it->dealsDamage())
			{
				int damage = it->getDamagePerTurn();

				takeDamage(damage);

				std::cout << name
						  << " takes "
						  << damage
						  << " damage from "
						  << it->getName()
						  << "!\n";

				std::cout << name << " HP: " << hp << std::endl;
			}

			it->reduceDuration();

			if (it->hasExpired())
			{
				std::cout << it->getName()
						  << " has worn off!\n";

				it = activeEffects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	bool canAct()
	{
		for (StatusEffect &effect : activeEffects)
		{
			if (effect.doesPreventAction() && !effect.hasExpired())
			{
				std::cout << name
						  << " cannot act because of "
						  << effect.getName()
						  << "!\n";

				return false;
			}
		}

		return true;
	}

	void gainExp(int amount)
	{
		exp += amount;

		std::cout << name
				  << " gained "
				  << amount
				  << " EXP!\n";

		while (exp >= maxExp)
		{
			levelUp();
		}
	}

	void levelUp()
	{
		level++;

		exp -= maxExp;
		maxExp += 50;

		maxHp += 10;
		hp = maxHp;

		maxMp += 5;
		mp = maxMp;

		atkPow += 5;
		defPow += 3;

		std::cout << "\n*** LEVEL UP! ***\n";

		std::cout << name
				  << " reached Level "
				  << level
				  << "!\n";

		std::cout << "HP increased to "
				  << maxHp
				  << "\n";

		std::cout << "MP increased to "
				  << maxMp
				  << "\n";

		std::cout << "Attack increased to "
				  << atkPow
				  << "\n";

		std::cout << "Defense increased to "
				  << defPow
				  << "\n";
	}

	void showStats();

	void addStatusEffect(StatusEffect effect)
	{
		if (!isAlive())

		{
			return;
		}
		for (StatusEffect &activeEffect : activeEffects)
		{
			if (activeEffect.getType() == effect.getType() && !activeEffect.hasExpired() && hp > 0)
			{
				std::cout << name
						  << " is already afflicted with "
						  << effect.getName()
						  << "!\n";

				return;
			}
		}

		activeEffects.push_back(effect);

		if (hp > 0)
		{
			std::cout << name
					  << " is afflicted with "
					  << effect.getName()
					  << "!\n";
		}
		// else
		// {
		// 	std::cout << name
		// 			  << " has been defeated and cannot be afflicted with "
		// 			  << effect.getName()
		// 			  << "!\n";
		// }
	}
};

#endif