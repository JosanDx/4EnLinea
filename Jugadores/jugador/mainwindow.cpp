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

    final << ui->fin1;
    final << ui->fin2;
    final << ui->fin3;



    mem = new memoria();


    //configurar variables
    continuar = false;
    habilitarturno = 0;
    fin = false;
    ganador = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::factualizar()
{
    if(mem->actualizar == true && (mem->jugador1 == false || mem->jugador2 == false))
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
        if(jugador == 1)
        {
            mem->jugador1 = true;
        }
        else if (jugador == 2)
        {
            mem->jugador2 = true;
        }
    }

    if(continuar == true)
    {
        if(mem->jugador1 == true && mem->jugador2 == false)
        {
            ui->texto_j_a_2->setText("Eres el");
            ui->texto_j_b_2->setText("Jugador 1");
            ui->texto_j_b_3->setText("Tu ficha");
            QPixmap ficha (":/imagenes/J1.png");
            ui->ficha_actual->setPixmap(ficha);

        }
        else if (mem->jugador1 == true && mem->jugador2 == true)
        {
            ui->texto_j_a_2->setText("Eres el");
            ui->texto_j_b_2->setText("Jugador 2");
            ui->texto_j_b_3->setText("Tu ficha");
            QPixmap ficha (":/imagenes/J2.png");
            ui->ficha_actual->setPixmap(ficha);

        }
        continuar = false;
    }

    if(habilitarturno == 1)
    {
        int c1 = 0;
        int c2 = 0;
        int c3 = 0;
        int c4 = 0;
        int c5 = 0;
        int c6 = 0;
        int c7 = 0;

        for (int y = 0;y<6;y++)
        {
            for (int x = 0;x<7;x++)
            {
                if(mem->tablero[y][x] == 'x')
                {
                    if(x == 0)
                    {
                        c1++;
                    }
                    else if(x == 1)
                    {
                        c2++;
                    }
                    else if(x == 2)
                    {
                        c3++;
                    }
                    else if(x == 3)
                    {
                        c4++;
                    }
                    else if(x == 4)
                    {
                        c5++;
                    }
                    else if(x == 5)
                    {
                        c6++;
                    }
                    else if(x == 6)
                    {
                        c7++;
                    }
                }
                else if(mem->tablero[y][x] == 'o')
                {
                    if(x == 0)
                    {
                        c1++;
                    }
                    else if(x == 1)
                    {
                        c2++;
                    }
                    else if(x == 2)
                    {
                        c3++;
                    }
                    else if(x == 3)
                    {
                        c4++;
                    }
                    else if(x == 4)
                    {
                        c5++;
                    }
                    else if(x == 5)
                    {
                        c6++;
                    }
                    else if(x == 6)
                    {
                        c7++;
                    }
                }
            }
        }
        if(c1 < 6)
        {
            ui->Btn_c_1->setEnabled(true);
        }
        if(c2 < 6)
        {
            ui->Btn_c_2->setEnabled(true);
        }
        if(c3 < 6)
        {
            ui->Btn_c_3->setEnabled(true);
        }
        if(c4 < 6)
        {
            ui->Btn_c_4->setEnabled(true);
        }
        if(c5 < 6)
        {
            ui->Btn_c_5->setEnabled(true);
        }
        if(c6 < 6)
        {
            ui->Btn_c_6->setEnabled(true);
        }
        if(c7 < 6)
        {
            ui->Btn_c_7->setEnabled(true);
        }
        habilitarturno = 2;
    }
    if(fin == true)
    {
        QPixmap ficha1 (":/imagenes/cuadroblanco.png");
        final.at(0)->setPixmap(ficha1);
        if(ganador == jugador)
        {

            final.at(1)->setText("GANASTE");
            QPixmap ficha2(":/imagenes/gano.jpg");
            final.at(2)->setPixmap(ficha2);
        }
        else
        {
            final.at(1)->setText("PERDISTE");
            QPixmap ficha2(":/imagenes/perdio.jpeg");
            final.at(2)->setPixmap(ficha2);
        }
    }
}

void MainWindow::on_Btn_c_1_clicked()
{
    columna = 0;
    ui->Btn_c_1->setEnabled(false);
    ui->Btn_c_2->setEnabled(false);
    ui->Btn_c_3->setEnabled(false);
    ui->Btn_c_4->setEnabled(false);
    ui->Btn_c_5->setEnabled(false);
    ui->Btn_c_6->setEnabled(false);
    ui->Btn_c_7->setEnabled(false);
    habilitarturno = 0;
}

void MainWindow::on_Btn_c_2_clicked()
{
    columna = 1;
    ui->Btn_c_1->setEnabled(false);
    ui->Btn_c_2->setEnabled(false);
    ui->Btn_c_3->setEnabled(false);
    ui->Btn_c_4->setEnabled(false);
    ui->Btn_c_5->setEnabled(false);
    ui->Btn_c_6->setEnabled(false);
    ui->Btn_c_7->setEnabled(false);
    habilitarturno = 0;
}

void MainWindow::on_Btn_c_3_clicked()
{
    columna = 2;
    ui->Btn_c_1->setEnabled(false);
    ui->Btn_c_2->setEnabled(false);
    ui->Btn_c_3->setEnabled(false);
    ui->Btn_c_4->setEnabled(false);
    ui->Btn_c_5->setEnabled(false);
    ui->Btn_c_6->setEnabled(false);
    ui->Btn_c_7->setEnabled(false);
    habilitarturno = 0;
}

void MainWindow::on_Btn_c_4_clicked()
{
    columna = 3;
    ui->Btn_c_1->setEnabled(false);
    ui->Btn_c_2->setEnabled(false);
    ui->Btn_c_3->setEnabled(false);
    ui->Btn_c_4->setEnabled(false);
    ui->Btn_c_5->setEnabled(false);
    ui->Btn_c_6->setEnabled(false);
    ui->Btn_c_7->setEnabled(false);
    habilitarturno = 0;
}

void MainWindow::on_Btn_c_5_clicked()
{
    columna = 4;
    ui->Btn_c_1->setEnabled(false);
    ui->Btn_c_2->setEnabled(false);
    ui->Btn_c_3->setEnabled(false);
    ui->Btn_c_4->setEnabled(false);
    ui->Btn_c_5->setEnabled(false);
    ui->Btn_c_6->setEnabled(false);
    ui->Btn_c_7->setEnabled(false);
    habilitarturno = 0;
}

void MainWindow::on_Btn_c_6_clicked()
{
    columna = 5;
    ui->Btn_c_1->setEnabled(false);
    ui->Btn_c_2->setEnabled(false);
    ui->Btn_c_3->setEnabled(false);
    ui->Btn_c_4->setEnabled(false);
    ui->Btn_c_5->setEnabled(false);
    ui->Btn_c_6->setEnabled(false);
    ui->Btn_c_7->setEnabled(false);
    habilitarturno = 0;
}

void MainWindow::on_Btn_c_7_clicked()
{
    columna = 6;
    ui->Btn_c_1->setEnabled(false);
    ui->Btn_c_2->setEnabled(false);
    ui->Btn_c_3->setEnabled(false);
    ui->Btn_c_4->setEnabled(false);
    ui->Btn_c_5->setEnabled(false);
    ui->Btn_c_6->setEnabled(false);
    ui->Btn_c_7->setEnabled(false);
    habilitarturno = 0;
}
