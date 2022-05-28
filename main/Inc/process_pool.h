#ifndef PROCESS_POOL_H
#define PROCESS_POOL_H


#include "error_types.h"
#include "process.h"

typedef struct process_pool_element process_pool_element_t;

struct process_pool_element
{
    process_t process;
    process_pool_element_t *next;
};

struct
{
    process_pool_element_t** start;
    int current_size;

}typedef process_pool_t;

//Points the start to null
error_status_t Pool_Init(process_pool_t* pool);

//Add an ellement to the array after the giving index 
//copying the data pointed by process to a new allocated chunk
//of memory
error_status_t Pool_AddEllementByIndex(process_pool_t* pool,
                                      process_t* process, int index);

//Remove and deallocate the memory of the node corresponding to the giving
//index
error_status_t Pool_RemoveEllementByIndex(process_pool_t* pool, int index);

//Swap the order of the first ellement with the second one
error_status_t Pool_SwapNodeOrder(process_pool_t* pool, int index_a, int index_b);

//Get the ellement by index if possible
error_status_t Pool_GetEllementByIndex(process_pool_t* pool,
                                        process_t* process, int index);

#endif