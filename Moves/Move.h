#ifndef MOVE_H
#define MOVE_H
#include "GameEnums.h"
#include <string>

class Move
{
  private:
	std::string name;
	int power;
	int accuracy;
	int mpCost;
	StatusType statusType;
	

  public:
	Move(std::string n, int p, int a, int m, StatusType eType)
	{
		name = n;
		power = p;
		mpCost = m;
		accuracy = a;
		statusType = eType;
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

	StatusType getStatusType() const
	{
		return statusType;
	}
};

#endif