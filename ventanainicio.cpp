#include "ventanainicio.h"
#include "ui_ventanainicio.h"
#include <QCryptographicHash>
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
    QString userHash, passHash;  //Esto se hashea
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
    //Hasheamos en MD5
    userHash = QString(QCryptographicHash::hash(usuario.toUtf8(), QCryptographicHash::Md5).toHex());
    passHash = QString(QCryptographicHash::hash(contra.toUtf8(), QCryptographicHash::Md5).toHex());
    //Creamos los archivos
    system("MKDIR usuario");
    ofstream archivo, archivo2;
    archivo.open("usuario/user.txt", ios::out);
    archivo2.open("usuario/pass.txt", ios::out);
    archivo <<userHash.toStdString();
    archivo2 <<passHash.toStdString();
    archivo.close();
    archivo2.close();
    return;
}
