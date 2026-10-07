#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include "/workspaces/Cpp-RPG/Moves/Move.h"
#include <cstdlib>
#include "/workspaces/Cpp-RPG/Status Effects/StatusEffect.h"
#include "/workspaces/Cpp-RPG/Database/StatusDatabase.h"

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

	int getDef()
	{
		return defPow;
	}

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

	void addMove(Move move)
	{
		moves.push_back(move);
	}

	void showMoves()
	{
		for (size_t i = 0; i < moves.size(); i++)
		{
			std::cout << i + 1 << ". "
					  << moves[i].getName()
					  << "\n Power: "
					  << moves[i].getPower()
					  << " \n Accuracy: "
					  << moves[i].getAccuracy()
					  << "%\n"
					  << " \n MP Cost: "
					  << moves[i].getMpCost()
					  << std::endl;
		}
	}

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

		int damage = (atkPow + move.getPower()) - target.defPow;

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

		std::cout << name << " HP: " << hp << std::endl;
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

	void showStats()
	{

		std::cout << "=============================\n";
		std::cout << "         CHARACTER\n";
		std::cout << "=============================\n";

		std::cout << "Name    : " << getName() << "\n";
		std::cout << "Level   : " << getLevel() << "\n";
		std::cout << "EXP     : " << getExp() << "/" << getMaxExp() << "\n";

		std::cout << "HP      : " << getHp() << "/" << getMaxHp() << "\n";
		std::cout << "MP      : " << getMp() << "/" << getMaxMp() << "\n";
		std::cout << "SP      : " << getSp() << "\n";

		std::cout << "Attack  : " << getAtk() << "\n";
		std::cout << "Defense : " << getDef() << "\n";
		std::cout
			<< "Status :";

		/* if (StatusType::Burn)
		{
			std::cout << "Burned";
		}
		else if (StatusType::Stun)
		{
			std::cout << "Stunned";
		}
		else
		{
			std::cout << "Healthy";
		}

		std::cout << std::endl; */
	}

	void addStatusEffect(StatusEffect effect)
	{
		activeEffects.push_back(effect);

		std::cout << name
				  << " is afflicted with "
				  << effect.getName()
				  << "!\n";
	}
};

#endif