export module katve.tekgin.paths;
import std;

import katve.tekgin.constants;

namespace fs = std::filesystem;

namespace Tekgin
{

#if defined(_WIN32)
static static const char* app_data = std::getenv("LOCALAPPDATA");
if (app_data) {
	export const fs::path data_dir = fs::path(localAppData) / appName / "Logs";
} else {
	std::cerr << "$LOCALAPPDATA not set, falling back to temporary directory path ";
	export const fs::path data_dir = fs::temp_directory_path() / "tekgin";
}

#else
static const char* const state    = std::getenv("XDG_STATE_HOME");
static const char* const home     = std::getenv("HOME");
export const fs::path    data_dir = [] {
   if (state) { return fs::path(state) / "tekgin"; }
   if (home) { return fs::path(home) / ".local" / "state" / "tekgin"; }
   std::cerr << "$XDG_STATE_HOME or $HOME not set, falling back to current path";
   return fs::path("tekgin");
}();

#endif

export const fs::path log_dir(data_dir / "logs");
export const fs::path log_file(log_dir / format("{}/Tekgin_{:%Y-%m-%d_%H-%M-%S}.log", log_dir.string(), START_TIME));

export const fs::path save_dir(data_dir / "save");

} // namespace Tekgin
