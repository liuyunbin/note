
add_executable(
    cpp-standard-library-queue-unittest
    queue/queue_unittest.cc
    priority_queue/priority_queue_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-queue-unittest
    gtest
    gtest_main
    pthread
    )

