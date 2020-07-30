#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <termios.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "qdebug.h"

struct memoria
{
    bool jugador1;
    bool jugador2;
    bool actualizar;
    char tablero[6][7];
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<QLabel *> tablero_fichas;
    QList<QLabel *> final;
    memoria *mem;

    bool continuar;
    int jugador;
    int habilitarturno;
    int columna;
    bool fin;
    int ganador;

public slots:
    void factualizar();
private slots:
    void on_Btn_c_1_clicked();

    void on_Btn_c_2_clicked();

    void on_Btn_c_3_clicked();

    void on_Btn_c_4_clicked();

    void on_Btn_c_5_clicked();

    void on_Btn_c_6_clicked();

    void on_Btn_c_7_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
