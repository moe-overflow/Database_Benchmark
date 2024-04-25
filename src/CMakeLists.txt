

add_executable(
        ${PROJECT_NAME}
        main.cpp
        utility/logger.cpp
        utility/logger.hpp
        utility/randomizer.hpp
        utility/timer.hpp

        benchmark.hpp
        mongodb_handler.cpp
        mongodb_handler.hpp

        sqlite_handler.hpp
        sqlite_handler.cpp

)

include(${CMAKE_SOURCE_DIR}/cmake/system_link.cmake)

target_link_system_libraries(
    ${PROJECT_NAME} 
    PRIVATE 
    spdlog::spdlog
    $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
    $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
    unofficial::sqlite3::sqlite3
	
)

