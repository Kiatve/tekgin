module;
#include <cassert>
module katve.tekgin.combat.enemy;

using enum Tekgin::Util::Log::Level;

namespace Tekgin
{

Enemy::Enemy(Character character) : Character(std::move(character))
{
	Util::log(debug, "Constructed Enemy from Character ({})", s_count);
	Util::log(debug, *this);
	assert(s_count >= 0 && "Enemy count negative during contruction");
}

Enemy::~Enemy()
{
	assert(s_count >= 0 && "Enemy count negative after destruction");
	Util::log(debug, "Destructed Enemy({})", s_count--);
}

void Enemy::serialize(std::ostream& ostr) const { ostr << "Enemy"; }
void Enemy::deserialize(std::istream& istr) const { std::cout << istr.rdbuf(); }

Util::LogData<int> Enemy::logFormat() const { return Util::log_format_helper("Health: {}", this->stats.health); }
} // namespace Tekgin
