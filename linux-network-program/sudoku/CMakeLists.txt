
add_executable(
    linux-network-program-sudoku-local-benchmark
    sudoku_local_benchmark.cc sudoku.cc
    )

add_executable(
    linux-network-program-sudoku-net-benchmark
    sudoku_net_benchmark.cc
    sudoku.cc)

add_executable(
    linux-network-program-sudoku-server-iterator
    sudoku_server_iterator.cc
    sudoku.cc)

add_executable(
    linux-network-program-sudoku-server-fork
    sudoku_server_fork.cc
    sudoku.cc
    )

