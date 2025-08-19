export module katve.tekgin.world.scene;

import std;
import katve.tekgin.core.interfaces.object;

namespace Tekgin
{

// Forward declare class to avoid cyclic depndency, imported in the implementation
class Map;

struct Position
{
	int x = 0, y = 0;
};

/**
 * @class Scene
 * @brief Class for creating "scenes", environments that contain all characters and objects
 *
 */
export class Scene
{
 public:
	Scene(const Scene&)            = default;
	Scene(Scene&&)                 = delete;
	Scene& operator=(const Scene&) = default;
	Scene& operator=(Scene&&)      = delete;
	~Scene()                       = delete;

	enum class Terrain : std::int8_t { ocean, lake, mountain, forest, plains, village, city, inside, dungeon };
	using enum Terrain;

	Scene(Tekgin::Map* world, Position position, std::string name, char visual, Terrain terrain_type, std::vector<Scene*> children);

 private:
	Tekgin::Map* m_world;

 public:
	std::string           name;
	std::vector<Scene*>   children;
	std::vector<IObject*> objects;
	const Scene*          parent = nullptr; ///< nullptr if a root scene
	Position              position{ .x = 0, .y = 0 };
	Terrain               terrain_type = plains;
	char                  visual       = 'x';

	virtual void unloadResources();
};
} // namespace Tekgin
