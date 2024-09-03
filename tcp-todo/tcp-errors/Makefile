
alr: reproduce-tcp-errors-reproduce-bind-errors-01 reproduce-tcp-errors-reproduce-bind-errors-02 reproduce-tcp-errors-reproduce-bind-errors-03 reproduce-tcp-errors-reproduce-connect-errors reproduce-tcp-errors-how-to-use-nonblock-connect reproduce-tcp-errors-reproduce-host-crash-and-restart-errors reproduce-tcp-errors-reproduce-host-crash-errors reproduce-tcp-errors-reproduce-host-shutdown-errors reproduce-tcp-errors-reproduce-process-crash-errors

reproduce-tcp-errors-reproduce-bind-errors-01: reproduce-bind-errors/*01.cc
	g++ $^ -o $@ -std=c++11

reproduce-tcp-errors-reproduce-bind-errors-02: reproduce-bind-errors/*02.cc
	g++ $^ -o $@ -std=c++11

reproduce-tcp-errors-reproduce-bind-errors-03: reproduce-bind-errors/*03.cc
	g++ $^ -o $@ -std=c++11

reproduce-tcp-errors-reproduce-connect-errors: reproduce-connect-errors/*errors.cc
	g++ $^ -o $@ -std=c++11

reproduce-tcp-errors-how-to-use-nonblock-connect: reproduce-connect-errors/how-to-use-nonblock-connect.cc
	g++ $^ -o $@ -std=c++11

reproduce-tcp-errors-reproduce-host-crash-and-restart-errors: reproduce-host-crash-and-restart-errors/*.cc
	g++ $^ -o $@ -std=c++11

reproduce-tcp-errors-reproduce-host-crash-errors: reproduce-host-crash-errors/*.cc
	g++ $^ -o $@ -std=c++11

reproduce-tcp-errors-reproduce-host-shutdown-errors: reproduce-host-shutdown-errors/*.cc
	g++ $^ -o $@ -std=c++11

reproduce-tcp-errors-reproduce-process-crash-errors: reproduce-process-crash-errors/*.cc
	g++ $^ -o $@ -std=c++11

