set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

function(compile_protos proto_name)

  set(GRPC_GEN_PROTOS_DIR ../${GRPC_GEN_PROTOS_DIR})

  # Proto file
  get_filename_component(PROTO_FILE ${GRPC_PROTOS_DIR}/${proto_name}.proto ABSOLUTE)
  get_filename_component(PROTO_PATH ${PROTO_FILE} PATH)

  # Generated sources
  set(PROTO_SOURCES ${GRPC_GEN_PROTOS_DIR}/${proto_name}.pb.cc)
  set(PROTO_HEADERS ${GRPC_GEN_PROTOS_DIR}/${proto_name}.pb.h)
  set(GRPC_SOURCES ${GRPC_GEN_PROTOS_DIR}/${proto_name}.grpc.pb.cc)
  set(GRPC_HEADERS ${GRPC_GEN_PROTOS_DIR}/${proto_name}.grpc.pb.h)


  add_custom_command(
  OUTPUT ${PROTO_SOURCES} ${PROTO_HEADERS} ${GRPC_SOURCES} ${GRPC_HEADERS}
  COMMAND $<TARGET_FILE:protobuf::protoc>
  ARGS --grpc_out ${GRPC_GEN_PROTOS_DIR}
      --cpp_out ${GRPC_GEN_PROTOS_DIR}
      -I ${PROTO_PATH}
      --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
      ${PROTO_FILE}
  DEPENDS ${PROTO_FILE})

  # Include generated *.pb.h files
  include_directories(${GRPC_GEN_PROTOS_DIR})

  # Libraries
  add_library(${proto_name}_grpc_lib
  ${GRPC_SOURCES}
  ${GRPC_HEADERS}
  ${PROTO_SOURCES}
  ${PROTO_HEADERS})
  
  target_link_libraries(${proto_name}_grpc_lib
  gRPC::grpc++
  protobuf::libprotobuf)

endfunction()