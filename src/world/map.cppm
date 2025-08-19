export module katve.tekgin.world.map;

import std;
import katve.tekgin.world.scene;


namespace Tekgin
{

export template<std::size_t width, std::size_t height>
class Map
{
 public:
	Tekgin::Scene operator[](std::size_t x, std::size_t y) { return m_world_map[y * width + x]; };
	Tekgin::Scene operator[](std::size_t x, std::size_t y) const { return m_world_map[y * width + x]; };

 private:
	std::array<Tekgin::Scene*, width * height> m_world_map;
};
} // namespace Tekgin
