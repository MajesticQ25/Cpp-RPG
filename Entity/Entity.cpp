#include "Entity.h"
#include <iostream>

void Entity::equipWeapon(const Equipment &weapon)
{
	equippedWeapon = weapon;

	std::cout << name << " equipped a weapon!\n";
}

void Entity::equipArmor(const Equipment &armor)
{
	equippedArmor = armor;

	std::cout << name << " equipped armor!\n";
}

void Entity::unequipWeapon()
{
	if (!equippedWeapon.has_value())
	{
		std::cout << name << " has no weapon equipped!\n";
		return;
	}

	equippedWeapon.reset();

	std::cout << name << " unequipped their weapon!\n";
}

void Entity::unequipArmor()
{
	if (!equippedArmor.has_value())
	{
		std::cout << name << " has no armor equipped!\n";
		return;
	}

	equippedArmor.reset();

	std::cout << name << " unequipped their armor!\n";
}

const Equipment *Entity::getEquippedWeapon() const
{
	if (!equippedWeapon.has_value())
	{
		return nullptr;
	}

	return &equippedWeapon.value();
}

const Equipment *Entity::getEquippedArmor() const
{
	if (!equippedArmor.has_value())
	{
		return nullptr;
	}

	return &equippedArmor.value();
}

void Entity::collectEquipmentModifiers(
	const Equipment &item,
	StatType stat,
	float &flatBonus,
	float &percentBonus) const
{
	for (const StatModifier &modifier : item.getModifiers())
	{
		if (modifier.stat == stat)
		{
			if (modifier.modifierType == ModifierType::Flat)
			{
				flatBonus += modifier.value;
			}
			else if (modifier.modifierType == ModifierType::Percent)
			{
				percentBonus += modifier.value;
			}
		}
	}
}

int Entity::getEffectiveAtk()
{

	float flatBonus = 0.0f;
	float percentBonus = 0.0f;

	// STEP 1: Collect equipment modifiers
	if (equippedWeapon.has_value())
	{
		collectEquipmentModifiers(equippedWeapon.value(), StatType::Attack, flatBonus, percentBonus);
	}

	if (equippedArmor.has_value())
	{
		collectEquipmentModifiers(equippedArmor.value(), StatType::Attack, flatBonus, percentBonus);
	}

	// STEP 2: Calculate Attack with equipment bonuses
	float effectiveAtk =
		(atkPow + flatBonus) * (1.0f + percentBonus);

	// STEP 3: Apply temporary status effects

	for (const StatusEffect &effect : activeEffects)
	{
		if (!effect.hasExpired())
		{
			effectiveAtk *= (1.0f + effect.getAttackModifier());
		}
	}

	if (effectiveAtk < 0.0f)
		effectiveAtk = 0.0f;

	return static_cast<int>(effectiveAtk);
}

int Entity::getEffectiveDef()
{
	float flatBonus{0.0f};
	float percentBonus{0.0f};

	if (equippedWeapon.has_value())
	{
		collectEquipmentModifiers(equippedWeapon.value(), StatType::Defense, flatBonus, percentBonus);
	}

	if (equippedArmor.has_value())
	{
		collectEquipmentModifiers(equippedArmor.value(), StatType::Defense, flatBonus, percentBonus);
	}

	float effectiveDef = (defPow + flatBonus) * (1.0f + percentBonus);

	for (const StatusEffect &effect : activeEffects)
	{
		if (!effect.hasExpired())
		{
			effectiveDef *= (1.0f + effect.getDefenseModifier());
		}
	}

	if (effectiveDef < 0)
	{
		effectiveDef = 0;
	}

	return static_cast<int>(effectiveDef);
}

void Entity::showMoves()
{
	std::cout << name << "'s Moves:\n";

	for (std::size_t i{0}; i < moves.size(); ++i)
	{
		const Move &move = moves[i];

		std::cout << i + 1 << ". "
				  << move.getName()
				  << " (Power: " << move.getPower()
				  << ", MP Cost: " << move.getMpCost()
				  << ", Accuracy: " << move.getAccuracy()
				  << "%)\n";
	}
}

void Entity::showStats()
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

	std::cout << "Attack  : " << getEffectiveAtk() << "  (Base: " << getAtk() << ")\n";
	std::cout << "Defense : " << getEffectiveDef() << " (Base: " << getDef() << ")\n";
	std::cout
		<< "Status :";

	if (activeEffects.empty())
	{
		std::cout << " None\n";
	}
	else
	{
		std::cout << "\n";
		for (const StatusEffect &effect : activeEffects)
		{
			std::cout << " - " << effect.getName()
					  << " (Duration: " << effect.getDuration() << " turns)\n";
		}
	}
}