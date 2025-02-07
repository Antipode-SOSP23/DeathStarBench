add_executable(
    PostStorageService
    PostStorageService.cpp
    ${THRIFT_GEN_CPP_DIR}/PostStorageService.cpp
    ${THRIFT_GEN_CPP_DIR}/social_network_types.cpp
    ${THRIFT_GEN_CPP_DIR}/AntipodeOracle.cpp
    ${THRIFT_GEN_CPP_DIR}/WriteHomeTimelineService.cpp
)

target_include_directories(
    PostStorageService PRIVATE
    ${LIBMEMCACHED_INCLUDE_DIR}
    ${MONGOC_INCLUDE_DIRS}
    /usr/local/include/jaegertracing
    /usr/local/include/xtrace
)

target_link_libraries(
    PostStorageService
    ${MONGOC_LIBRARIES}
    ${LIBMEMCACHED_LIBRARIES}
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
    jaegertracing
    xtrace
    protobuf
    tbb
)

install(TARGETS PostStorageService DESTINATION ./)
