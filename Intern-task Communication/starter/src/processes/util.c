#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>

mqd_t openQueue(char* name, int permission){
    mqd_t queue = mq_open(name, permission);
    if(queue == -1){
        printf("mq_open() failed to open queue: %s\n", name);
        exit(EXIT_FAILURE);
    }
    
    return queue;
}

//struct mq_attr createQueueAttr(mq_maxmsg max_msg, mq_msgsize size, mq_flags flags){
//    struct mq_attr queue_attribute;
//    queue_attribute.mq_maxmsg = max_msg;
//    queue_attribute.mq_msgsize = size;
//    queue_attribute.mq_flags = flags;
//
//    return queue_attribute;
//}
mqd_t createQueue(char* name, int permission, mode_t mode, struct mq_attr attr){
    mqd_t queue = mq_open(name, permission, mode, &attr);
    if (queue == -1 ) {
        printf("mq_open() failed to create queue:%s\n", name);
        exit(EXIT_FAILURE);
    }
    
    return queue;
}

void sendMessage(mqd_t queue, char* msg_ptr, size_t msg_len, unsigned int priority){
    if(mq_send(queue, msg_ptr, msg_len, priority) == -1){
        printf("Failed to send message to queue\n");
        exit(EXIT_FAILURE);
    }
}

void receiveMessage(mqd_t queue, char* msg_ptr, size_t msg_len, unsigned int* priority){
    if(mq_receive(queue, msg_ptr, msg_len, priority) == -1){
        printf("Failed to retrieve message from message queue\n");
        exit(EXIT_FAILURE);
    }
}

void closeQueue(mqd_t queue){
    if(mq_close(queue) == -1){
        printf("mq_close() failed to close queue\n");
        exit(EXIT_FAILURE);
    }
}

void unlinkQueueName(char* name){
    if(mq_unlink(name) != 0) {
        perror("mq_unlink() failed to unlink message queue name\n");
        exit(EXIT_FAILURE);
    }
}

void cleanUpQueue(mqd_t queue, char* name){
    closeQueue(queue);
    unlinkQueueName(name);
}


