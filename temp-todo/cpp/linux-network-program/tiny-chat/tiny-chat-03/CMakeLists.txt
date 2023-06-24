
add_executable(
    tiny-chat-03-server
    tiny-chat-03-server.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    chat.heartbeat.pb.cc
    )

target_link_libraries(
    tiny-chat-03-server
    gflags
    glog
    event
    protobuf
    )

add_executable(
    tiny-chat-03-client
    tiny-chat-03-client.cc
    log_init.cc
    encode.cc
    decode.cc
    chat.message_unit.pb.cc
    chat.heartbeat.pb.cc
    )

target_link_libraries(
    tiny-chat-03-client
    gflags
    glog
    event
    protobuf
    )

