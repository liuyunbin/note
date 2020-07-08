
add_executable(
    linux-network-program-tiny-chat-06-server
    tiny-chat-06-server.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    chat.heartbeat.pb.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-06-server
    gflags
    glog
    event
    protobuf
    )

add_executable(
    linux-network-program-tiny-chat-06-client
    tiny-chat-06-client.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    chat.heartbeat.pb.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-06-client
    gflags
    glog
    event
    protobuf
    )

