#ifndef STATUS_DATABASE_H
#define STATUS_DATABASE_H
#include "/workspaces/Cpp-RPG/Status Effects/StatusEffect.h"

class StatusDatabase
{
public:
	static StatusEffect getStatus(StatusType type)
	{
		switch (type)
		{
		case StatusType::Burn:
			return StatusEffect(
				"Burn",													   // Name
				"Target loses HP every round. Target's attack is halved.", // Description
				3,														   // Duration (turns)
				5,														   // Damage
				-0.5,													   // Attack Modifier
				0,														   // Defense Modifier
				StatusType::Burn,										   // Type
				false													   // Prevent Action
			);

		case StatusType::Stun:

			return StatusEffect(

				"Stun",
				"Cannot act.",
				1,
				0,
				0,
				0,
				StatusType::Stun,
				true);

		default:

			return StatusEffect(
				"None",
				"No Effect",
				0,
				0,
				0,
				0,
				StatusType::None,
				false);
		}
	}
};
#endif