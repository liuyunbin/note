
add_executable(
    solve-sudoku
    solve-sudoku.cc
    )

add_test(
    NAME solve-sudoku
    COMMAND solve-sudoku data.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
