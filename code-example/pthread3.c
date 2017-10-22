#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;

void* runner( void* param );

int main( int argc, char* argv[] ) {

  pthread_t tid;
  pthread_attr_t attr;

  if ( argc != 2 ) {
    fprintf(stderr, "Usage: %s <int>\n", argv[0]);
    exit(-1);  
  }
  if (atoi( argv[1] ) < 0 ) {
    fprintf(stderr, "Arg must be >= 0.\n");
    return -1;
  }

  pthread_attr_init( &attr ) ;

  pthread_create(&tid, &attr, &runner, argv[1]);
  pthread_join( tid, NULL );
  printf( "Sum = %d.\n", sum );

  pthread_exit( NULL );
}

void* runner( void* param ) {
  int i; 
  int max = atoi( param );
  for (i = 1; i <= max; ++i ) {
     sum += i;
  }
  pthread_exit( NULL );
}




 
