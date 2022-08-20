
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/linux-network-program)

add_subdirectory(echo)
add_subdirectory(reproduce-multi-machine-data-processing)
add_subdirectory(reproduce-tcp-errors)
add_subdirectory(sudoku)
add_subdirectory(tiny-chat)
add_subdirectory(ttcp)

