#include "process.h"
#include "test_functions.h"
#include "kernel.h"
#include "process_pool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Kernel Coração de mãe, sempre cabe mais um processo

void TestProcessPoolFunctions(void);

int main(void)
{
    TestProcessPoolFunctions();



    //Kernel_Loop();

    return 0;
}

void TestProcessPoolFunctions(void)
{
        process_pool_t pool;

    Pool_Init(&pool);

    process_t proc;
    char proc_name[] = "A Proc";

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, 0);

    proc_name[0] = 'B';

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, 0);

    proc_name[0] = 'C';

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, 0);

    proc_name[0] = 'D';

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, pool.current_size);


    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    proc_name[0] = 'E';

    Process_SetName(&proc, proc_name, sizeof(proc));
    Pool_AddEllementByIndex(&pool, &proc, 4);    

    printf("-----------\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    Pool_SwapNodeOrder(&pool, 0, 2);

    printf("----Swapped 0 and 4\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }


    Pool_RemoveEllementByIndex(&pool, 0);

    printf("-----Remove 0\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    Pool_RemoveEllementByIndex(&pool, pool.current_size);

    printf("-----Remove last\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    Pool_RemoveEllementByIndex(&pool, 1);

    printf("-----Remove 1\n");

    for(int i = 0; i < pool.current_size; i++)
    {
        Pool_GetEllementByIndex(&pool, &proc, i);
        printf("%s\n", proc.NomeProcesso);
    }

    Pool_Clear(&pool);
}