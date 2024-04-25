#include "utility/logger.hpp"

#include "mongodb_handler.hpp"
#include "sqlite_handler.hpp"

static void perform_benchmark()
{
	// MongoDB
	Database_Benchmark::mongodb_handler("MongoDB-Test");

	// SQLite
	LOG_INFO("Running Sqlite on Disk:");
	Database_Benchmark::sqlite_handler("sqlite-Test", false);
	LOG_INFO("Running Sqlite in memory:");
	Database_Benchmark::sqlite_handler("sqlite-Test", true);


}

int main(void)
{
	helper::logger::init();

	LOG_INFO("Start of Benchmark");

	perform_benchmark();

	LOG_INFO("End of Benchmark");

	return 0;
}
