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
bool *comenzar;
int *turno;
int *ganador;

void *servidor(void*);
void *J1(void*);
void *J2(void*);

int obtenerganador();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    //Configurar memoria
    const int SIZE = sizeof(memoria);
    char name[100]="memoria";
    int shm_fd;
    void *ptr;

    shm_fd = shm_open(name, O_RDONLY, 0666);
    if(shm_fd!=-1)
    {
        shm_unlink(name);
    }
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0777);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(nullptr, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);


    mem = static_cast<memoria*>(ptr);
    w.mem = mem;



    //Configurar hilos
    pthread_t tidJ1,tidJ2, tidservidor;
    pthread_attr_t attrJ1,attrJ2, attrservidor;


    pthread_attr_init(&attrJ1);
    pthread_attr_init(&attrJ2);
    pthread_attr_init(&attrservidor);
    pthread_create(&tidJ1, &attrJ1, J1, nullptr);
    pthread_create(&tidJ2, &attrJ2, J2, nullptr);
    pthread_create(&tidservidor, &attrservidor, servidor, nullptr);

    //configurar variables
    continuar = &w.continuar;
    comenzar = &w.comenzar;
    turno = &w.turno;
    ganador = &w.ganador;

    w.show();

    return a.exec();
}
void *servidor(void*)
{

    while (mem->jugador1 == false) {}
    *continuar = true;
    while (mem->jugador2 == false) {}
    *continuar = true;

    *turno = 1 + rand() % (2 +1 - 1);
    for (int y = 0;y<6;y++)
    {
        for (int x = 0;x<7;x++)
        {
            mem->tablero[y][x] = '-';
        }
    }

}
void *J1(void*)
{
    while (mem->jugador1 == false) {}
    int idJ1;
    char fifoJ1[50] = "/tmp/jugador1";
    mkfifo(fifoJ1, 0666);

    char enviar[50];
    char recibir[50];

    sprintf(enviar,"%s","TU_TURNO");
    *ganador = 0;
    while (*comenzar == false) {}
    while(true)
    {
        if(*turno == 1)
        {
            if(*ganador != 0)
            {
                if(*ganador == 1)
                {
                    sprintf(enviar,"%s","GANAS");
                    idJ1 = open(fifoJ1, O_WRONLY);
                    write(idJ1, enviar, strlen(enviar)+1);
                    close(idJ1);
                }
                else
                {
                    sprintf(enviar,"%s","PIERDES");
                    idJ1 = open(fifoJ1, O_WRONLY);
                    write(idJ1, enviar, strlen(enviar)+1);
                    close(idJ1);
                }
            }
            else
            {
                idJ1 = open(fifoJ1, O_WRONLY);
                write(idJ1, enviar, strlen(enviar)+1);
                close(idJ1);

                idJ1 = open(fifoJ1, O_RDONLY);
                read(idJ1, recibir, 50);
                int columna;
                sscanf(recibir,"%d",&columna);
                close(idJ1);


                for (int x = 5;x>=0;x--)
                {
                    if(mem->tablero[x][columna] == '-')
                    {
                        mem->tablero[x][columna] = 'x';
                        break;
                    }
                }

                *ganador = obtenerganador();


                mem->actualizar = true;
                usleep(50*1000);
                while(mem->actualizar == true){}

                *turno = 2;
                usleep(50*1000);
                sprintf(recibir,"%s","");
            }

        }
        else
        {
            if(*ganador != 0)
            {
                if(*ganador == 1)
                {
                    sprintf(enviar,"%s","GANAS");
                    idJ1 = open(fifoJ1, O_WRONLY);
                    write(idJ1, enviar, strlen(enviar)+1);
                    close(idJ1);
                }
                else
                {
                    sprintf(enviar,"%s","PIERDES");
                    idJ1 = open(fifoJ1, O_WRONLY);
                    write(idJ1, enviar, strlen(enviar)+1);
                    close(idJ1);
                }
            }
        }
    }



}
void *J2(void*)
{
    while (mem->jugador2 == false) {}
    int idJ2;
    char fifoJ2[50] = "/tmp/jugador2";
    mkfifo(fifoJ2, 0666);

    char enviar[50];
    char recibir[50];

    sprintf(enviar,"%s","TU_TURNO");
    *ganador = 0;
    while (*comenzar == false) {}
    while(true)
    {
        if(*turno == 2)
        {
            if(*ganador != 0)
            {
                if(*ganador == 1)
                {
                    sprintf(enviar,"%s","GANAS");
                    idJ2 = open(fifoJ2, O_WRONLY);
                    write(idJ2, enviar, strlen(enviar)+1);
                    close(idJ2);
                }
                else
                {
                    sprintf(enviar,"%s","PIERDES");
                    idJ2 = open(fifoJ2, O_WRONLY);
                    write(idJ2, enviar, strlen(enviar)+1);
                    close(idJ2);
                }
            }
            else
            {
                idJ2 = open(fifoJ2, O_WRONLY);
                write(idJ2, enviar, strlen(enviar)+1);
                close(idJ2);

                idJ2 = open(fifoJ2, O_RDONLY);
                read(idJ2, recibir, 50);
                int columna;
                sscanf(recibir,"%d",&columna);
                close(idJ2);


                for (int x = 5;x>=0;x--)
                {
                    if(mem->tablero[x][columna] == '-')
                    {
                        mem->tablero[x][columna] = 'o';
                        break;
                    }
                }

                *ganador = obtenerganador();

                mem->actualizar = true;
                usleep(50*1000);
                while(mem->actualizar == true){}

                *turno = 1;
                usleep(50*1000);
                sprintf(recibir,"%s","");
            }

        }
        else
        {
            if(*ganador != 0)
            {
                if(*ganador == 1)
                {
                    sprintf(enviar,"%s","PIERDES");
                    idJ2 = open(fifoJ2, O_WRONLY);
                    write(idJ2, enviar, strlen(enviar)+1);
                    close(idJ2);
                }
                else
                {
                    sprintf(enviar,"%s","GANAS");
                    idJ2 = open(fifoJ2, O_WRONLY);
                    write(idJ2, enviar, strlen(enviar)+1);
                    close(idJ2);
                }
            }
        }
    }
}

