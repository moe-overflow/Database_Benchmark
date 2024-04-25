#pragma once

#include "benchmark.hpp"
#include <sqlite3.h>


namespace Database_Benchmark
{
	class sqlite_handler : benchmark
	{
	public:
		sqlite_handler(const std::string& name, bool in_memory);
		~sqlite_handler() = default;

		void run() override;

		int init(const std::string& database_name);
		int init_in_memory();
		int exec(const std::string& cmd);
		int create_table(bool single);
		void insert_single_data(double x);
		void insert_double_data(double x, double y);

	private:
		sqlite3* _db;
		std::string _name;
	};
}

