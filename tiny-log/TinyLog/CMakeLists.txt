set(SRC
  log_append_file.cc
  log_buffer.cc
  log_file.cc
  log_format.cc
  log_strerror.cc
  log_stream.cc
  logger.cc
  logging.cc
  logging_async.cc
  time_stamp.cc
  )

add_library(tinylog_static STATIC ${SRC})
add_library(tinylog_shared SHARED ${SRC})
set_target_properties(tinylog_static PROPERTIES OUTPUT_NAME tinylog)
set_target_properties(tinylog_shared PROPERTIES OUTPUT_NAME tinylog)

install(TARGETS tinylog_static DESTINATION lib)
install(TARGETS tinylog_shared DESTINATION lib)

set (HEADER
  log_append_file.h
  log_buffer.h
  log_file.h
  log_format.h
  log_strerror.h
  log_stream.h
  logger.h
  logging.h
  logging_async.cc
  time_stamp.h
  )

install(FILES ${HEADER} DESTINATION include/TinyLog)