int obtenerganador()
{
    int direccionesx[8] = {-1,0,1,-1,1,-1,0,1};
    int direccionesy[8] = {-1,-1,-1,0,0,1,1,1};
    int ganador = 0;
    for (int y = 0;y<6;y++)
    {
        for (int x = 0;x<7;x++)
        {
            if(mem->tablero[y][x] != '-')
            {
                if(mem->tablero[y][x] == 'x')
                {
                    ganador++;
                    for(int a = 0;a <8;a++)
                    {
                        for (int i = 1;i<=3;i++)
                        {


                            if(y+(direccionesy[a]*i) >= 0 && y+(direccionesy[a]*i) < 6 && x+(direccionesx[a]*i) >= 0 && x+(direccionesx[a]*i) < 7)
                            {
                                if(mem->tablero[y+(direccionesy[a]*i)][x+(direccionesx[a]*i)] == 'x')
                                {
                                    ganador++;
                                }


                            }

                        }
                        if(ganador==4)
                        {
                            return 1;
                        }
                        else
                        {
                            ganador = 1;
                        }


                    }

                }
                else
                {
                    ganador++;
                    for(int a = 0;a <8;a++)
                    {
                        for (int i = 1;i<=3;i++)
                        {


                            if(y+(direccionesy[a]*i) >= 0 && y+(direccionesy[a]*i) < 6 && x+(direccionesx[a]*i) >= 0 && x+(direccionesx[a]*i) < 7)
                            {
                                if(mem->tablero[y+(direccionesy[a]*i)][x+(direccionesx[a]*i)] == 'o')
                                {
                                    ganador++;
                                }


                            }

                        }
                        if(ganador==4)
                        {
                            return 2;
                        }
                        else
                        {
                            ganador = 1;
                        }


                    }
                }
            }
            if(ganador==4)
            {
                break;
            }
            else
            {
                ganador = 0;
            }
        }

    }
    return 0;
}
