#ifndef MOVE_H
#define MOVE_H
#define EFFECT_NONE 0
#define EFFECT_BURN 1
#define EFFECT_STUN 2
#define EFFECT_HEAL 3

#include <string>

class Move
{
  private:
	std::string name;
	int power;
	int accuracy;
	int mpCost;
	int effectType;
	

  public:
	Move(std::string n, int p, int a, int m, int e)
	{
		name = n;
		power = p;
		mpCost = m;
		accuracy = a;
		effectType = e;
	}

	std::string getName()
	{
		return name;
	}

	int getPower()
	{
		return power;
	}
	
	int getMpCost()
	{
		return mpCost;
	}

	int getAccuracy()
	{
		return accuracy;
	}

	int getEffectType()
	{
		return effectType;
	}
};

#endif