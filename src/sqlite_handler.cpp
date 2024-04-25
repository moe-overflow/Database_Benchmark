#include "sqlite_handler.hpp"

#include "utility/logger.hpp"

namespace Database_Benchmark
{
	constexpr char NAME[] = "Statistics";
	constexpr char TABLE_NAME[] = "MY_TABLE";

	sqlite_handler::sqlite_handler(const std::string& name, bool in_memory) : _name(NAME)
	{
		int success = in_memory ? init_in_memory() : init(_name);
		
		if (success)
			LOG_ERROR("Initializing the database failed");
		else
			LOG_INFO("Initializing the database succeeded");

		run();
	}

	void sqlite_handler::run()
	{
		create_table(true);

		helper::randomizer randomizer;
		std::vector<double> input = randomizer.randomize(10000);

		helper::timer timer;

		for (double number : input)
			insert_single_data(number);

		LOG_INFO("SQLite - Elapsed time: {} ms", timer.elapsed());

		sqlite3_close(_db);

	}

	int sqlite_handler::init_in_memory()
	{
		return sqlite3_open(":memory:", &_db);		
	}

	int sqlite_handler::init(const std::string& database_name)
	{
		std::string name;
		name.append(database_name);
		name.append(".db");
		return sqlite3_open(name.c_str(), &_db);	
	}

	static int callback(void* unused, int count, char** data, char** columns)
	{
		LOG_INFO("Number of used columns: {}", count);
		for (int i = 0; i < count; i++)
		{
			LOG_INFO("Data in column {} is: {}", columns[i], data[i]);
		}
		return 0;
	}

	// Creates a table with a specific name and two columns (x and y) both of integer type
	int sqlite_handler::create_table(bool single)
	{
		std::string col = single ? "(X REAL)" : "(X REAL, Y REAL)";
		std::string cmd = "create table if not exists " + std::string(TABLE_NAME) + col;
		exec(cmd);
		return 0;
	}

	void sqlite_handler::insert_single_data(double x)
	{
		std::string cmd = "insert into " + std::string(TABLE_NAME) + "(X) values (" +
			std::to_string(x) + ");";

		exec(cmd);
	}

	void sqlite_handler::insert_double_data(double x, double y)
	{
		std::string cmd = "insert into " + std::string(TABLE_NAME) + "(X,Y) values (" +
			std::to_string(x) + ", " + std::to_string(y) + ");";

		exec(cmd);
	}

	int sqlite_handler::exec(const std::string& cmd)
	{
		int result;
		char* message = 0;
		result = sqlite3_exec(_db, cmd.c_str(), callback, 0, &message);
		if (result != SQLITE_OK)
		{
			LOG_ERROR("Error with executing sql command: {} ", sqlite3_errmsg(_db));
			sqlite3_free(message);
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}



}