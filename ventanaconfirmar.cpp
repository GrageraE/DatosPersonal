#include "ventanaconfirmar.h"
#include "ui_ventanaconfirmar.h"
#include <stdlib.h>
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
    system("DEL usuario");
    system("RD usuario");
}
