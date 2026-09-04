
test_gcov: main.cc
	g++ -fprofile-arcs -ftest-coverage -o test_gcov -lgcov main.cc

html:
	rm -rf html
	lcov --directory . --capture --output-file gcov.info
	genhtml --output-directory html gcov.info
	tar acf html.tgz html

clean:
	lcov --zerocounters --directory .
	rm -rf test_gcov *.gcno *.gcda gcov.info html

