/**
 * @file memory.c
 * @brief: ECE254 Lab: memory allocation algorithm comparison template file
 * @author: 
 * @date: 2015-11-20
 */

/* includes */
#include <stdio.h> 
#include <stdlib.h>
#include "mem.h"
#include "util.h"
#include <error.h>


//record the first node of linked list
//record total size of liked list
node* bf_front;
size_t bf_total_size;

node* wf_front;
size_t wf_total_size;

void print_list(node* start) {
    int i = 1;
    node* n = start;
    printf("\n");
    while(n){
        printf("Node #: %2d | Previous: %10p | Next: %10p | Start Address: %10p | Size: %4d | Is Free: %4s\n",
               i, n->previous, n->next, n->start_address, n->size, (n->free == true) ? ("True") : ("False") );
        i++;
        n = n->next;
    }
    printf("Node size = %ld\n\n", sizeof(node));
    
}

void best_fit_print() {
    print_list(bf_front);
}

void worst_fit_print() {
    print_list(wf_front);
}


node* mem_init(node* front, size_t size)
{
	/***The request cannot be less than the smallest size ***/
	if (size < LEAST_NODE_SIZE)
		return NULL;
    
	void* chunck = malloc(size);
	
	/*** Check if malloc failed***/
    if (chunck == NULL){
        printf("Failed to init memory of size %zd\n\n", size);
        return NULL;
    }
	
	front = (node*)chunck;
	front->next = NULL;
	front->previous = NULL;
	front->start_address = chunck + sizeof(node);
	front->size = size - sizeof(node);
	front->free = true;
    
    printf("Initialized memory of size %zd\n\n", size);
	return front;
}


void* mem_allocate(node* front, size_t size, int bf_wf)
{
    /***Standard error checking**/
	/***Memory request is not a valid number**/
    if (size <= 0){
        perror("Error - The requested memory size has to be larger than 0\n");
        return NULL;
    }
    
    /**Determine if the request is best-fit or worst-fit**/
	int total_size = (bf_wf) == 0 ? bf_total_size : wf_total_size;
    
    /***Memory request exceeds the total size available**/
    if (size >= total_size){
        perror("Error - The requested memory size cannot be larger than the total size available\n");
        return NULL;
    }

	/**Round the request to the nearest multiple of 4**/
	size_t allocate_num = round_size(size);
    
    /**Retrieve the free node based on different algorithms**/
    node* fit_node = NULL;
    switch(bf_wf){
        case BEST_FIT:
            if (!get_largest_free_node(front, allocate_num)){
                printf("Requested %zd bytes -> Aborted due to not enough memory left\n", size);
                return NULL;
            }
            fit_node = get_least_free_node(front, allocate_num);
            break;
        case WORST_FIT:
            fit_node = get_largest_free_node(front, allocate_num);
            break;
    }
    /**Check if the free node is valid**/
    if(fit_node == NULL){
        printf("Requested %zd bytes -> Aborted due to not enough memory left\n", size);
        return NULL;
    }
	
    /**Split the node into the allocated chunk and the free chunk**/
	fit_node = split_node(fit_node, allocate_num);
    
    printf("Requested %zd bytes -> Rounded and allocated %zd bytes\n", size, allocate_num);
	return fit_node->start_address;
}

void mem_deallocate(void* ptr, node* front)
{

    /**Iterate through the list and find the node with desired start address**/
	node* target = NULL;
	node* n = front;
	while(n){
		if(n->start_address == ptr) {
			target = n;
			break;
		}
		n = n->next;		
	}
    
    /**If there is no such node, throw error**/
    if(!target){
        perror("Error - Unable to deallocate the node because it does not exist in the list\n");
        return;
    }
	
    /**Free the target node and coalesce**/
	target->free = true;
    printf("Deallocated node %p %d bytes\n", target->start_address, target->size);
    coalesce(target);
    
	return;
}

int mem_count_extfrag(node* front, size_t size)
{
    /**Count the num of external fragments less than the specified size**/
	int total = 0;
	node* n = front;
	while(n){
        printf("size = %zd n->size = %d n->free = %s\n",size, n->size, (n->free == true) ? ("True"):("False"));
		if(n->size < size && n->free == true){
			total++;
           printf("Total = %d\n", total);
		}
		n = n->next;		
	}	

	return total;	
}

/* memory initializer */
int best_fit_memory_init(size_t size)
{
	bf_total_size = size;
	bf_front = mem_init(bf_front, size);

	if (bf_front)
	{
		return 0;
	}
	else
	{
        perror("Error - failed to init the best-fit memory pool\n");
		return -1;
	}
}

int worst_fit_memory_init(size_t size)
{
	wf_total_size = size;
	wf_front = mem_init(wf_front, size);

	if (wf_front)
	{
		return 0;
	}
	else
	{
        perror("Error - failed to init the worst-fit memory pool\n");
		return -1;
	}

}

/* memory allocators */
void *best_fit_alloc(size_t size)
{
    /***choose the smallest block that is at least as big as size***/
    void* result = mem_allocate(bf_front, size, BEST_FIT);
    best_fit_print();
    return result;
}


void *worst_fit_alloc(size_t size)
{
    /***choose the largest block available***/
    void* result = mem_allocate(wf_front, size, WORST_FIT);
    worst_fit_print();
    return result;
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) 
{
    /***Deallocate node with specified address***/
	mem_deallocate(ptr, bf_front);
    best_fit_print();
}

void worst_fit_dealloc(void *ptr) 
{
    /***Deallocate node with specified address***/
	mem_deallocate(ptr, wf_front);
    worst_fit_print();
}


/* memory algorithm metric utility function(s) */

int best_fit_count_extfrag(size_t size)
{
    /**Count the num of external fragments less than the specified size**/
	return mem_count_extfrag(bf_front, size);
}

int worst_fit_count_extfrag(size_t size)
{
    /**Count the num of external fragments less than the specified size**/
	return mem_count_extfrag(wf_front, size);
}

