#include <stdio.h> 
#include <stdlib.h> 
#include "mem.h"
#include "util.h"

/***round N bytes to (N+δ) which is multiple of 4***/
size_t round_size(size_t size)
{	
	int remainder = size % 4;
	size = size + (4- remainder);
	return size;
}

/***find the largest block which is at leaast greater than min***/
node* get_largest_free_node(node* front, int min) {
	node* largest = NULL;
	node* n = front;
	while(n){
		if (n->free == true)
		{
			if( n->size >= min && (!largest || n->size > largest->size) )
				largest = n;
		}

		n = n->next;
	}

	if(!largest)
		return NULL;
	else
		return largest;
}

/***find the smallest block which is at leaast greater than min***/
node* get_least_free_node(node* front, int min) {
	node* least = NULL;
	node* n = front;
	while(n){
		if (n->free == true)
		{
			if( n->size >= min && (!least ||n->size < least->size) )
				least = n;
		}

		n = n->next;
	}

	if(!least)
		return NULL;
	else
		return least;
}

/***recombine two free nodes***/
void coalesce(node* start) {

	if(start->previous && start->previous->free == true){
		start = start->previous;
		node* end = start->next;
		//if end node is not the last node
		if(end->next){
			start->next = end->next;
			end->next->previous = start;
		}
		//if end node is the last node
		else
		{
			end->previous->next = start;
			start->next = NULL;
		}
	
		start->size = start->size + end->size + sizeof(node);		
	}

	if(start->next && start->next->free == true){
		node* end = start->next;
		//if end node is not the last node
		if(end->next){
			start->next = end->next;
			end->next->previous = start;
		}
		//if end node is the last node
		else
		{
			end->previous->next = start;
			start->next = NULL;
		}
		start->size = start->size + end->size + sizeof(node);		
	}
	return;
}

/***insert node**/
node* split_node(node* fit_node, size_t allocate_num){

	int child_total_size = fit_node->size - allocate_num;

	if (child_total_size < LEAST_NODE_SIZE)
	{
		//not enough space to allocate even a node
	}
	else
	{
		node* child = (node*)fit_node->start_address + allocate_num;
		
		child->size = child_total_size - sizeof(node);
		child->start_address = child + sizeof(node);
		child->free = true;
		
		child->previous = fit_node;
		child->next = fit_node->next;		
		if(fit_node->next) {
			fit_node->next->previous = child;
		}

		fit_node->next = child;
		fit_node->size = allocate_num;
	}
	fit_node->free = false;
	return fit_node;
}
