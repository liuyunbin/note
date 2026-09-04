
all: sudoku-local-benchmark add_executable sudoku-server-iterator sudoku-server-fork

sudoku-local-benchmark: sudoku_local_benchmark.cc sudoku.cc
	g++ $^ -o $@ -std=c++11

add_executable: sudoku_net_benchmark.cc sudoku.cc
	g++ $^ -o $@ -std=c++11

sudoku-server-iterator: sudoku_server_iterator.cc sudoku.cc
	g++ $^ -o $@ -std=c++11

sudoku-server-fork: sudoku_server_fork.cc sudoku.cc
	g++ $^ -o $@ -std=c++11


