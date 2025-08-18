export module katve.tekgin.core.interfaces.saveable;
import std;

namespace Tekgin
{
export struct ISaveable;
export template<class Saveable>
	requires std::is_base_of_v<ISaveable, Saveable>
struct SaveFile;

/**
 * @brief Save an object ont onto disk under
 *
 * @tparam T Class of the object to save to disk
 * @return SaveFile that refers to the saved object
 */
export template<class T>
	requires std::is_base_of_v<ISaveable, T>
auto SaveToDisk(T obj);

export template<class T>
	requires std::is_base_of_v<ISaveable, T>
auto LoadFromDisk(std::string_view path);


export struct ISaveable
{
	ISaveable(const ISaveable&)            = default;
	ISaveable(ISaveable&&)                 = default;
	ISaveable& operator=(const ISaveable&) = default;
	ISaveable& operator=(ISaveable&&)      = default;
	ISaveable()                            = default;
	virtual ~ISaveable()                   = default;

	template<typename T>
	friend auto SaveToDisk(T);

	virtual void serialize(std::ostream&) const   = 0;
	virtual void deserialize(std::istream&) const = 0;
};

/**
 * @brief Consteval function so classes can specialize their path as the return
 *
 * @tparam T Any class that implements the ISaveable interface
 * @return Path relative to save folder where objects of class T are saved
 */
export template<class T>
	requires std::is_base_of_v<ISaveable, T>
consteval std::string_view getClassSaveRelPath();

export template<class T>
	requires std::is_base_of_v<ISaveable, T>
struct SaveFile
{
	using Type = T;

	SaveFile(const SaveFile&)            = delete;
	SaveFile(SaveFile&&)                 = delete;
	SaveFile& operator=(const SaveFile&) = delete;
	SaveFile& operator=(SaveFile&&)      = delete;
	SaveFile()                           = delete;
	~SaveFile()                          = default;

	explicit SaveFile(T);

	std::string  path = getClassSaveRelPath<T>();
	std::fstream file;
};

} // namespace Tekgin
