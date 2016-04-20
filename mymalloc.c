#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h"

//finding a free memory space using first fit algorithm
block *find_free_block(size_t s){
	block *fitting_slot = freeArray; 	//declare and initialize a block type pointer pointing to the first location of the 'memory_arr'
	
	while(((fitting_slot->next)!=NULL) && (((fitting_slot->size)<s)||((fitting_slot->isFree)!=1))){ //find the first fitting free block
		fitting_slot = fitting_slot->next;
	}
	
	return (fitting_slot); //return a pointer to the fitting free block

}
//mymalloc(size_t reqSpace) function
void *mymalloc(size_t reqSpace){
	block *fit_Curr_Meta;	 				//declare a block type pointer
	void *fit_data_Ptr; 					//declare a void pointer, pointing to the fitting block's data part
	
	if (reqSpace <= 0) {
    	return NULL;						//if required space is zero or negative value, then return NULL
    	
  	}else{		
		if(!(freeArray -> size)){						//initialize the memory array if it's not set initially.
			freeArray -> size = 20000 - BLOCKSIZE; 		//initial size of the data block
			freeArray -> isFree = 1; 					//initially it's free
			freeArray -> next = NULL;					//initially it does not have a next pointer
			
			
		}
		fit_Curr_Meta = find_free_block(reqSpace); //finding a suitable free block to be allocated
		
		if((fit_Curr_Meta->size) > reqSpace){ //size of the fitting free block is larger than the requested memory size
			block *new_meta_block = (void*)((void*)fit_Curr_Meta+BLOCKSIZE+reqSpace); //create a new block to keep separate the unused memory block size as free.
			new_meta_block -> size = (fit_Curr_Meta->size)-reqSpace-BLOCKSIZE; //set the size of the unused memory block
			new_meta_block -> isFree = 1; 				   //set the unused memory block as free
			new_meta_block -> next = fit_Curr_Meta->next; //set the next pointer of the unused memory block
			
			fit_Curr_Meta -> size = reqSpace; 		//set the size of the allocated memory block
			fit_Curr_Meta -> isFree = 0; 			//set it as not free
			fit_Curr_Meta -> next = new_meta_block; //set it's next pointer
			
			fit_data_Ptr = (void*)(++fit_Curr_Meta); //set the pointer to the starting point of the allocated data block
			return fit_data_Ptr; 					  //return the pointer to starting address of the allocated data block of memory
		}
		else if((fit_Curr_Meta -> size) == reqSpace){ //size of the fitting free block is same as the size of the requested memory size
			fit_Curr_Meta -> isFree = 0; 			  //set the fitting block to not free
			fit_data_Ptr = (void*)(++fit_Curr_Meta);  //set the pointer to the starting address of the allocated data block
			return fit_data_Ptr;					  //return the pointer to starting address of the allocated data block of memory
			
		}
		else{                                        //there is no sufficient memory to allocate
			fit_data_Ptr = NULL; 
			printf("No sufficient memory to allocate\n");
			return fit_data_Ptr;					// return a null pointer
		}
	}
}
//myfree(void *needToFree) function
void myfree(void *needToFree){
	int lower = (int)(needToFree - (void *)memory_arr); //lower bound checking value
	void *upper = (void*)(memory_arr+20000); //upper bound checking pointer
	
	if((lower > 0) && (needToFree <= upper)){ //checking whether the requested 'needToFree' pointer is pointing to somewhere within the memory array
		block *free_data = needToFree; //declare and initialize a block type pointer,pointing to the starting address of the data block 
									   //which is needed to be free
		--free_data;				   //reduce the pointer as it is pointing to the meta data block of the respective data block
		free_data -> isFree = 1;	   //set the data block as free.
		
		
		//concatanate the adjacent free blocks
		block *cur_merge = freeArray; //declare and initialize a block type pointer,pointing to the starting address of the memory array
		while((cur_merge -> next)!=NULL){ //loop through until the *next is not NULL
			if((!(cur_merge -> isFree)) || (!(cur_merge -> next -> isFree))){ //if 2 adjacent memory chunks are not empty
				cur_merge  = cur_merge  -> next;
			}else{ 
				cur_merge -> size += (cur_merge -> next -> size)+BLOCKSIZE; //concatanate the sizes of 2 chunks
				cur_merge -> next = cur_merge -> next -> next; //set the next pointer
    	   	
    	   
			}
		}
		
	}else{   
		//requested 'needToFree' pointer is not pointing to somewhare within the memory array
		printf("Pointer is not in the range of the memory array");
	}
	
}
//print_memory() function
void print_memory()
{
    int index=400; //initialize the index as 0
    for(index; index < 600 ; index++) //loop through the memory array
    {
        printf("memory_arr[%d] = %c\n", index, memory_arr[index]); //print the content of each memory address. 
    }
}

