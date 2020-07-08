
add_executable(
    linux-network-program-tiny-chat-01-server
    tiny-chat-01-server.cc 
    log_init.cc 
    encode.cc 
    decode.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-01-server
    gflags
    glog
    event
    )

add_executable(
    linux-network-program-tiny-chat-01-client
    tiny-chat-01-client.cc
    log_init.cc
    encode.cc
    decode.cc
    )

target_link_libraries(
    linux-network-program-tiny-chat-01-client
    gflags
    glog
    event
    )

