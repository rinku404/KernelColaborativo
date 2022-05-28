#ifndef POOL_SORTING_H
#define POOL_SORTING_H

#include "error_types.h"
#include "process_pool.h"

//Print The Pool Names
error_status_t PoolSort_Print(process_pool_t* pool);

//Sort The Current Processes on the pool by time
//putting the fastests first
error_status_t PoolSort_ByTime(process_pool_t* pool);

error_status_t PoolSort_ByPriority(process_pool_t* pool);

error_status_t PoolSort_ByPriorityAndTime(process_pool_t* pool);

#endif