#ifndef KERNEL_H
#define KERNEL_H

#include "process.h"
#include "process_pool.h"
#include "error_types.h"

struct
{
    process_pool_t pool;

}typedef kernel_t;

error_status_t Kernel_Init(kernel_t* kernel);
error_status_t Kernel_Loop(kernel_t* kernel);

#endif