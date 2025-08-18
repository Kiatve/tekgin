export module katve.tekgin.combat.attacks;
import std;

import katve.tekgin.combat.elements;
import katve.tekgin.core.character;

namespace Tekgin
{
export struct AttackResult;

export template<class C>
concept Attacker = requires(const C& c) {
	c.attack();
	std::is_base_of_v<Character, C>;
};

export struct Attack
{
	enum class Kind : std::uint8_t { melee, ranged, magic };
	using enum Kind;

	Kind    kind         = Kind::melee;
	Element element      = Element::none;
	double  damage_coeff = 1.0, range_coeff = 1.0, speed_coeff = 1.0; ///< @brief Stat coefficients of attach

	/**
	 * @brief Get AttackResult for attack.
	 *
	 * @param attacker Owner of the attack
	 * @return The result of the attack
	 *
	 * @todo Implement support for items, likely remove and handle logic elsewhere
	 */
	AttackResult getResult(Attacker auto& attacker);
};

export struct AttackResult
{
	Attack::Kind kind    = Attack::Kind::melee;
	Element      element = Element::none;
	int          damage = 0, range = 0, speed = 0; ///< @brief Stats of attack
};

} // namespace Tekgin
