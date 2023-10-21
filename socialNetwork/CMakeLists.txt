cmake_minimum_required(VERSION 3.5)
project(social_network_microservices)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_INSTALL_PREFIX /usr/local/bin)

# ----------
# RENDEZVOUS
# ----------
find_package(libmongoc-1.0 1.13 REQUIRED)
find_package(nlohmann_json 3.5.0 REQUIRED)
find_package(Threads)

include("cmake/FindgRPC.cmake")
include("cmake/CompileProtos.cmake")

set(GRPC_PROTOS_DIR rendezvous/protos)
set(GRPC_GEN_PROTOS_DIR gen-protos)

compile_protos(rendezvous)
add_subdirectory(rendezvous)
# ----------
# RENDEZVOUS
# ----------

add_subdirectory(src)
#add_subdirectory(test)
#enable_testing()