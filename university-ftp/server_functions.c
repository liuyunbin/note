#include"common_functions.h"

static char   input[MAX_SIZE];
static char  output[MAX_SIZE];
static char  current_dir[MAX_SIZE];
static char          dir[MAX_SIZE];
static int connection_port;
static int connection_data;
static int sock_port;
static int sock_data;
static int len;
static struct sockaddr_in servaddr_port;
static struct sockaddr_in servaddr_data;
static struct sockaddr_in client_port; 
static FILE* file;
static int n;
static char *p1, *p2;

static void cmd_ls( void );
static void cmd_get( void );
static void cmd_cd();
static void cmd_put( void );
static void print_help( void );
static void thread( void );
void dir_is_exist(const char*);

void start_server( void ) 
{
	char st[MAX_SIZE];

	len = sizeof(client_port);
	while( true ) 
	{
		connection_port = Accept(sock_port, &client_port, &len );
		inet_ntop( AF_INET, &client_port.sin_addr, st, len );
		printf( "client ip %s port %d\n", st, client_port.sin_port );
		if( ( n = fork() ) == 0 ) 
			thread();
		else 
			if( n > 0 ) 
				close(connection_port);
			else 
				error_exit( -1, "fork error\n" );
	}
}

static void thread( void )
{	
	while( true ) 
	{
		Read( connection_port, input, MAX_SIZE );
		p1 = strtok( input, " " );
		p2 = strtok( NULL, " " );
		if( strcmp(p1, "quit") == 0 || strcmp(p1, "exit") == 0 || strcmp(p1, "bye") == 0 )
			return ;
		if( strcmp( p1, "ls" ) == 0 )
		{
			cmd_ls();
			continue;
		}
		if( strcmp( p1, "cd" ) == 0 )
		{
			cmd_cd();
			continue;
		}
		if( strcmp( p1, "pwd" ) == 0 )
		{
			Write( connection_port, current_dir );
			continue;
		}
		if( strcmp( p1, "get" ) == 0 )
		{
			cmd_get();		
			continue;
		}
		if( strcmp( p1, "put" ) == 0 )
		{
			cmd_put();
			continue;
		}
		Write( connection_port, "argv error" );
	}
}


void init( int argc, char** argv )
{
	struct hostent *host;

	strcpy( dir, "test" );
	
	servaddr_port.sin_family = AF_INET;
	servaddr_port.sin_port   = htons(21);
	servaddr_port.sin_addr.s_addr = htonl(INADDR_ANY);
	
	while( --argc != 0 )
	{	
		if( strlen(*++argv) != 2 || **argv != '-' || --argc == 0 )
		{	
			perror( "argc error\n" );
			print_help();
			exit(1);
		}
		switch((*argv++)[1])
       		{
		case 's':
			Inet_pton( AF_INET, *argv, &servaddr_port.sin_addr );
			break;
		case 'p':
			n = atoi(*argv);
			if( n < 1 || n > 32768 )
				error_exit( -1, "port error" );
			servaddr_port.sin_port = htons(n);
			break;
		case 'c':
			dir_is_exist(*argv);
			strncpy( dir, *argv, MAX_SIZE );
			break;			
		default:
			printf( "argc error\n" );
			print_help();
			exit(1);
		}
	}

	sock_port = Socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	Bind( sock_port, (struct sockaddr *)&servaddr_port, sizeof(servaddr_port) );
	Listen( sock_port, 5 );

	servaddr_data.sin_family = AF_INET;
	servaddr_data.sin_port   = htons(20);
	servaddr_data.sin_addr.s_addr = htonl(INADDR_ANY);
	sock_data = Socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	Bind( sock_data, (struct sockaddr *)&servaddr_data, sizeof(servaddr_data) );
	Listen( sock_data, 5 );
	chroot( dir );
	strcpy( current_dir, "/" );
	chdir( "/" );
}

void dir_is_exist( const char* st )
{
	DIR* p;

	if( ( p = opendir(st) ) == NULL )
		error_exit( -1, "opendir error" );
	closedir(p);
}

static void cmd_cd( void )
{
	if( chdir(p2 == NULL ? "/" : p2) == -1 )
	{
		Write( connection_port, "lcd argc error" );
		return ;
	}
	getcwd( current_dir, MAX_SIZE );
	Write( connection_port, "ok" );
}

static void cmd_ls( void )
{
	DIR* dir;
	struct dirent* p;

	if( ( dir=opendir(p2 == NULL ? current_dir : p2) ) == NULL )
	{
		Write( connection_port, "ls argc error" );
		return ;
	}

	Write( connection_port, "ok" );
	connection_data = Accept(sock_data, NULL, NULL);
	while( ( p=readdir(dir) ) != NULL )
		if( *p->d_name != '.' )
		{
			Write( connection_data, p->d_name );
			Write( connection_data, "\t" );
		}
	close(connection_data);
	closedir(dir);
	Write( connection_port, "ok" );
}

static void cmd_get( void )
{
	if( p2 == NULL )
	{
		Write( connection_port, "get argc error" );
		return ;
	}
	if( ( file = fopen(p2, "r") ) == NULL )
	{
		Write( connection_port, "file not find" );
		return ;
	}
	Write( connection_port, "ok" );

	connection_data = Accept(sock_data, NULL, NULL );
	while( n = fread(output, sizeof(char), MAX_SIZE, file) )
		write( connection_data, output, n );
	fclose(file);
	close(connection_data);
	Write( connection_port, "file get finished" );
}

static void cmd_put( void )
{
	if( p2 == NULL )
	{
		Write( connection_port, "argc error" );
		return ;
	}
	if( ( file = fopen(p2, "w") ) == NULL )
	{
		Write( connection_port, "file not find" );
		return ;
	}
	Write( connection_port, "ok" );
	connection_data = Accept(sock_data, NULL, NULL );
	while(  n = read(connection_data, output, MAX_SIZE ) ) 
        	fwrite( output, sizeof(char), n, file );
	fclose(file);
	close( connection_data );
	Write( connection_port, "file put finished" );
}

static void print_help( void )
{
	printf("\t server [OPTIONS]\n");
	printf("\t -h              \t     Display tinyftp help\n");
	printf("\t -s [address]    \t     Set the server address\n");
	printf("\t -p [port]       \t     Set the server port \n");
	printf("\t -c [directory]  \t     Default directory \n");
}


