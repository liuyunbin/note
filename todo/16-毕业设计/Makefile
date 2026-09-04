all: client server

client: client.o common_functions.o
	gcc client.o common_functions.o -o client 

client.o: client.c

server: server.o server_functions.o common_functions.o
	gcc server.o server_functions.o common_functions.o -o server

server.o: server.c

common_functions.o: common_functions.c

server_functions.o: server_functions.c

clean:
	rm -rf *.o server client
	
