#pragma once

#include "benchmark.hpp"

#include "mongocxx/instance.hpp"
#include "mongocxx/client.hpp"
#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"
#include "bsoncxx/oid.hpp"

namespace Database_Benchmark
{
	class mongodb_handler : benchmark
	{
	public:
		mongodb_handler(const std::string& name);
		virtual ~mongodb_handler();

		void list_collections();
		void delete_document();
		void insert_data(int lines, const std::string& key, const std::string& value);
		void insert_array(const std::string& key, std::vector<double> input);

		void print_data();
		void print_collections();
		void print_documents();

		void run() override;

	private:
		mongocxx::uri _uri;
		mongocxx::client _client;
		mongocxx::database _database;
		std::vector<mongocxx::collection> _collections; // still needed?
		mongocxx::collection _collection;

		mongocxx::instance mongodb_instance{}; // to be called once only

	};
}

