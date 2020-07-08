
add_executable(
    linux-network-program-tiny-chat-02-server
    tiny-chat-02-server.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-02-server
    gflags
    glog
    event
    protobuf
    )

add_executable(
    linux-network-program-tiny-chat-02-client
    tiny-chat-02-client.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-02-client
    gflags
    glog
    event
    protobuf
    )

