#include "mongodb_handler.hpp"
#include "utility/logger.hpp"

namespace Database_Benchmark
{
	// uri address 
	// hint: for modulization it can be set as an environment variable and get accessed from there 
	//const std::string URI = "mongodb://localhost:27017";
	constexpr char URI[] = "mongodb://localhost:27017";

	// Name of basic collection for database
	constexpr char COLLECTION_NAME[] = "Statistics";

	// basic document builder
	using bsoncxx::builder::basic::kvp;
	using bsoncxx::builder::basic::make_array;
	using bsoncxx::builder::basic::make_document;


	mongodb_handler::mongodb_handler(const std::string& name)
	{
		// creating an instance
		_uri = mongocxx::uri(URI);
		_client = mongocxx::client(_uri);

		// creating a database with a name 
		_database = _client[name];

		// creating a collection
		_collection = _database.collection(COLLECTION_NAME);

		//todo: create index?

		run();
	}

	mongodb_handler::~mongodb_handler()
	{
		//_database.~database();
	}

	void mongodb_handler::run()
	{
		try
		{
			LOG_INFO("Create a mongoDB database with name: {}", _database.name());
			_database.drop(); // clear database

			// Create a vector with random double values
			{
				LOG_INFO("Inserting an array with 100 random double values");

				std::vector<double> data = helper::randomizer::randomize(10000);

				helper::timer timer;
				insert_array("random array", data);
				LOG_INFO("MongoDB - Elapsed time: {} ms", timer.elapsed());

				//print_documents();
				//LOG_INFO("Elapsed time after printing: {} ms", timer.elapsed());
			}

		}
		catch (std::exception& e)
		{
			LOG_ERROR("Error with MongoDB: {}", e.what());
		}
	}

	void mongodb_handler::insert_data(int lines, const std::string& key, const std::string& value)
	{
		auto document = bsoncxx::builder::stream::document{};
		for (int i = 0; i < lines; i++)
		{
			// using a stream document builder
			document << key << value;
		}
		//document << bsoncxx::builder::stream::finalize;

		/*auto result = _collection.insert_one(document.view());
		assert(result);
		*/
		auto result = _database.collection(COLLECTION_NAME).insert_one(document.view());
		assert(result);
	}

	// true
	void mongodb_handler::insert_array(const std::string& key, std::vector<double> value)
	{
		// create a single document and insert input into it
		auto builder = bsoncxx::builder::basic::array{};
		for (auto data : value)
			builder.append(data);
		auto document = make_document(kvp(key, builder));
		auto result = _database.collection(COLLECTION_NAME).insert_one(document.view());
		assert(result);
	}

	void mongodb_handler::delete_document()
	{
		//_collection.de
	}

	void mongodb_handler::print_collections()
	{
		LOG_INFO("Database {} has the following collections: ", _database.name());
		_database.list_collection_names();
		for (const auto& collection : _database.list_collection_names())
		{
			LOG_INFO(collection);
		}
	}

	void mongodb_handler::print_documents()
	{
		LOG_INFO("Collection {} has following documents:", _collection.name());
		auto cursor = _collection.find({});
		for (auto doc : cursor)
		{
			LOG_INFO("\n{}\n", bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed));
		}
	}

	void mongodb_handler::print_data()
	{
		try
		{
			for (mongocxx::collection collection : _collections)
			{
				auto cursor_all = collection.find({});
				// todo: implement user defined types for spdlog 
				//LOG_INFO("Collection {} contains these documents", collection);

				for (const auto& document : cursor_all)
				{
					//LOG_INFO("{}", bsoncxx::to_json(document, bsoncxx::ExtendedJsonMode::k_relaxed));
				}
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("Error while inserting document into collection: {}", e.what());
		}
	}

	/**
	*	lists all collections of the database
	*	info: collections which have no documents included won't be listed
	*/
	void mongodb_handler::list_collections()
	{
		// Collections of database
		LOG_INFO("Number of collections: {} ", _database.list_collection_names().size());
		for (const auto& coll : _database.list_collection_names())
		{
			LOG_INFO("Collection: {}", coll);
		}
	}




}