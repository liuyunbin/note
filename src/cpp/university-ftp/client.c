#include"common_functions.h"

static	int  connection_port;
static  int  connection_data;
static struct  sockaddr_in servaddr_port;
static struct  sockaddr_in servaddr_data;
static  char     input[MAX_SIZE];
static  char    output[MAX_SIZE];
static	char	current_dir[MAX_SIZE];
static	char    st[MAX_SIZE];
static	char    user[MAX_SIZE];
static	char password[MAX_SIZE];
static FILE* file;
static	int   n;
static	char *p1, *p2;

static void printfs( const char* st );
static void print_help( void );
static void cmd_lcd( void );
static void cmd_lls( void );
static void cmd_ls( void );
static void cmd_get( void );
static void cmd_put( void );
static void cmd_user( void );

int main( int argc, char **argv )
{
	if (argc != 2)
		error_exit( -1, "argc error" );

	servaddr_port.sin_family = AF_INET;
	servaddr_port.sin_port   = htons(21);	

	servaddr_data.sin_family = AF_INET;
	servaddr_data.sin_port   = htons(20);

	getcwd( current_dir, MAX_SIZE );
	connection_port = Socket(AF_INET, SOCK_STREAM, 0);

	Inet_pton( AF_INET, argv[1], &servaddr_port.sin_addr );
	Inet_pton( AF_INET, argv[1], &servaddr_data.sin_addr );
	Connect( connection_port, (const struct sockaddr *)(&servaddr_port), sizeof(servaddr_port) );

	strcpy( user, "anonymous" );

	while( true )
	{
		printf( "ftp:> " );
		Fgets( input, MAX_SIZE, stdin );
		strcpy( st, input );
		p1 = strtok( st, " " );
		if( p1 == NULL )
			continue;
		p2 = strtok( NULL, " " );
		if( strcmp(p1, "help") == 0 || strcmp(p1, "?" ) == 0 )
		{
			print_help();
			continue;
		}

		if( strcmp(p1, "exit") == 0 || strcmp(p1, "bye") == 0 || strcmp(p1, "quit") == 0 )
		{
			Write( connection_port, "quit" );
			return 0;
		}

		if( strcmp( p1, "lls" ) == 0 )
		{
			cmd_lls();
			continue;
		}

		if( strcmp( p1, "lcd" ) == 0 )
		{
			cmd_lcd();
			continue;
		}

		if( strcmp( p1, "lpwd" ) == 0 )
		{
			printfs( current_dir );
			continue;
		}

		if( strcmp( p1, "get" ) == 0 )
		{		
			cmd_get();			
			continue;
		}

		if( strcmp( p1, "put" ) == 0 )
		{
			if( strcmp(user, "root") == 0 )
				cmd_put();
			else
				puts( "Limited permission" );
		
			continue;
		}
		
		if( strcmp( p1, "ls" ) == 0 )
		{
			cmd_ls();
			continue;
		}

		if( strcmp( p1, "user" ) == 0 )
		{
			cmd_user();
			continue;
		}

		Write( connection_port, input );
	 	Read(  connection_port, output, MAX_SIZE);
		printfs( output );
	}

}

static void printfs( const char* st )
{
	if( strcmp(st, "ok") != 0 )
		printf( "  %s\n", st );
}

static void print_help( void )
{
	printf("\t client  [OPTIONS] [OPTION] [OPTION] \n");
	printf("\t help | ?             \t help information \n");
	printf("\t     cd [direction]   \t Display FTP direction \n");
	printf("\t    lcd [direction]   \t Display current direction \n");
	printf("\t    pwd               \t Display FTP pathname \n");
	printf("\t   lpwd               \t Display current pathname \n");
	printf("\t     ls [direction]   \t list FTP File or direction \n");
	printf("\t    lls [direction]   \t list current File or direction \n");
	printf("\t    put file          \t put file \n");
	printf("\t    get file          \t get file \n");
}

static void cmd_user( void )
{
	if( p2 != NULL && strcmp(p2, "root") == 0 )
	{
		printf( "ftp:> password: " );
		fgets( password, MAX_SIZE, stdin );
		if( strcmp( password, "root\n" ) == 0 )
			strcpy( user, "root" );
	}
}

static void cmd_lcd( void )
{
	if( chdir(p2 == NULL ? getenv("HOME") : p2) == -1 )
	{
		puts( "lcd argc error" );
		return ;
	}
	getcwd( current_dir, MAX_SIZE );
}

static void cmd_lls( void )
{
	DIR* dir;
	struct dirent* p;

	if( ( dir=opendir(p2 == NULL ? current_dir : p2) ) == NULL )
	{
		puts( "ls argc error" );
		return ;
	}

	while( ( p=readdir(dir) ) != NULL )
		if( *p->d_name != '.' )
			printf( "%s\t", p->d_name );
	printf( "\n" );
	closedir(dir);
}

static void cmd_ls( void )
{
	Write( connection_port, input );
	Read(  connection_port, output, MAX_SIZE);
	if( strcmp(output, "ok") != 0 )
	{
		printfs( output );
		return ;
	}

	connection_data = Socket(AF_INET, SOCK_STREAM, 0 );
	Connect( connection_data, (const struct sockaddr *)(&servaddr_data), sizeof(servaddr_data) );
		
	while( read(connection_data, output, MAX_SIZE) ) 
        	printf( "%s\t", output );
	printf( "\n" );	
	close( connection_data );
	Read( connection_port, output, MAX_SIZE );
	printfs( output );
}

static void cmd_get( void )
{
	if( p2 == NULL )
	{
		printfs( "get agrc error" );
		return ;
	}
	if( ( file = fopen(p2, "w" ) ) == NULL )
	{
		printfs( "open error" );
		return ;
	}

	Write( connection_port, input );
	Read(  connection_port, output, MAX_SIZE);
	if( strcmp(output, "ok") != 0 )
	{
		printfs( output );
		return ;
	}

	connection_data = Socket(AF_INET, SOCK_STREAM, 0 );
	Connect( connection_data, (const struct sockaddr *)(&servaddr_data), sizeof(servaddr_data) );
		
	while( n = read(connection_data, output, MAX_SIZE) ) 
        	fwrite( output, sizeof(char), n, file );
			
	fclose(file);
	close( connection_data );
	Read( connection_port, output, MAX_SIZE );
	printfs( output );
}

static void cmd_put( void )
{
	if( p2 == NULL )
	{
		printfs( "put agrc error" );
		return ;
	}
	if( ( file = fopen(p2, "r") ) == NULL )
	{
		printfs( "file not find" );
		return ;
	}

	Write( connection_port, input );
	Read(  connection_port, output, MAX_SIZE);
	if( strcmp( output, "ok") != 0 )
	{
		printfs( output );
		return ;
	}
	connection_data = Socket(AF_INET, SOCK_STREAM, 0 );
	Connect(connection_data, (const struct sockaddr *)(&servaddr_data), sizeof(servaddr_data) );
	
	while( n = fread( output, sizeof(char), MAX_SIZE, file ) )
		write( connection_data, output, n );
	
	fclose(file);
	close(connection_data);
	Read( connection_port, output, MAX_SIZE );
	printfs( output );
}

