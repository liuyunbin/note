set(SRC
  acceptor.cc
  buffer.cc
  channel.cc
  epoller.cc
  event_loop.cc
  event_loop_thread.cc
  event_loop_thread_pool.cc
  inet_address.cc
  listen_socket.cc
  tcp_connection.cc
  tcp_server.cc
  )

add_library(TinyNet_static STATIC ${SRC})
add_library(TinyNet_shared SHARED ${SRC})
set_target_properties(TinyNet_static PROPERTIES OUTPUT_NAME TinyNet)
set_target_properties(TinyNet_shared PROPERTIES OUTPUT_NAME TinyNet)

target_link_libraries(TinyNet_static pthread)
target_link_libraries(TinyNet_shared pthread)

install(TARGETS TinyNet_static DESTINATION lib)
install(TARGETS TinyNet_shared DESTINATION lib)

set (HEADER
  acceptor.h
  buffer.h
  channel.h
  epoller.h
  event_loop.h
  event_loop_thread.h
  event_loop_thread_pool.h
  inet_address.h
  listen_socket.h
  tcp_connection.h
  tcp_server.h
  )

install(FILES ${HEADER} DESTINATION include/TinyNet)

