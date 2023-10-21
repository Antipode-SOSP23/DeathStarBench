set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(GRPC_PROTOS_DIR proto)
set(GEN_PROTO_DIR .)

function(compile_protos proto_name)
  # Proto file
  get_filename_component(PROTO_FILE ${GRPC_PROTOS_DIR}/${proto_name}.proto ABSOLUTE)
  get_filename_component(PROTO_PATH ${PROTO_FILE} PATH)

  # Generated sources
  set(PROTO_SOURCES ${GEN_PROTO_DIR}/${proto_name}.pb.cc)
  set(PROTO_HEADERS ${GEN_PROTO_DIR}/${proto_name}.pb.h)


  add_custom_command(
  OUTPUT ${PROTO_SOURCES} ${PROTO_HEADERS}
  COMMAND $<TARGET_FILE:protobuf::protoc>
  ARGS --cpp_out ${GEN_PROTO_DIR}
      -I ${PROTO_PATH}
      --plugin=protoc-gen-grpc
      --experimental_allow_proto3_optional
      ${PROTO_FILE}
  DEPENDS ${PROTO_FILE})

  # Include generated *.pb.h files
  include_directories(${GEN_PROTO_DIR})

  # Libraries
  add_library(${proto_name}_lib
  ${PROTO_SOURCES}
  ${PROTO_HEADERS})
  
  target_link_libraries(${proto_name}_lib
  protobuf::libprotobuf)

endfunction()