#include "utility/logger.hpp"
#include "mongodb_handler.hpp"


static void perform_benchmark()
{
	Database_Benchmark::mongodb_handler("MongoDB-Test");
}

int main(void)
{
	helper::logger::init();

	LOG_INFO("Start of Benchmark");

	perform_benchmark();

	LOG_INFO("End of Benchmark");

	return 0;
}
