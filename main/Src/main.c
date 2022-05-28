#include "process.h"
#include "test_functions.h"
#include "kernel.h"
#include "process_pool.h"
#include "test_functions.h"
#include "pool_sorting.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Kernel Coração de mãe, sempre cabe mais um processo (durante runtime)

void TestProcessPoolFunctions(void);
void CreateProcesses(process_pool_t* pool);
void ProcessSchedulledByExecTime(void);
void ProcessSchedulledByPriorityOnly(void);
void ProcessSchedulledByPriorityAndExecTime(void);

int main(void)
{
    //TestProcessPoolFunctions();
    //ProcessSchedulledByExecTime();
    ProcessSchedulledByPriorityOnly();

    return 0;
}

void TestProcessPoolFunctions(void)
{
    process_pool_t pool;

    Pool_Init(&pool);
    CreateProcesses(&pool);
       

    printf("-----------\n");
    PoolSort_Print(&pool);

    Pool_SwapNodeOrder(&pool, 0, 1);
    printf("----Swapped 0 and 1\n");
    PoolSort_Print(&pool);

    Pool_SwapNodeOrder(&pool, 2, 3);
    printf("----Swapped 2 and 3\n");
    PoolSort_Print(&pool);

    Pool_SwapNodeOrder(&pool, 1, 3);
    printf("----Swapped 1 and 3\n");
    PoolSort_Print(&pool);

    Pool_SwapNodeOrder(&pool, 3, 0);
    printf("----Swapped 3 and 0\n");
    PoolSort_Print(&pool);

    Pool_RemoveEllementByIndex(&pool, 0);
    printf("-----Remove 0\n");
    PoolSort_Print(&pool);

    Pool_RemoveEllementByIndex(&pool, pool.current_size - 1);
    printf("-----Remove last\n");
    PoolSort_Print(&pool);

    Pool_RemoveEllementByIndex(&pool, 1);
    printf("-----Remove 1\n");
    PoolSort_Print(&pool);
}

void CreateProcesses(process_pool_t* pool)
{
    process_t process;

    {
        char name[] = "A Proc";

        Process_Init(&process);
        Process_SetName(&process, name, sizeof(name));
        process.TempoExec = 3;
        process.Prioridade = 1;
        process.ExecutionFunction = PrintMessageA;
        process.process_execution_class = REPEAT;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    {
        char name[] = "B Proc";

        Process_Init(&process);
        Process_SetName(&process, name, sizeof(name));
        process.TempoExec = 2;
        process.Prioridade = 4;
        process.ExecutionFunction = PrintMessageB;
        process.process_execution_class = ONCE;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    {
        char name[] = "C Proc";

        Process_Init(&process);
        Process_SetName(&process, name, sizeof(name));
        process.TempoExec = 1;
        process.Prioridade = 2;
        process.ExecutionFunction = PrintMessageC;
        process.process_execution_class = REPEAT;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    {
        char name[] = "D Proc";

        Process_Init(&process);
        Process_SetName(&process, name, sizeof(name));
        process.TempoExec = 5;
        process.Prioridade = 3;
        process.ExecutionFunction = PrintMessageD;
        process.process_execution_class = ONCE;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

}

void ProcessSchedulledByExecTime(void)
{
    kernel_t kernel;

    printf("Initializing Kernel\n");
    Kernel_Init(&kernel);

    printf("Creating Processes\n");
    CreateProcesses(&kernel.pool);

    printf("\n\nCreated Process Initial Order\n");
    PoolSort_Print(&kernel.pool);

    PoolSort_ByTime(&kernel.pool);
    printf("Sorted Process Order\n");
    PoolSort_Print(&kernel.pool);
    
    printf("Entering Kernel Loop:\n");
    Kernel_Loop(&kernel);
}

void ProcessSchedulledByPriorityOnly(void)
{
    kernel_t kernel;

    printf("Initializing Kernel\n");
    Kernel_Init(&kernel);

    printf("Creating Processes\n");
    CreateProcesses(&kernel.pool);

    printf("\n\nCreated Process Initial Order\n");
    PoolSort_Print(&kernel.pool);

    PoolSort_ByPriority(&kernel.pool);
    printf("Sorted Process Order\n");
    PoolSort_Print(&kernel.pool);
    
    printf("Entering Kernel Loop:\n");
    Kernel_Loop(&kernel);
}