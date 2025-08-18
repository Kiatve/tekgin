module katve.tekgin.core.engine;


namespace Tekgin
{
Engine::Engine()
{
	std::filesystem::create_directories(data_dir);
	std::filesystem::create_directory(log_dir);

	std::filesystem::create_directories(log_dir);
	std::println("Log file can be found at {}/Tekgin_{:%Y-%m-%d_%H-%M-%S}.log", log_dir.string(), START_TIME);
}
} // namespace Tekgin
