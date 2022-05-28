#include "pool_sorting.h"

#include "stdlib.h"

error_status_t PoolSort_ByTime(process_pool_t* pool)
{
    error_status_t status = SUCCESS;

    if(pool != NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;
    }

    if(pool->current_size == 0)
    {
        status = LIST_EMPTY;
        goto FINISH;
    }

    if(pool->current_size == 1)
    {
        //Pool already sorted
        goto FINISH;
    }

    process_t process;

    //Insertion Sort
    for(int sorted_itens = 1, tested_item = 1;
        sorted_itens < pool->current_size;
        sorted_itens++)
    {


        
    }

FINISH:
    return status;
}
