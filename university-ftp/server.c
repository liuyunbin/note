#include"common_functions.h"

void start_server();
void init( int, char** );

int main( int argc, char** argv )
{
	init( argc, argv);
	start_server();
	return	0;
}
