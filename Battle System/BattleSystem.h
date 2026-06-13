#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <iostream>
#include <cstdlib>
#include "/workspaces/Cpp-RPG/Entity/Entity.h"

class BattleSystem
{
  public:
	void playerTurn(Entity &player, Entity &enemy)
	{
		std::cout << "\nChoose a move:\n";

		player.showMoves();

		int choice;
		std::cin >> choice;

		if (choice < 1 || choice > player.getMoveCount())
		{
			std::cout << "Invalid move!\n";
			return;
		}

		if (!enemy.isAlive())
		{
			return;
		}

		player.applyStatus();

		if (!player.canAct())
			return;

		player.useMove(choice - 1, enemy);
	}

	void enemyTurn(Entity &enemy, Entity &player)
	{
		std::cout << "\n---- Enemy Turn ----\n";

		int move = rand() % enemy.getMoveCount();

		enemy.useMove(move, player);

		if (!player.isAlive())
		{
			return;
		}

		enemy.applyStatus();

		if (!enemy.canAct())
			return;
	}

	void startBattle(Entity &player, Entity &enemy)
	{
		while (player.isAlive() && enemy.isAlive())
		{
			showBattleState(player, enemy);
			bool playerFirst = player.getSp() >= enemy.getSp();

			if (playerFirst)
			{
				playerTurn(player, enemy);

				if (enemy.isAlive())
					enemyTurn(enemy, player);
			}
			else
			{
				enemyTurn(enemy, player);

				if (player.isAlive())
					playerTurn(player, enemy);
			}
		}

		if (player.isAlive())
			std::cout << "\nVictory!\n";
		else
			std::cout << "\nYou were defeated.\n";
	}

	void showBattleState(Entity &player, Entity &enemy)
	{
		std::cout << "\n===== BATTLE STATUS =====\n";

		std::cout << player.getName()
				  << " HP: "
				  << player.getHp()
				  << "\n";

		std::cout << enemy.getName()
				  << " HP: "
				  << enemy.getHp()
				  << "\n";

		std::cout << "=========================\n";
	}
};

#endif