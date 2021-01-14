
add_executable(
    sudoku
    sudoku.cc
    )

add_test(
    NAME sudoku
    COMMAND sudoku data.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
