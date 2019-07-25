#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCryptographicHash>
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
    /* Variables con el hash */ QString userHash, passHash; /*--------*/
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
    //Hasheamos userStr // El usuario recogido
    userHash = QString::fromStdString(userStr);
    userHash = QString(QCryptographicHash::hash(userHash.toUtf8(), QCryptographicHash::Md5).toHex());

    if(temp!=userHash.toStdString())
    {
        ui->result->setText("El usuario no es correcto");
        return;
    }
    while(!archivo2.eof())
    {
        getline(archivo2, temp2);
    }
    //Hasheamos passStr // La contraseña recogida
    passHash = QString::fromStdString(passStr);
    passHash = QString(QCryptographicHash::hash(passHash.toUtf8(), QCryptographicHash::Md5).toHex());

    if(temp2!=passHash.toStdString())
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
