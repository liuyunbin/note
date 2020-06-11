
add_executable(
    linux-commands-shell
    shell.cc
    main.cc
    )

target_link_libraries(
    linux-commands-shell
    readline
    )

