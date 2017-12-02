#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <error.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int num_of_integers;
int buffer_size;
int num_of_producers;
int num_of_consumers;

double getTimestamp(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    return tv.tv_sec + tv.tv_usec/1000000.0;
}

int forkandRun(char* executionStr, char** args, int id){
    
    args[0] = executionStr;
    
    /**Cast id into string to be passed as argument**/
    char id_to_str[12];
    sprintf(id_to_str, "%d", id);
    args[2] = id_to_str; // buffer size is not needed in producer/consumer processes
    
    pid_t pid = fork();
    if(pid < 0){
        perror("Fork() failed");
        exit(EXIT_FAILURE);
    }else if(pid > 0){
        /**In parent process**/
        return pid;
    }else if(pid == 0){
        execvp (executionStr, args);
    }
}

int main(int argc, char* argv[]){
    
    const int MAX_MSG = 1;
    const int MSG_SIZE = sizeof(int);
    
    /**Standard error checking**/
    if(argc != 5){
        perror("Have to provide 4 arguments\n");
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
    
    /**Create msg queue**/
    struct mq_attr msg_queue_attribute;
    msg_queue_attribute.mq_maxmsg = buffer_size;
    msg_queue_attribute.mq_msgsize = MSG_SIZE;
    msg_queue_attribute.mq_flags = 0;
    mode_t queue_mode = S_IRUSR | S_IWUSR;
    
    mqd_t msg_queue = createQueue("/message_queue", O_RDWR | O_CREAT, queue_mode, msg_queue_attribute);
    
    /**Create consumption queue**/
    struct mq_attr c_queue_attribute;
    c_queue_attribute.mq_maxmsg = MAX_MSG;
    c_queue_attribute.mq_msgsize = MSG_SIZE;
    c_queue_attribute.mq_flags = 0;
    
    mqd_t consumption_queue = createQueue("/consumption_queue", O_RDWR | O_CREAT, queue_mode, c_queue_attribute);

    
    /**Send the num of integers in total to consumption queue**/
    char* msg_ptr = (char*) &num_of_integers;
    sendMessage(consumption_queue, msg_ptr, MSG_SIZE, 0);
    
    /**Get starting timestamp**/
    double start_ts = getTimestamp();
    
    /**Create producer processes**/
    int i = 0;
    for(i = 0; i < num_of_producers; i++){
        forkandRun("./producer", argv, i);
    }
    /**Create consumer processes**/
    for(i = 0; i < num_of_consumers; i++){
        forkandRun("./consumer", argv, i);
    }
    
    /**Wait for all child processes to finish execution**/
    //source: stackoverflow
    pid_t pid;
    while (pid = waitpid(-1, NULL, 0)) {
        if (errno == ECHILD) {
            break;
        }
    }
    
    /**Get finishing timestamp**/
    double end_ts = getTimestamp();
    
    /**Print out the duration**/
    printf("System execution time: %f seconds\n", end_ts - start_ts);
    
    /**Clean up**/
    cleanUpQueue(msg_queue, "/message_queue");
    cleanUpQueue(consumption_queue, "/consumption_queue");
}
