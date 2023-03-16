#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void ras(){
    printf("Le code fonctionne correctement !\n");
}

void waiting(int time){
    sleep(time);
    system("cls");system("clear");
}



void waiting(int time);

#endif
