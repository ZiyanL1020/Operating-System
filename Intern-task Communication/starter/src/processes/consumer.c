#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <error.h>
#include <math.h>
#include "util.h"

const int MSG_SIZE = sizeof(int);

int isPerfectSquare(int number){
    
    double double_val = sqrt((double)number);
    int int_val = (int) double_val;
    
    return double_val == int_val ? 1 : 0;
}

int main(int argc, char* argv[]){
    
    /**Standard error checking**/
    if(argc != 5){
        perror("Have to provide 4 arguments to the consumer process\n");
        return -1;
    }
    
    /**Convert conmmand line arguments into variables**/
    int num_of_integers = atoi(argv[1]);
    int id = atoi(argv[2]);
 
    /**Open message queue with read only access**/
    mqd_t msg_queue = openQueue("/message_queue", O_RDONLY);
    
    /**Open consumption queue**/
    mqd_t consumption_queue = openQueue("/consumption_queue", O_RDWR);
    
    int consumed;
    int message;
    for(;;){
        /**Check the total num of msgs have been consumed**/
        char* msg_consumed = (char*)&consumed;
        receiveMessage(consumption_queue, msg_consumed, MSG_SIZE, 0);
        
        if(consumed == 0){
            sendMessage(consumption_queue, msg_consumed, MSG_SIZE, 0);
            break;
        }else{
            consumed--;
            sendMessage(consumption_queue, msg_consumed, MSG_SIZE, 0);
        }
        
        /**Retrieve the message from the message queue**/
        receiveMessage(msg_queue, (char *) &message, MSG_SIZE, 0);
        
        if(isPerfectSquare(message)){
            printf("%d %d %d \n", id, message, (int)sqrt(message));
        }
    }
    
    /**Clean up**/
    closeQueue(msg_queue);
    closeQueue(consumption_queue);
    
    return 0;
}
