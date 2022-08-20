


#include<apue.h>
#include<dirent.h>
#include<fcntl.h>
#include<unistd.h>

int function(int x)
{
	if( x == 0 )
		return 0;
	else
		exit( 1 );
}

int main( int argc, char** argv )
{
//	function(0);

//	puts( "first\n" );
//	function(1);
//
//puts( "second\n" );

	printf( "%d\n", stdin );	
	printf( "%d\n", stdout );	
	printf( "%d\n", stderr );	
	
	return 0;
}


