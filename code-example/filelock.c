#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

#define NUM_THREADS 10

int lock_fd;
int shared = 0;

void* run( void* arg ) {
  int* id = (int*) arg;
  while( rename( "file.lock", "file.locked" ) == -1 ) {
		 printf("Thread %d waiting.\n", *id); 
  }

  printf("Thread %d in critical section.\n", *id);
  printf("Shared incremented from %d", shared);
  shared++;
  printf(" to %d.\n", shared);
  /* sleep( 1 );*/  
  rename("file.locked", "file.lock"); /* Unlock */

  free( arg );
  pthread_exit(NULL);
}

void* writer( void* arg ) {



  pthread_exit(NULL);
}


int main( int argc, char** argv ) {

  lock_fd = open( "file.lock", O_CREAT | O_EXCL );  
  if (lock_fd == -1 ) {
   printf( "File creation failed.\n");
   return -1;
  }

  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    int * id = malloc( sizeof( int ) );
    *id = i;
    pthread_create( &threads[i], NULL, run, id );
  }


	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join( threads[i], NULL );
	}

  close( lock_fd );
  remove( "file.lock" );

  return 0;

}
