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
    memoria *mem;

    bool continuar;
    bool comenzar;
    int turno;
    int ganador;

public slots:
    void factualizar();
private slots:
    void on_Btn_comenzar_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
