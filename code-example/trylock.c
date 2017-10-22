#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* run( void* arg ) {
 
  for (int i = 0; i < 100000; ++i ) { 
    
    int succeeded = 0;
    while( succeeded == 0 ) {
      int r1 = pthread_mutex_trylock( &mutex1 );
      int r2 = pthread_mutex_trylock( &mutex2 );
      if (r1 != 0 && r2 == 0) {
        pthread_mutex_unlock( &mutex2 );
      } else if (r1 == 0 && r2 != 0 ) {
        pthread_mutex_unlock( &mutex1 );
      } else if (r1 != 0 && r2 != 0 ) {
         /* Do nothing */
      } else {
        succeeded = 1;
      }
    }

    pthread_mutex_unlock( &mutex1 );
    pthread_mutex_unlock( &mutex2 );
  }
  pthread_exit( NULL );
}

void* run2( void* arg ) {
  for (int i = 0; i < 100000; ++i ) {
    pthread_mutex_trylock( &mutex2 );
    pthread_mutex_trylock( &mutex1 );

    pthread_mutex_unlock( &mutex2 );
    pthread_mutex_unlock( &mutex1 );
  }
  pthread_exit( NULL );

}

int main( int argc, char** argv ) {

   pthread_t t1; 
	 pthread_t t2;

   pthread_mutex_init( &mutex1, NULL );
   pthread_mutex_init( &mutex2, NULL );

   pthread_create(&t1, NULL, run, NULL);
   pthread_create(&t2, NULL, run2, NULL);

   pthread_join(t1, NULL);
   pthread_join(t2, NULL);

   pthread_mutex_destroy( &mutex1 );
   pthread_mutex_destroy( &mutex2 );
  pthread_exit( NULL );
}


