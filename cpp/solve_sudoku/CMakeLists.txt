
add_executable(
    solve_sudoku
    solve_sudoku.cc
    )

add_test(
    NAME solve_sudoku
    COMMAND solve_sudoku data.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
