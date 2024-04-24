#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/ostr.h> 

#include <memory>
#include <string>

namespace helper
{
	class logger
	{
	public:
		static void init();
		static std::shared_ptr<spdlog::logger> get() { return instance; }
		
	private:
		logger() = default;

		static std::shared_ptr<spdlog::logger> instance;

	};
}

#define LOG_INFO(...) ::helper::logger::get()->info(__VA_ARGS__)
#define LOG_ERROR(...) ::helper::logger::get()->error(__VA_ARGS__)


