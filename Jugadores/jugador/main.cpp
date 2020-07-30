#include "mainwindow.h"
#include <QApplication>

#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <termios.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <qdebug.h>
#include <time.h>

memoria *mem;
bool *continuar;
int *jugador;
int *habilitarturno;
int *columna;
bool *fin;
int *ganador;

void *Jugadores(void*);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //Configurar memoria
    const int SIZE = sizeof(memoria);
    char name[100]="memoria";
    int shm_fd;
    void *ptr;


    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0777);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(nullptr, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);


    mem = static_cast<memoria*>(ptr);
    w.mem = mem;

    //configurar variables
    continuar = &w.continuar;
    jugador = &w.jugador;
    habilitarturno = &w.habilitarturno;
    columna = &w.columna;
    fin = &w.fin;
    ganador = &w.ganador;

    if(mem->jugador1 == false && mem->jugador2 == false)
    {
        mem->jugador1 = true;
        *continuar = true;
        *jugador = 1;
    }
    else if(mem->jugador1 == true && mem->jugador2 == false)
    {
        mem->jugador2 = true;
        *continuar = true;
        *jugador = 2;
    }

    pthread_t tidJugadores;
    pthread_attr_t attrJugadores;


    pthread_attr_init(&attrJugadores);
    pthread_create(&tidJugadores, &attrJugadores, Jugadores, nullptr);


    w.show();

    return a.exec();
}

void *Jugadores(void*)
{

    if(*jugador == 1)
    {
        int idJ1;
        char fifoJ1[50] = "/tmp/jugador1";
        mkfifo(fifoJ1, 0666);

        char enviar[50];
        char recibir[50];
        *fin = false;
        while (*fin == false)
        {
            idJ1 = open(fifoJ1, O_RDONLY);
            read(idJ1, recibir, 50);

            if(strcmp(recibir,"TU_TURNO") == 0)
            {
                close(idJ1);
                *habilitarturno = 1;
                while (*habilitarturno != 0) {}
                sprintf(enviar,"%d",*columna);
                idJ1 = open(fifoJ1, O_WRONLY);
                write(idJ1,enviar,strlen(enviar)+1);
                close(idJ1);

                sprintf(recibir,"%s","");


            }
            else if(strcmp(recibir,"GANAS") == 0)
            {
                *ganador = 1;
                *fin = true;
            }
            else if(strcmp(recibir,"PIERDES") == 0)
            {
                *ganador = 2;
                *fin = true;
            }
        }


    }
    else
    {
        int idJ2;
        char fifoJ2[50] = "/tmp/jugador2";
        mkfifo(fifoJ2, 0666);

        char enviar[50];
        char recibir[50];
        *fin = false;
        while (*fin == false)
        {
            idJ2 = open(fifoJ2, O_RDONLY);
            read(idJ2, recibir, 50);
            if(strcmp(recibir,"TU_TURNO") == 0)
            {
                close(idJ2);
                *habilitarturno = 1;
                while (*habilitarturno != 0) {}
                sprintf(enviar,"%d",*columna);
                idJ2 = open(fifoJ2, O_WRONLY);
                write(idJ2,enviar,strlen(enviar)+1);
                close(idJ2);

                sprintf(recibir,"%s","");


            }
            else if(strcmp(recibir,"GANAS") == 0)
            {
                *ganador = 2;
                *fin = true;
            }
            else if(strcmp(recibir,"PIERDES") == 0)
            {
                *ganador = 1;
                *fin = true;
            }
        }

    }
}
