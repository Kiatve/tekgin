export module katvees.tekgin.constants;
import std;

namespace Tekgin
{

/** @addtogroup version Engine version compile time variables
 *  @todo Consider replacing with #defines set during compilation
 *  @{
 */
export constinit int         ENGINE_VERSION_MAJOR  = 0;
export constinit int         ENGINE_VERSION_MINOR  = 0;
export constinit int         ENGINE_VERSION_PATCH  = 0;
export constinit const char* ENGINE_VERSION_STRING = "0.0.0";
/// @}

/// @todo Consider setting through another method
export const std::chrono::system_clock::time_point START_TIME{ std::chrono::system_clock::now() };

} // namespace Tekgin
