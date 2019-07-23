#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
//Mis librerias
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
//Ventanas
#include "ventanainicio.h"
#include "ventanaadmin.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    ventanaInicio ventanainicio;
    ventanainicio.setModal(true);
    ventanainicio.exec();
    return;
}

void MainWindow::on_pushButton_clicked()
{
    QString user, pass;
    string userStr, passStr, temp, temp2;
    user = ui->usuario->text();
    pass = ui->contra->text();
    userStr = user.toStdString();
    passStr = pass.toStdString();
    ifstream archivo, archivo2;
    archivo.open("usuario/user.txt", ios::in);
    archivo2.open("usuario/pass.txt", ios::in);
    if(archivo.fail()||archivo2.fail())
    {
        ui->result->setText("Por favor, inicialize su usario para comenzar");
        return;
    }
    while(!archivo.eof())
    {
        getline(archivo, temp);
    }
    if(temp!=userStr)
    {
        ui->result->setText("El usuario no es correcto");
        return;
    }
    while(!archivo2.eof())
    {
        getline(archivo2, temp2);
    }
    if(temp2!=passStr)
    {
        ui->result->setText("La contraseña no es correcta");
        return;
    }
    ui->result->setText("Identificación correcta");
    //Invocamos la ventana
    ventanaAdmin ventanaadmin;
    ventanaadmin.setModal(true);
    ventanaadmin.exec();
    return;
}
