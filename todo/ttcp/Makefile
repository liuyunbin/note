all: ttcp-server ttcp-client

ttcp-server: ttcp_server.cc
	g++ -std=c++11 -O2 $^ -o $@

ttcp-client: ttcp_client.cc
	g++ -std=c++11 -O2 $^ -o $@

clean:
	rm -f ttcp-server ttcp-client
