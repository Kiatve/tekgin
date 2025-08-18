export module katve.tekgin.combat.enemy;
import std;

import katve.tekgin.core.character;
import katve.tekgin.core.interfaces.saveable;
import katve.tekgin.util.logging;

namespace Tekgin
{
export class Enemy : public Character, ISaveable
{
 public:
	Enemy(const Enemy&)            = default;
	Enemy(Enemy&&)                 = default;
	Enemy& operator=(const Enemy&) = default;
	Enemy& operator=(Enemy&&)      = default;
	~Enemy() override;

	Enemy(Character);

 private:
	static inline long s_count = 0;

	std::size_t m_id      = s_count++; // This is a placeholder, will be replaced with a proper uuid again
	std::size_t m_id_hash = std::hash<std::size_t>{}(m_id);

 public:
	void serialize(std::ostream& ostr) const override;
	void deserialize(std::istream& istr) const override;

	static long getCount() { return s_count; };
	static long decrementCount() { return --s_count; };

	[[nodiscard]] Util::LogData<int> logFormat() const;
};
} // namespace Tekgin
