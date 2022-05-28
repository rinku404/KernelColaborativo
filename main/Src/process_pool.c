#include "process_pool.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

error_status_t Pool_Init(process_pool_t* pool)
{
    error_status_t status = SUCCESS;

    if(pool == NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;
    }

    pool->start = (process_pool_element_t**)malloc(sizeof(process_pool_element_t*));
    if(pool->start == NULL)
    {
        status = MEMORY_ALLOCATION_FAILED;
        goto FINISH;
    }
    pool->current_size = 0;
    *(pool->start) = NULL;

FINISH:
    return status;
}

error_status_t Pool_AddEllementByIndex(process_pool_t* pool,
                                       process_t* process, int index)
{
    error_status_t status = SUCCESS;

    if(pool == NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;
    }

    if(process == NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;  
    }

    if(index > pool->current_size || index < 0)
    {
        status = INDEX_OUT_OF_RANGE;
        goto FINISH;
    }

    //Insert on list start
    if(index == 0)
    {
        process_pool_element_t* node = 
        (process_pool_element_t*)malloc(sizeof(process_pool_element_t));

        if(node == NULL)
        {
            status = MEMORY_ALLOCATION_FAILED;
            goto FINISH;
        }

        node->process = *process;
        node->next = *(pool->start);
        *(pool->start) = node;

        pool->current_size++;

        //printf("%s\n", node->process.NomeProcesso);
    }

    //Insert on list end
    else if(index == pool->current_size)
    {
        process_pool_element_t* node = 
        (process_pool_element_t*)malloc(sizeof(process_pool_element_t));

        if(node == NULL)
        {
            status = MEMORY_ALLOCATION_FAILED;
            goto FINISH;
        }  

        node->process = *process;
        node->next = NULL;
        
        process_pool_element_t *aux = *(pool->start);

        while(aux->next != NULL)
        {
            aux = aux->next;
        }

        aux->next = node;

        pool->current_size++;
    }

    //Insert on any point of the list
    else
    {
        process_pool_element_t* node = 
        (process_pool_element_t*)malloc(sizeof(process_pool_element_t));

        if(node == NULL)
        {
            status = MEMORY_ALLOCATION_FAILED;
            goto FINISH;
        }  

        node->process = *process;
        
        
        process_pool_element_t *aux = *(pool->start);

        for(int i = 0; i < index - 1; i++)
        {
            aux = aux->next;
        }

        node->next = aux->next;
        aux->next = node;

        pool->current_size++;
    }

    

FINISH:
    return status;
}

error_status_t Pool_GetEllementByIndex(process_pool_t* pool,
                                        process_t* process, int index)
{
    error_status_t status = SUCCESS;

    if(pool == NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;
    }

    if(process == NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;  
    }

    if(index > pool->current_size || index < 0)
    {
        status = INDEX_OUT_OF_RANGE;
        goto FINISH;
    }

    if(pool->current_size == 0)
    {
        status = LIST_EMPTY;
        goto FINISH;
    }

    process_pool_element_t *node = *(pool->start);

    for(int i = 0; i < index; i++)
    {
        node = node->next;
    }

    *process = node->process;


FINISH:
    return status;
}

error_status_t Pool_RemoveEllementByIndex(process_pool_t* pool, int index)
{
    error_status_t status = SUCCESS;

    if(pool == NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;
    }

    if(index > pool->current_size || index < 0)
    {
        status = INDEX_OUT_OF_RANGE;
        goto FINISH;
    }

    if(pool->current_size <= 0)
    {
        status = LIST_EMPTY;
        goto FINISH;
    }

    //Remove Fom Start
    if(index == 0)
    {
        process_pool_element_t *node = *(pool->start);
        *(pool->start) = node->next;
        free(node);

        pool->current_size--;

        goto FINISH;
    }

    //Remove From End
    else if(index == pool->current_size && index != 1)
    {
        process_pool_element_t *node = *(pool->start);
        process_pool_element_t *prev;
        
        while(node->next != NULL)
        {
            prev = node;
            node = node->next;
        }

        prev->next = node->next;
        free(node);

        pool->current_size--;

        goto FINISH;
    }


    //Remove From Middle
    else
    {
        process_pool_element_t *node = *(pool->start);
        process_pool_element_t *prev;
        
        for(int i = 0; i < index; i++)
        {
            prev = node;
            node = node->next;
        }

        prev->next = node->next;
        free(node); 

        pool->current_size--; 

        goto FINISH;
    }


FINISH:
    return status;
}

error_status_t Pool_SwapNodeOrder(process_pool_t* pool, int index_a, int index_b)
{
    error_status_t status = SUCCESS;

    if(pool == NULL)
    {
        status = MEMORY_NOT_ALLOCATED;
        goto FINISH;
    }

    if(index_a > pool->current_size || index_a < 0)
    {
        status = INDEX_OUT_OF_RANGE;
        goto FINISH;
    }

    if(index_b > pool->current_size || index_b < 0)
    {
        status = INDEX_OUT_OF_RANGE;
        goto FINISH;
    }

    if(index_a == index_b)
    {
        status = INDEX_OUT_OF_RANGE;
        goto FINISH;
    }

    if(pool->current_size < 2)
    {
        status = LIST_EMPTY;
        goto FINISH;
    }

    if(index_a > index_b)
    {
        int index_aux;

        index_aux = index_b;
        index_b = index_a;
        index_a = index_aux;
    }


    process_pool_element_t *node_a = *(pool->start);

    process_pool_element_t *node_b = *(pool->start);
    process_pool_element_t *prev_b;

    process_pool_element_t aux_node_a, aux_node_b;
    process_pool_element_t aux_prev_a, aux_prev_b;

    for(int i = 0; i < index_b; i++)
    {
        prev_b = node_b;
        node_b = node_b->next;
    }

    if(index_a == 0)
    {
        *(pool->start) = node_b;   
    }
    else
    {
        process_pool_element_t *prev_a;

        for(int i = 0; i < index_a; i++)
        {
            prev_a = node_a;
            node_a = node_a->next;
        }

        aux_prev_a = *prev_a;
        prev_a->next = node_b;
    }

    aux_node_a = *node_a;
    aux_node_b = *node_b;
    aux_prev_b = *prev_b;

    prev_b->next = node_a;
    node_a->next = aux_node_b.next;
    node_b->next = aux_node_a.next;


FINISH:
    return status;
}

error_status_t Pool_Clear(process_pool_t* pool)
{
    error_status_t status = SUCCESS;

    while(pool->current_size != 0)
    {
        Pool_RemoveEllementByIndex(pool, 0);
    }

    if(*(pool->start) != NULL)
    {
        free(*(pool->start));
    }

    if((pool->start) != NULL)
    {
        free((pool->start));
    }

    printf("Pool cleared\n");

FINISH:
    return status;
}