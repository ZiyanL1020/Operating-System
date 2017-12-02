#include <semaphore.h>
#include <math.h>
#include <error.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int num_of_integers;
int buffer_size;
int num_of_producers;
int num_of_consumers;

int* buffer;
int consumed;
int produced;
int buffer_count;


pthread_mutex_t mutex;
sem_t spaces;
sem_t items;

int isPerfectSquare(int number){

	double double_val = sqrt((double)number);
	int int_val = (int) double_val;
	
	return double_val == int_val ? 1 : 0;
}

double getTimestamp(){
	struct timeval tv;
        gettimeofday(&tv, NULL);
        
	return tv.tv_sec + tv.tv_usec/1000000.0;
}

void setup(){
        
	/**Init all mutex and semaphores, create the buffer**/
        buffer = (int*)malloc(sizeof(int)*buffer_size);    

        sem_init(&items, 0, 0);
        sem_init(&spaces, 0, buffer_size-1);
        pthread_mutex_init(&mutex, NULL);

        consumed = 0;
        produced = 0;
        buffer_count = 0;
}

void* produce(void* argv){

	//producer id
	int* id = (int*) argv;
	int i = 0;

	/**Continue to generate numbers until the required quantity is satisfied**/	
	while(produced < num_of_integers && i < num_of_integers){
		if(i % num_of_producers == *id){
			sem_wait(&spaces);
			pthread_mutex_lock(&mutex);
			{
				buffer_count++;
				buffer[buffer_count] = i;
				produced++;
				//printf("i = %d, produced = %d, consumed = %d\n", i, produced, consumed);
			}
			pthread_mutex_unlock(&mutex);
			sem_post(&items);
		}
		i++;
	}
	
	free(argv);
	pthread_exit(NULL);
	
}


void* consume(void* argv){
	
	//consumer id
	int* id = (int*) argv;
	int val = 0;
	
	for(;;){
		/**Finish execution when all N integers have been consumed**/
		if(consumed == num_of_integers){
			break;
		}
		
		sem_wait(&items);
		pthread_mutex_lock(&mutex);
		{
			val = buffer[buffer_count];
			buffer_count--;
			consumed++;
			if(isPerfectSquare(val) == 1){
				printf("%d %d %d \n", *id, val, (int)sqrt(val));
			}
		//		printf("From consumer %d: val = %d, buffer_count = %d, produced = %d, consumed = %d \n",*id,val,buffer_count, produced, consumed);
		}
		pthread_mutex_unlock(&mutex);
		sem_post(&spaces);			
	}
	
	free(argv);
	pthread_exit(NULL);
}

int main ( int argc, char *argv[] )
{
		/**Standard error checking**/
		if(argc != 5){
			perror("Have to provide 4 arguments");
			return -1;
		}
		
		/**Convert conmmand line arguments into variables**/
		num_of_integers = atoi(argv[1]);
		buffer_size = atoi(argv[2]);
		num_of_producers = atoi(argv[3]);
		num_of_consumers = atoi(argv[4]);
		
		/**More error checking**/
		if(num_of_integers < 0 || buffer_size < 0 || num_of_producers < 0 || num_of_consumers < 0){
			perror("Invalid argument");
			return -1;
		}
	
		/**Set up all the essential components.**/
		setup();

		/**Arrays for threads**/
        	pthread_t producer_threads[num_of_producers];
        	pthread_t consumer_threads[num_of_consumers];
		
		/**Record starting timestamp**/
		double start_ts = getTimestamp();		

		/**Create producer and consumer threads**/
		int i = 0;
		for(i = 0; i < num_of_producers; i++){
			int* argv = malloc(sizeof(int));
			*argv = i;
			pthread_create(&producer_threads[i], NULL, &produce, argv);
		}
		for(i = 0; i < num_of_consumers; i++){
			int* argv = malloc(sizeof(int));
			*argv = i;
			pthread_create(&consumer_threads[i], NULL, &consume, argv);
		}

		/**Wait until all N integers have been consumed**/		
		while(consumed < num_of_integers){
			
		}
	
		/**Record finishing timestamp**/
		double end_ts = getTimestamp();

		printf("System execution time: %f seconds\n", end_ts - start_ts);
	

		/**Clean up**/
		free(buffer);
		sem_destroy(&spaces);
		sem_destroy(&items);
		pthread_mutex_destroy(&mutex);

  		return 0;
		
		
		
}
