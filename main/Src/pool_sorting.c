#include "pool_sorting.h"

#include <stdlib.h>
#include <stdio.h>


error_status_t PoolSort_Print(process_pool_t* pool)
{
    error_status_t status = SUCCESS;

    if(pool == NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;
    }

    printf("\nStart---------\n");

    if(pool->current_size == 0)
    {
        status = LIST_EMPTY;
        printf("Pool Empty\n");
        goto FINISH;
    }

    process_t proc;

    for(int i = 0; i < pool->current_size; i++)
    {
        Pool_GetEllementByIndex(pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    printf("End----------\n\n");

FINISH:
    return status;
}

error_status_t PoolSort_ByTime(process_pool_t* pool)
{
    error_status_t status = SUCCESS;

    printf("a\n");

    if(pool == NULL)
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

    process_t process_to_be_inserted;
    process_t tested_process;


    printf("Before Sorting: \n");
    PoolSort_Print(pool);

    //Insertion Sort
    for(int item_to_be_inserted_index = 1, tested_item_index;
        item_to_be_inserted_index < pool->current_size;
        item_to_be_inserted_index++)
    {
        tested_item_index = item_to_be_inserted_index - 1;

        Pool_GetEllementByIndex(pool, &process_to_be_inserted, item_to_be_inserted_index);

        printf("item_to_be_inserted_index: %d\n", item_to_be_inserted_index);

        while(tested_item_index >= 0)
        {
            //printf("\ttested_item_index: %d\n", tested_item_index);
            //PoolSort_Print(pool);

            Pool_GetEllementByIndex(pool, &tested_process, tested_item_index);
            
            printf("Tested Proc: %s Proc_insert: %s\n",
                tested_process.NomeProcesso, process_to_be_inserted.NomeProcesso);
            if(tested_process.TempoExec > process_to_be_inserted.TempoExec)
            {
                Pool_SwapNodeOrder(pool, tested_item_index, item_to_be_inserted_index);
            }
            else
            {
                break;
            }

            tested_item_index--;
            
            getchar();
        }



        
    }

    printf("Done Sorting: \n");
    PoolSort_Print(pool);

FINISH:
    return status;
}
