#include <stdio.h>
#include <stddef.h>

typedef struct meta_data_block block; 	//'struct meta_data_block' can be refered as 'block'

struct meta_data_block{ 				//structure holding information about the data block
	size_t size; 						//size of the data block
	int isFree; 						//if free, 1. else 0.
	block *next; 						//block type pointer to the next meta_data_block
};

#define BLOCKSIZE sizeof(block) 		//size of the meta_data_block

char memory_arr[20000]; 				//character array which is used as memory

block *freeArray = (void*)memory_arr; 	//block type pointer which is pointing to the first location of the 'memory_arr'

//function definitions defined in mymalloc.c
block *find_free_block(size_t size);
void *mymalloc(size_t mem_space);
void myfree(void *ptr);
void print_memory();

