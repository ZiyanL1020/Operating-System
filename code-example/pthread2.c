#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
  int p1;
  int p2;
} params_t;

void* hello( void* arg ) {
  int* id = (int*) arg;
  printf("Hello from thread %d.\n", *id);
  pthread_exit(0);
}

int main( int argc, char** argv ) {
  
  printf("Number of args is %d.\n", argc);
  if ( argc != 2 ) {
    printf("Error! Wrong number of arguments.\n");
    return -1;
  }
  for (int i = 0; i < argc; ++i) {
    printf("Argument %d: %s\n", i, argv[i]);
  }
  
  int num_threads = atoi( argv[1] ); 
  printf("Number of threads is %d.\n", num_threads); 

  if (num_threads <= 0) {
   printf("Invalid number of threads specified.\n");
   abort();
  }

  pthread_t * threads = malloc( num_threads * sizeof( pthread_t ) );
  int * ids = malloc( num_threads * sizeof( int ) ); 

  for ( int j = 0; j < num_threads; ++j ) {
    ids[j] = j;
    pthread_create( &threads[j], NULL, hello, &ids[j] );
  }

  for ( int k = 0; k < num_threads; ++k ) {
    pthread_join( threads[k], NULL );
  }

  free( ids );
  free( threads );

  pthread_exit(0);
}
