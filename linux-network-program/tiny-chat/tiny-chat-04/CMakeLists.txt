
add_executable(
    linux-network-program-tiny-chat-04-server
    tiny-chat-04-server.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    chat.heartbeat.pb.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-04-server
    gflags
    glog
    event
    protobuf
    )

add_executable(
    linux-network-program-tiny-chat-04-client
    tiny-chat-04-client.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    chat.heartbeat.pb.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-04-client
    gflags
    glog
    event
    protobuf
    )

