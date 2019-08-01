#include "ventanaconfirmar.h"
#include "ui_ventanaconfirmar.h"
#include <stdlib.h>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
using namespace std;

ventanaConfirmar::ventanaConfirmar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaConfirmar)
{
    ui->setupUi(this);
}

ventanaConfirmar::~ventanaConfirmar()
{
    delete ui;
}

void ventanaConfirmar::on_buttonBox_rejected()
{
    reject();
}

void ventanaConfirmar::on_buttonBox_accepted()
{
    QSqlQuery query;
    query.exec("DROP DATABASE qt;");
    query.exec("CREATE DATABASE qt;");
    system("DEL usuario");
    QMessageBox::information(this, "Información", "Operación realizada correctamente. Usuario eliminado");
    reject();
}
