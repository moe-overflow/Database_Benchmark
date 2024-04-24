#include "logger.hpp"

namespace helper
{
	std::shared_ptr<spdlog::logger> logger::instance;

	void logger::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		instance = spdlog::stdout_color_mt("Database");
		instance->set_level(spdlog::level::trace);
	}

	//void logger::log_info(const std::string& message)
	//{
	//	instance->info(message);
	//}

	//void logger::log_error(const std::string& message)
	//{
	//	instance->error(message);
	//}

}