
add_executable(
    linux-network-program-tiny-chat-07-server
    tiny-chat-07-server.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    chat.heartbeat.pb.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-07-server
    gflags
    glog
    event
    protobuf
    )

add_executable(
    linux-network-program-tiny-chat-07-client
    tiny-chat-07-client.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    chat.heartbeat.pb.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-07-client
    gflags
    glog
    event
    protobuf
    )

