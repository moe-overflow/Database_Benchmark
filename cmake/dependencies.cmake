function(find_packages)

	find_package(unofficial-sqlite3 CONFIG REQUIRED)
	find_package(spdlog CONFIG REQUIRED)
	find_package(bsoncxx CONFIG REQUIRED)
	find_package(mongocxx CONFIG REQUIRED)

endfunction()