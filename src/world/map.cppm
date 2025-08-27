export module katve.tekgin.world.map;

import std;
import katve.tekgin.world.scene;


namespace Tekgin
{

export template<std::size_t width, std::size_t height>
class Map
{
 public:
	// 2D access to world map
	Tekgin::Scene operator[](std::size_t x, std::size_t y) { return m_map[y * width + x]; };
	Tekgin::Scene operator[](std::size_t x, std::size_t y) const { return m_map[y * width + x]; };

	void setScene(Tekgin::Scene* scene_ptr, std::size_t x, std::size_t y) { m_map[x, y] = scene_ptr; };

 private:
	std::array<Tekgin::Scene*, width * height> m_map = {}; ///< 1D array storing the scenes
};
} // namespace Tekgin
