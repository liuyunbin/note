
add_executable(
    linux-commands-bc
    bc.cc
    main.cc
    )

target_link_libraries(
    linux-commands-bc
    readline
    )

