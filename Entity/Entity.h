#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include "/workspaces/Cpp-RPG/Moves/Move.h"
#include <cstdlib>

class Entity
{
private:
	std::string name;

	int hp;
	int maxHp;
	int mp;
	int sp;

	int level;
	int exp;

	int atkPow;
	int defPow;
	bool isBurned;
	bool isStunned;

	std::vector<Move> moves;

public:
	Entity()
	{
		hp = 0;
		maxHp = 0;
		mp = 0;
		sp = 0;

		level = 1;
		exp = 0;

		atkPow = 0;
		defPow = 0;
		isBurned = false;
		isStunned = false;
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

	std::string getName()
	{
		return name;
	}

	int getHp()
	{
		return hp;
	}

	int getSp()
	{
		return sp;
	}

	int getLevel()
	{
		return level;
	}

	int getExp()
	{
		return exp;
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
					  << std::endl;
		}
	}

	void useMove(int index, Entity &target)
	{
		Move move = moves[index];
		int effect = move.getEffectType();

		// Accuracy check
		int roll = rand() % 100;

		if (roll >= move.getAccuracy())
		{
			std::cout << name << " used "
					  << move.getName()
					  << " but missed!\n";
			return;
		}

		if (effect == EFFECT_HEAL)
		{
			int healAmount = 20;

			hp += healAmount;
			if (hp > maxHp)
				hp = maxHp;

			std::cout << name << " healed for "
					  << healAmount << " HP !\n";

			return;
		}

		// Critical hit check
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

		if (effect == EFFECT_BURN)
		{
			target.isBurned = true;
			std::cout << target.getName() << " was burned!\n";
		}
		else if (effect == EFFECT_STUN)
		{
			target.isStunned = true;
			std::cout << target.getName() << " was stunned!\n";
			return;
		}
	}

	void takeDamage(int dmg)
	{
		hp -= dmg;

		if (hp < 0)
			hp = 0;

		std::cout << name << " HP: " << hp << std::endl;
	}

	void applyStatus()
	{
		if (isBurned)
		{
			int burnDamage = 5;
			hp -= burnDamage;

			if (hp < 0)
				hp = 0;

			std::cout << name << " is burned and takes "
					  << burnDamage << " damage!\n";
		}
	}

	bool canAct()
	{
		if (isStunned)
		{
			std::cout << name << " is stunned and cannot move!\n";
			isStunned = false; // wears off after one turn
			return false;
		}
		return true;
	}

	void levelUp()
	{
		level++;

		exp -= 100;

		maxHp += 10;
		hp = maxHp;

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

		std::cout << "Attack increased to "
				  << atkPow
				  << "\n";

		std::cout << "Defense increased to "
				  << defPow
				  << "\n";
	}
};

#endif