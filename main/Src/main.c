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
void ProcessManagedByTime(void);

int main(void)
{
    //TestProcessPoolFunctions();
    ProcessManagedByTime();

    //Kernel_Loop();

    return 0;
}


void ProcessManagedByTime(void)
{
    kernel_t kernel;

    Kernel_Init(&kernel);

    CreateProcesses(&kernel.pool);
    PoolSort_ByTime(&kernel.pool);

    //printf("pool size: %d\n", kernel.pool.current_size);

    Kernel_Loop(&kernel);
}

void CreateProcesses(process_pool_t* pool)
{
    process_t process;

    printf("Creating Processes\n");

    {
        char name[] = "A Proc";

        Process_Init(&process);
        Process_SetName(&process, name, sizeof(name));
        process.TempoExec = 300;
        process.Prioridade = 1;
        process.ExecutionFunction = PrintMessageA;
        process.process_execution_class = REPEAT;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    {
        char name[] = "B Proc";

        Process_Init(&process);
        Process_SetName(&process, name, sizeof(name));
        process.TempoExec = 200;
        process.Prioridade = 3;
        process.ExecutionFunction = PrintMessageB;
        process.process_execution_class = ONCE;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    {
        char name[] = "C Proc";

        Process_Init(&process);
        Process_SetName(&process, name, sizeof(name));
        process.TempoExec = 100;
        process.Prioridade = 3;
        process.ExecutionFunction = PrintMessageC;
        process.process_execution_class = REPEAT;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    {
        char name[] = "D Proc";

        Process_Init(&process);
        Process_SetName(&process, name, sizeof(name));
        process.TempoExec = 50;
        process.Prioridade = 3;
        process.ExecutionFunction = PrintMessageD;
        process.process_execution_class = REPEAT;
    }

    Pool_AddEllementByIndex(pool, &process, pool->current_size);

    //printf("pool size: %d\n", pool->current_size);

    printf("Processes Created\n");
}

void TestProcessPoolFunctions(void)
{
    process_pool_t pool;

    Pool_Init(&pool);
    CreateProcesses(&pool);
       

    printf("-----------\n");
    PoolSort_Print(&pool);

    Pool_SwapNodeOrder(&pool, 0, 3);
    printf("----Swapped 0 and 3\n");
    PoolSort_Print(&pool);

    Pool_SwapNodeOrder(&pool, 2, 3);
    printf("----Swapped 2 and 3\n");
    PoolSort_Print(&pool);

    Pool_SwapNodeOrder(&pool, 3, 4);
    printf("----Swapped 3 and 4\n");
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