#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //timers
    QTimer *actualizar = new QTimer(this);
    connect(actualizar,SIGNAL(timeout()),this,SLOT(factualizar()));
    actualizar->start(100);

    tablero_fichas << ui->ficha_0_0;
    tablero_fichas << ui->ficha_0_1;
    tablero_fichas << ui->ficha_0_2;
    tablero_fichas << ui->ficha_0_3;
    tablero_fichas << ui->ficha_0_4;
    tablero_fichas << ui->ficha_0_5;
    tablero_fichas << ui->ficha_0_6;
    tablero_fichas << ui->ficha_1_0;
    tablero_fichas << ui->ficha_1_1;
    tablero_fichas << ui->ficha_1_2;
    tablero_fichas << ui->ficha_1_3;
    tablero_fichas << ui->ficha_1_4;
    tablero_fichas << ui->ficha_1_5;
    tablero_fichas << ui->ficha_1_6;
    tablero_fichas << ui->ficha_2_0;
    tablero_fichas << ui->ficha_2_1;
    tablero_fichas << ui->ficha_2_2;
    tablero_fichas << ui->ficha_2_3;
    tablero_fichas << ui->ficha_2_4;
    tablero_fichas << ui->ficha_2_5;
    tablero_fichas << ui->ficha_2_6;
    tablero_fichas << ui->ficha_3_0;
    tablero_fichas << ui->ficha_3_1;
    tablero_fichas << ui->ficha_3_2;
    tablero_fichas << ui->ficha_3_3;
    tablero_fichas << ui->ficha_3_4;
    tablero_fichas << ui->ficha_3_5;
    tablero_fichas << ui->ficha_3_6;
    tablero_fichas << ui->ficha_4_0;
    tablero_fichas << ui->ficha_4_1;
    tablero_fichas << ui->ficha_4_2;
    tablero_fichas << ui->ficha_4_3;
    tablero_fichas << ui->ficha_4_4;
    tablero_fichas << ui->ficha_4_5;
    tablero_fichas << ui->ficha_4_6;
    tablero_fichas << ui->ficha_5_0;
    tablero_fichas << ui->ficha_5_1;
    tablero_fichas << ui->ficha_5_2;
    tablero_fichas << ui->ficha_5_3;
    tablero_fichas << ui->ficha_5_4;
    tablero_fichas << ui->ficha_5_5;
    tablero_fichas << ui->ficha_5_6;



    mem = new memoria();

    //memoria
    mem->jugador1 = false;
    mem->jugador2 = false;
    mem->actualizar = false;

    for (int y = 0;y<6;y++)
    {
        for (int x = 0;x<7;x++)
        {
            mem->tablero[y][x] = '-';
        }
    }

    //configurar variables
    continuar = false;
    comenzar = false;
    ganador = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::factualizar()
{
    if(mem->actualizar == true)
    {
        for (int y = 0;y<6;y++)
        {
            for (int x = 0;x<7;x++)
            {
                if(mem->tablero[y][x] == 'x')
                {
                    QPixmap ficha (":/imagenes/J1.png");
                    tablero_fichas.at(x + (y*7))->setPixmap(ficha);
                }
                else if(mem->tablero[y][x] == 'o')
                {
                    QPixmap ficha (":/imagenes/J2.png");
                    tablero_fichas.at(x + (y*7))->setPixmap(ficha);
                }
            }
        }
        mem->jugador1 = false;
        mem->jugador2 = false;
        int salir = 0;
        while ((mem->jugador1 == false || mem->jugador2 == false) && salir < 50000000) {salir++;}
        mem->actualizar = false;
    }
    if(continuar == true)
    {
        if(mem->jugador1 == true && mem->jugador2 == false)
        {
            ui->Jugador_2->setText("Jugador 1");
            ui->conectado_2->setText("Conectado");
        }
        if(mem->jugador1 == true && mem->jugador2 == true)
        {
            ui->Jugador_2->setText("Jugadores");
            ui->conectado_2->setText("Conectados");

            ui->texto_j_a->setText("Todo");
            ui->texto_j_b->setText("Listo");

            ui->Btn_comenzar->setEnabled(true);
            ui->Btn_reiniciar->setEnabled(true);
        }
        continuar = false;
    }
    if(ganador !=0)
    {
        ui->Jugador_2->setText("El ganador es");
        if(ganador == 1)
        {
            ui->conectado_2->setText("el jugador 1");
        }
        else
        {
            ui->conectado_2->setText("el jugador 2");
        }
    }

}

void MainWindow::on_Btn_comenzar_clicked()
{
    comenzar = true;
    mem->jugador1 = false;
    mem->jugador2 = false;
    ui->Jugador_2->setText("Partida en");
    ui->conectado_2->setText("Curso...");
}
