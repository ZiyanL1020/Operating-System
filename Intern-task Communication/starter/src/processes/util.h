#ifndef util_h
#define util_h

#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>

mqd_t openQueue(char* name, int permission);
//struct mq_attr createQueueAttr(mq_maxmsg max_msg, mq_msgsize size, mq_flags flags);
mqd_t createQueue(char* name, int permission, mode_t mode, struct mq_attr attr);
void sendMessage(mqd_t queue, char* msg_ptr, size_t msg_len, unsigned int priority);
void receiveMessage(mqd_t queue, char* msg_ptr, size_t msg_len, unsigned int priority);
void closeQueue(mqd_t queue);
void unlinkQueueName(char* name);
void cleanUpQueue(mqd_t queue, char* name);

#endif
