#include<stdio.h>
#include<string.h>

#define MAX 10
#define MAX_SIZE 100

void init( int (*a)[MAX], int* n, int* m )
{
	int i, j, k;

	scanf( "%d%d", n, m );

	for( i = 0; i < *n; ++i )
		for( j = 0; j < *n; ++j )
			a[i][j] = MAX_SIZE;
	for( i = 0; i < *n; ++i )
		a[i][i] = 0;
	for( k = 0; k < *m; ++k )
	{
		scanf( "%d%d", &i, &j );
		scanf( "%d", a[i] + j );
		a[j][i] = a[i][j];
	}
}

void dijkstra( int (*a)[MAX], int n, int m, int* pre, int* weight, int k )
{
	int visit[MAX];
	int i, j;

	memset( visit, 0, n * sizeof(int) );
	for( i = 0; i < n; ++i )
	{
		weight[i] = a[k][i];
		pre[i] = k;
	}
	weight[n] = MAX_SIZE;
	pre[k] = -1;
	visit[k] = 1;
	for( i = 1; i < n; ++i )
	{
		k = n;
		for( j = 0; j < n; ++j )
			if( visit[j] == 0 && weight[j] < weight[k] )
				k = j;
		visit[k] = 1;
		for( j = 0; j < n; ++j )
			if( visit[j] == 0 && weight[k] + a[k][j] < weight[j] )
			{
				weight[j] = weight[k] + a[k][j];
				pre[j] = k;
			}
	}
}

void pre_output( const int* pre, int k )
{
	if( pre[k] != -1 )
		pre_output( pre, pre[k] );
	printf( "%d\t", k ); 
}

void output( int (*a)[MAX], int n, const int* pre, const int* weight )
{
	int i;

	for( i = 0; i < n; ++i )
		printf( "%d------>%d\n", i, weight[i] );
	puts( "" );
	for( i = 0; i < n; ++i )
	{
		printf( "------>%d:  ", i );
		pre_output( pre, i );
		putchar( '\n' );
	}	
}


int main( void )
{
	int a[MAX][MAX];
	int n, m;
	int pre[MAX];
	int weight[MAX];
	int i;

	init( a, &n, &m );
	dijkstra( a, n, m, pre, weight, 0 );
	output( a, n, pre, weight );

	return 0;
}
