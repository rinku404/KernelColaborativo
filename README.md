# Kernel Colaborativo

Esse projeto foi feito como trabalho da disciplina de Sistemas Embarcados.

A proposta inicial era a criação de uma aplicação capaz de gerenciar processos levando em conta o tempo de execução e a prioridade de cada um deles.
Como um desafio pessoal, buscando aprendizado extra, foi optado por utilizar uma abordagem de lista dinâmica encadeada para gerenciar o pool de processos.
Dessa forma, não existe limitação para a criação e remoção de processos durante a execução, além de otimizar o gerenciamento de memória, uma vez que processos finalizados tem o bloco de memória que possuiam desalocados.

Como é um trabalho puramente para estudo, não foi utilizado nenuma biblioteca de temporização.
No entanto foi desenvolvido um sistema de "Clock" onde o "pulso" é o usuário pressionando enter.