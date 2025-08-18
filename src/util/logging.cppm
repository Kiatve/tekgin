/** @file
 * @brief Implements logging functions and allows classes to have a formatter function to easily log the object
 */

export module katve.tekgin.util.logging;
import std;

import katve.tekgin.paths;
import katve.tekgin.constants;


using std::strcmp;

namespace Tekgin::Util
{

export namespace Log
{
	enum class Level : std::int8_t { fatal = -1, none, error, warn, info, debug, trace };
	[[gnu::const]] std::ostream& getStream(Level level = Level::info);
	[[gnu::const]] std::ostream& getFile();
}; // namespace Log

using enum Log::Level;

/// @brief The logging level set through an environment variable
export const Log::Level LOG_LEVEL = [] {
	const char* log_level_str = std::getenv("LOG_LEVEL");
	if (log_level_str != nullptr) {
		if (strcmp(log_level_str, "FATAL") == 0) { return fatal; }
		if (strcmp(log_level_str, "NONE") == 0) { return none; }
		if (strcmp(log_level_str, "ERROR") == 0) { return error; }
		if (strcmp(log_level_str, "WARN") == 0) { return warn; }
		if (strcmp(log_level_str, "INFO") == 0) { return info; }
		if (strcmp(log_level_str, "DEBUG") == 0) { return debug; }
		if (strcmp(log_level_str, "TRACE") == 0) { return trace; }
	}
	return info;
}();

[[gnu::always_inline]] inline bool shouldLog(Log::Level level) { return level <= LOG_LEVEL; }

std::string logLevelToString(Log::Level level);
export std::string logLevelLabel(Log::Level level);

/// @todo possible make fmt of type std::format_string
export template<typename... Args>
struct LogData
{
	std::string_view    fmt;
	std::tuple<Args...> args;
};

/// @brief Concept requiring the class to have the member function logFormat
template<typename T>
concept HasLogFormat = requires(const T& t) { t.logFormat(); };

/**
 * @brief Log a string into cout or cerr depending on log level or to specified stream
 *
 * @param level The verbosity/severity level of the log
 * @param fmt Format string
 * @tparam Args Any type that has std::format specialization
 * @param args Arguments for format string
 */
export template<typename... Args>
void log(Log::Level level, std::string_view fmt, Args&&... args)
{
	if (shouldLog(level)) {
		try {
			std::println(Log::getStream(level),
			             std::runtime_format(logLevelLabel(level) + ": " + fmt),
			             std::forward<Args>(args)...);
		} catch (const std::exception& e) {
			std::cerr << "ERROR: Logging to stdout/stderr failed: " << e.what() << "\n";
		}
	}
	try {
		std::println(Log::getFile(), std::runtime_format(logLevelLabel(level) + ": " + fmt), std::forward<Args>(args)...);
	} catch (const std::exception& e) {
		std::cerr << "ERROR: Logging to file failed: " << e.what() << "\n";
	}
}

/**
 * @brief Log a string into cout or cerr depending on log level
 *
 * @param fmt Format string
 * @tparam Args Any type that has std::format specialization
 * @param args Arguments for format string
 */
export template<typename... Args>
void log(const std::string& fmt, Args&&... args)
{
	log(info, fmt, std::forward<Args>(args)...);
}

/**
 * @brief Function to log a class
 *
 * @tparam T Type of the object
 * @param level The verbosity/severity level of the log
 * @param obj The object to log
 */
export template<typename T>
	requires HasLogFormat<T>
void log(Log::Level level, const T& obj)
{
	auto data = obj.logFormat();
	std::apply([level, &data](auto&&... args) { log(level, data.fmt, std::forward<decltype(args)>(args)...); }, data.args);
}

/**
 * @brief Function to log a class (with default options)
 *
 * @tparam T Type of the object
 * @param obj The object to log
 */
export template<typename T>
	requires HasLogFormat<T>
void log(const T& obj)
{
	log(info, obj);
}

export template<typename... Args>
constexpr LogData<std::decay_t<Args>...> log_format_helper(std::string_view fmt, Args&&... args)
{
	return { fmt, std::forward_as_tuple(std::forward<Args>(args)...) };
}

} // namespace Tekgin::Util
