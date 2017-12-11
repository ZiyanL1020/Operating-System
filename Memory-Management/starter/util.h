#ifndef util_h
#define util_h

#include <stddef.h>
#include "mem.h"


/***define a boolean type***/
typedef enum {
    false, true
}bool;

/***define double linked list***/
/***start address is some_node + sizeof(node)***/
/***size is allocate_num - sizeof(node)***/
typedef struct node{
	struct node* next;
	struct node* previous;
	void* start_address;
	int size;
	bool free;
}node;


/***define constants to represent different algotithms***/
#define BEST_FIT  0
#define WORST_FIT 1

/***define constant to represent the smallest node size***/
#define LEAST_NODE_SIZE (sizeof(node) + 4)


node* get_largest_free_node(node* front, int min);
node* get_least_free_node(node* front, int min);
void coalesce(node* start);
node* split_node(node* fit_node, size_t allocate_num);
size_t round_size(size_t size);
void print_list(node* start);

//void best_fit_print();
//void worst_fit_print();


#endif // !MEM_H_
