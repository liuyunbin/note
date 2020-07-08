
add_executable(
    linux-network-program-echo-fork
    echo_fork.cc
    )

add_executable(
    linux-network-program-echo-libevent
    echo_libevent.cc)

target_link_libraries(
    linux-network-program-echo-libevent
    event_core
    )

add_executable(
    linux-network-program-echo-libevent-thread
    echo_libevent_thread.cc
    )

target_link_libraries(
    linux-network-program-echo-libevent-thread
    event_core
    event_pthreads
    pthread
    )

add_executable(
    linux-network-program-test-echo-server-use-just-send-data
    test_echo_server_use_just_send_data.cc
    )

add_executable(
    linux-network-program-test-echo-server-use-send-shutdown-recv-data
    test_echo_server_use_send_shutdown_recv_data.cc
    )

