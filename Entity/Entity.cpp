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