#include "kernel.h"


error_status_t Kernel_Init(kernel_t* kernel)
{
    error_status_t status = SUCCESS;

    Pool_Init(&(kernel->pool));

    return status;
}

error_status_t Kernel_Loop(kernel_t* kernel)
{
    error_status_t status = SUCCESS;
    process_t current_process;


    while(kernel->pool.current_size > 0)
    {
        Pool_GetEllementByIndex(&(kernel->pool), &current_process, 0);
        
        current_process.ExecutionFunction();

        //Press enter to "clock"
        getchar();

        Pool_RemoveEllementByIndex(&(kernel->pool), 0);

        if(current_process.process_execution_class == REPEAT)
        {
            Pool_AddEllementByIndex(&(kernel->pool), &current_process, kernel->pool.current_size);
        }
    }


    return status;
}