#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <string>
#include <vector>
#include "StatModifier.h"

class Equipment
{
private:
	std::string name;
	std::string description;
	std::string type;							// The type of equipment (e.g., weapon, armor, accessory)
	std::string rarity;							// The rarity of the equipment (e.g., common, rare, epic, legendary)
	std::string element;						// The elemental attribute of the equipment (e.g., fire, water, earth, air)
	std::string effect;							// The effect of the equipment (e.g., increase attack, increase defense, increase speed)
	std::string specialEffect;					// The special effect of the equipment (e.g., chance to inflict status effect, chance to double attack)
	std::string specialEffectDescription;		// The description of the special effect of the equipment
	std::string specialEffectType;				// The type of the special effect (e.g., status effect, double attack, etc.)
	std::string specialAbility;					// The special ability of the equipment (e.g., fireball, heal, etc.)
	std::vector<StatModifier> modifiers;		// The idea behind this is to store all the modifiers (atk, def, mag, etc...) into a vector and consolidate code while also making getting the modifiers that apply to each piece of equipent more manageable and efficient.
	std::vector<std::string> applicableClasses; // The classes that can equip this equipment (e.g., warrior, mage, rogue)
	int level;
	int attack;
	int defense;
	int randomStatBoost;
	int durability;
	float exp;
	float weight;

public:
	Equipment()
	{
		name = "";
		description = "";
		type = "";
		rarity = "";
		element = "";
		effect = "";
		specialEffect = "";
		specialEffectDescription = "";
		specialEffectType = "";
		specialAbility = "";
		modifiers = std::vector<StatModifier>();
		applicableClasses = std::vector<std::string>();
		level = 1;
		attack = 0;
		defense = 0;
		randomStatBoost = 0;
		durability = 100;
		exp = 0.0f;
		weight = 0.0f;
	}

	std::string getName() const { return name; }
	std::string getDescription() const { return description; }
	std::string getType() const { return type; }
	std::string getRarity() const { return rarity; }
	std::string getElement() const { return element; }
	std::string getEffect() const { return effect; }
	std::string getSpecialEffect() const { return specialEffect; }
	std::string getSpecialEffectDescription() const { return specialEffectDescription; }
	std::string getSpecialEffectType() const { return specialEffectType; }
	std::string getSpecialAbility() const { return specialAbility; }
	const std::vector<StatModifier> &getModifiers() const { return modifiers; }
	std::vector<std::string> getApplicableClasses() const { return applicableClasses; }
	int getLevel() const { return level; }
	int getAttack() const { return attack; }
	int getDefense() const { return defense; }
	int getRandomStatBoost() const { return randomStatBoost; }
	int getDurability() const { return durability; }
	float getExp() const { return exp; }
	float getWeight() const { return weight; }

	void addModifier(StatType stat, float value)
	{
		modifiers.push_back({stat, value});
	}

	std::string toString() const
	{
		std::string result = "Name: " + name + "\n";
		result += "Description: " + description + "\n";
		result += "Type: " + type + "\n";
		result += "Rarity: " + rarity + "\n";
		result += "Element: " + element + "\n";
		result += "Effect: " + effect + "\n";
		result += "Special Effect: " + specialEffect + "\n";
		result += "Special Effect Description: " + specialEffectDescription + "\n";
		result += "Special Effect Type: " + specialEffectType + "\n";
		result += "Special Ability: " + specialAbility + "\n";
		result += "Modifiers: ";

		for (const auto &modifier : modifiers)
		{
			result += "Stat: " + std::to_string(static_cast<float>(modifier.stat)) + ", Value: " + std::to_string(modifier.value) + ", ";
		}

		result += "\nApplicable Classes: ";

		for (const auto &applicableClass : applicableClasses)
		{
			result += applicableClass + ", ";
		}

		result += "\nLevel: " + std::to_string(level) + "\n";
		result += "Attack: " + std::to_string(attack) + "\n";
		result += "Defense: " + std::to_string(defense) + "\n";
		result += "Random Stat Boost: " + std::to_string(randomStatBoost) + "\n";
		result += "Durability: " + std::to_string(durability) + "\n";
		result += "Experience: " + std::to_string(exp) + "\n";
		result += "Weight: " + std::to_string(weight) + "\n";

		return result;
	}
};

#endif // EQUIPMENT_H