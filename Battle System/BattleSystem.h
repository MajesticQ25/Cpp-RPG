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
		{
			player.applyStatus();
			return;
		}

		player.applyStatus();

		if (!player.isAlive())
		{
			return;
		}

		player.useMove(choice - 1, enemy);
	}

	void enemyTurn(Entity &enemy, Entity &player)
	{
		std::cout << "\n---- Enemy Turn ----\n";
		if (!enemy.canAct())
		{
			enemy.applyStatus();
			return;
		}

		enemy.applyStatus();

		if (!enemy.isAlive())

		{
			return;
		}

		int move = rand() % enemy.getMoveCount();

		enemy.useMove(move, player);
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
		{
			std::cout << "\nVictory!\n";

			player.gainExp(enemy.getExpReward());
		}
		else
			std::cout << "\nYou were defeated.\n";
	}

	void showBattleState(Entity &player, Entity &enemy)
	{
		std::cout << "\n===== BATTLE STATUS =====\n";

		std::cout << player.getName() << " LVL: "
				  << player.getLevel()
				  << " HP: "
				  << player.getHp()
				  << " EXP: "
				  << player.getExp()
				  << "/100\n";

		std::cout << enemy.getName()
				  << " HP: "
				  << enemy.getHp()
				  << "\n";

		std::cout << "=========================\n";
	}
};

#endif