
add_executable(
    shell
    shell.cc
    main.cc
    )

target_link_libraries(
    shell
    readline
    )

