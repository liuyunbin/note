
all: echo-fork echo-libevent echo-libevent-thread test-echo-server-use-just-send-data test-echo-server-use-send-shutdown-recv-data

echo-fork: echo_fork.cc
	g++ $^ -o $@ -std=c++11

echo-libevent: echo_libevent.cc
	g++ $^ -o $@ -std=c++11 -levent_core

echo-libevent-thread: echo_libevent_thread.cc
	g++ $^ -o $@ -std=c++11 -levent_core -levent_pthreads -lpthread

test-echo-server-use-just-send-data: test_echo_server_use_just_send_data.cc
	g++ $^ -o $@ -std=c++11

test-echo-server-use-send-shutdown-recv-data: test_echo_server_use_send_shutdown_recv_data.cc
	g++ $^ -o $@ -std=c++11

