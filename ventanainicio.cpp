#include "ventanainicio.h"
#include "ui_ventanainicio.h"
#include <string>
#include <fstream>
using namespace std;

ventanaInicio::ventanaInicio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaInicio)
{
    ui->setupUi(this);
}

ventanaInicio::~ventanaInicio()
{
    delete ui;
}

void ventanaInicio::on_pushButton_clicked()
{
    QString usuario, contra, contra2, clave;
    int claveInt;
    const int claveComp = 525246; //Importante
    usuario = ui->usuario->text();
    contra = ui->contra1->text();
    contra2 = ui->contra2->text();
    if(contra!=contra2)
    {
        return;
    }
    clave = ui->clave->text();
    claveInt = clave.toInt();
    if(claveInt!=claveComp)
    {
        return;
    }
    //Creamos los archivos
    system("MKDIR usuario");
    ofstream archivo, archivo2;
    archivo.open("usuario/user.txt", ios::out);
    archivo2.open("usuario/pass.txt", ios::out);
    archivo <<usuario.toStdString();
    archivo2 <<contra.toStdString();
    archivo.close();
    archivo2.close();
    return;
}
