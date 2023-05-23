
add_executable(
    sudoku-local-benchmark
    sudoku_local_benchmark.cc sudoku.cc
    )

add_executable(
    sudoku-net-benchmark
    sudoku_net_benchmark.cc
    sudoku.cc)

add_executable(
    sudoku-server-iterator
    sudoku_server_iterator.cc
    sudoku.cc)

add_executable(
    sudoku-server-fork
    sudoku_server_fork.cc
    sudoku.cc
    )

