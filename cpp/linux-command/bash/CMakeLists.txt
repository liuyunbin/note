
add_executable(
    bash
    bash.cc
    main.cc
    )

target_link_libraries(
    bash
    readline
    )

