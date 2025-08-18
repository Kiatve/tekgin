export module katve.tekgin.core.character;
import std;

import katve.tekgin.combat.elements;

export namespace Tekgin
{
/// Base class for all characters (e.g. enemies, NPCs, player)
class Character
{

 public:
	/// Character size classes
	enum class Size : std::uint8_t { tiny = 0, small = 1, medium = 1, large = 2, huge = 3 };

	/// Contains attributes of character
	struct Attributes
	{
		int  vitality{}, endurance{}, strength{}, dexterity{};  // Physical
		int  charisma{}, intelligence{}, wisdom{}, willpower{}; // Mental
		Size size = Size::medium;
	};

	const Attributes& getAttributes() { return attributes; }

	/// Contains stats of character
	struct Stats
	{
		int health{}, stamina{}, mana{}, range{}, speed{}, defense{};

		Stats& operator+=(const Stats& rhs);
		Stats& operator-=(const Stats& rhs);
	};


	friend Stats operator+(Stats lhs, const Stats& rhs) { return lhs += rhs; };
	friend Stats operator-(Stats lhs, const Stats& rhs) { return lhs += rhs; };

	/// Get stats with or without bonuses applied
	Stats getStats(bool with_bonuses = false) const { return with_bonuses ? stats + bonus : stats; }

 protected:
	Attributes attributes;
	Stats      stats, bonus;

	ElementMap<double> m_resistances;
	ElementMap<double> m_weaknesses;

 public:
	Character(const Character&)            = default;
	Character(Character&&)                 = default;
	Character& operator=(const Character&) = default;
	Character& operator=(Character&&)      = default;
	virtual ~Character()                   = default;

	Character(Attributes attributes, ElementMap<double> resistances = {}, ElementMap<double> weaknesses = {});

	/// Reduce health by damage - defense and apply relevant m_resistances and m_weaknesses
	virtual void takeDamage(int damage, const Element& damage_type);

	/// Initialize stats for character
	virtual void updateStats();

	void                             setResistance(Element element, double value) { m_resistances[element] = value; }
	[[nodiscard]] ElementMap<double> getResistances() { return m_resistances; }
	[[nodiscard]] double             getResistance(Element element) const { return m_resistances[element]; }

	void                             setWeakness(Element element, double value) { m_weaknesses[element] = value; }
	[[nodiscard]] ElementMap<double> getWeaknesses() { return m_weaknesses; }
	[[nodiscard]] double             getWeakness(Element element) const { return m_weaknesses[element]; }
};
} // namespace Tekgin
