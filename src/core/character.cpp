module katve.tekgin.core.character;
import std;

import katve.tekgin.combat.elements;

namespace Tekgin
{
Character::Stats& Character::Stats::operator+=(const Character::Stats& rhs)
{
	this->health += rhs.health;
	this->stamina += rhs.stamina;
	this->mana += rhs.mana;
	this->range += rhs.range;
	this->speed += rhs.speed;
	this->defense += rhs.defense;
	return *this;
}

Character::Stats& Character::Stats::operator-=(const Character::Stats& rhs)
{
	this->health -= rhs.health;
	this->stamina -= rhs.stamina;
	this->mana -= rhs.mana;
	this->range -= rhs.range;
	this->speed -= rhs.speed;
	this->defense -= rhs.defense;
	return *this;
}

Character::Character(Attributes attributes, ElementMap<double> resistances, ElementMap<double> weaknesses)
	 : attributes(attributes),
		stats(),
		bonus(),
		m_resistances(resistances),
		m_weaknesses(weaknesses)
{
	updateStats();
}

void Character::updateStats()
{
	// int  vitality{}, endurance{}, strength{}, dexterity{};  // Physical
	// int  charisma{}, intelligence{}, wisdom{}, willpower{}; // Mental
	const auto& attributes = this->attributes;
	this->stats.health     = attributes.vitality + attributes.endurance;
	this->stats.stamina    = attributes.endurance + attributes.willpower;
	this->stats.mana       = attributes.willpower + attributes.wisdom;
	this->stats.range      = static_cast<double>(attributes.size);
	this->stats.speed      = static_cast<double>(attributes.size) + attributes.dexterity;
	this->stats.defense    = attributes.endurance;
}

void Character::takeDamage(int damage, const Element& damage_type)
{
	damage *= 1 - getResistance(Element::all) + getWeakness(Element::all) - getResistance(damage_type)
	        + getWeakness(damage_type);
	damage = damage < 0 ? 0 : damage;
	stats.health -= damage;
}
} // namespace Tekgin
