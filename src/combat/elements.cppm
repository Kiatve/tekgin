/**
 * @file
 * @brief Element enum class and ElementMap<T> class for creating easy associative arrays of elements and values
 */
module;
#include <cassert>
export module katve.tekgin.combat.elements;
import std;

export namespace Tekgin
{

/** @brief Elements for damage types etc.
 *
 * @note COUNT is always the last member to get the size at compile time,
 * though this might be removed in the future as it would be safer to simply
 * have a compile time constant that is the size of the enum
 */
enum class Element : std::uint8_t { none = 0, all, fire, cold, lightning, poison, count };

using enum Element;

/**
 * @brief Specialized class to associate balues with elements without the
 * overhead of a map
 *
 * @tparam T Type of the underlying data
 */
template<typename T>
struct ElementMap
{
 private:
	/// @brief Size of the underlying array
	static constinit const std::uint8_t k_size = std::to_underlying(count);

	std::array<T, k_size> m_data{}; ///< @brief Underlying array of the map

	/// @brief Convert Element to corresponding index
	static constexpr std::uint8_t toIndex(Element element)
	{
		assert(element != count && "Element::COUNT is not a valid value");
		return std::to_underlying(element);
	}

 public:
	void set(Element element, const T& value) { m_data.at(toIndex(element)) = value; } ///< @brief Set value at element
	constexpr T  get(Element element) const { return m_data.at(toIndex(element)); }    ///< @brief Get value at element
	constexpr T& get(Element element) { return m_data.at(toIndex(element)); }          ///< @brief Get value at element

	constexpr T&       operator[](Element element) { return m_data[toIndex(element)]; }
	constexpr const T& operator[](Element element) const { return m_data[toIndex(element)]; }

	constexpr ElementMap& operator+=(const ElementMap& rhs)
	{
		for (std::uint8_t i = 0; i < k_size; ++i) { this->m_data[i] += rhs.m_data[i]; }
	};

	constexpr ElementMap& operator-=(const ElementMap& rhs)
	{
		for (std::uint8_t i = 0; i < k_size; ++i) { this->m_data[i] -= rhs.m_data[i]; }
	};

	friend ElementMap operator+(ElementMap lhs, const ElementMap& rhs) { return lhs += rhs; };
	friend ElementMap operator-(ElementMap lhs, const ElementMap& rhs) { return lhs += rhs; };
};
} // namespace Tekgin
