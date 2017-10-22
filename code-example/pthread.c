#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* foo( void* arg );

int main( int argc, void** argv) {
  
  pthread_t thread;
  int* param = malloc( sizeof(int) );
  *param = 25;

  void* rval;
  
  pthread_create( &thread, NULL, foo, param );
  pthread_join( thread, &rval ); 
   
  int* intval = (int*) rval;
  printf("Thread running foo returned %d.\n", *intval); 
  free( rval );

  return 0;
}

void* foo( void* arg ) {
  int* p = (int*) arg;
  printf("Parameter value is %d.\n", *p);
  int * r = malloc( sizeof(int) );
  *r = 42;
  free( p );

  pthread_exit( r );
}
