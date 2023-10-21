set (RENDEZVOUS_LIB_HEADERS
    include/monitor_mongodb.h
    include/monitor.h
    include/rendezvous.h
    include/storage_mongodb.h)

set (RENDEZVOUS_LIB_SOURCES
    src/monitor_mongodb.cpp
    src/monitor.cpp
    src/storage_mongodb.cpp)

set (RENDEZVOUS_LIB_UTILS
    utils/logger.h)

add_library(rendezvous_lib ${RENDEZVOUS_LIB_SOURCES})
target_sources(rendezvous_lib PRIVATE ${RENDEZVOUS_LIB_UTILS})
target_include_directories(rendezvous_lib PUBLIC include ${MONGOC_INCLUDE_DIRS})
target_link_libraries(rendezvous_lib PUBLIC ${MONGOC_LIBRARIES} nlohmann_json::nlohmann_json rendezvous_grpc_lib)