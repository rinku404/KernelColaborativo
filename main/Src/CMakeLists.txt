cmake_minimum_required(VERSION 3.16)

include_directories(${CMAKE_SOURCE_DIR}/main/Inc)

add_executable( kernel_tempo_prioridade
                main.c process_pool.c
                process.c test_functions.c
                pool_sorting.c
                kernel.c
                )