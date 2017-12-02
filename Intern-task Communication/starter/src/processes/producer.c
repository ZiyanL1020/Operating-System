#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <error.h>

const int MSG_SIZE = sizeof(int);

int main(int argc, char* argv[]){
    
    /**Standard error checking**/
    if(argc != 5){
        perror("Have to provide 4 arguments to the producer process\n");
        return -1;
    }
    
    /**Convert conmmand line arguments into variables**/
    int num_of_integers = atoi(argv[1]);
    int id = atoi(argv[2]);
    int num_of_producers = atoi(argv[3]);
    
    /**More error checking**/
    if(num_of_integers < 0 || id < 0 || num_of_producers < 0){
        perror("Invalid argument");
        return -1;
    }
    
    /**Open message queue**/
    mqd_t msg_queue = openQueue("/message_queue", O_RDWR);
    
    /**Producers generate numbers and sent them to the message queue**/
    int i = 0;
    for(i = id; i < num_of_integers; i+= num_of_producers){
        char* msg = (char*) &i;
        sendMessage(msg_queue, msg, MSG_SIZE, 0);
    }
    
    /**Clean up**/
    closeQueue(msg_queue);
    
    return 0;

}
