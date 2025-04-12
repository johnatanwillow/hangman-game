#include "exe02.h"
#include <stdio.h>

void tempo_horas(int segundos)
{
    int horas = (int) segundos / 3600;
    int resto_horas = (int) segundos % 3600;
    int minutos = (int) resto_horas / 60;
    int minutos_resto = (int) resto_horas % 60;
    int segundos_restantes = (int) segundos % 60;
    printf("A corrida durou %d:%d:%d horas\n", horas, minutos, segundos_restantes);
}