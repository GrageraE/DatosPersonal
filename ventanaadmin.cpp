#include "ventanaadmin.h"
#include "ui_ventanaadmin.h"
#include "ventanaconfirmar.h"

ventanaAdmin::ventanaAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaAdmin)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2); //Configurar las columnas
    QStringList columnas;
    columnas <<"Nombre" <<"ID";
    ui->tableWidget->setHorizontalHeaderLabels(columnas);
}

ventanaAdmin::~ventanaAdmin()
{
    delete ui;
}

void ventanaAdmin::on_pushButton_3_clicked()
{
    exit(0);
}

void ventanaAdmin::on_pushButton_clicked() //Añadir
{
    //Recogemos los datos
    QString nombre = ui->nombre->text();
    QString id = ui->id->text();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount()); //Crear fila
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, NOMBRE, //Añadir datos en la fila
                             new QTableWidgetItem(nombre));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ID,
                             new QTableWidgetItem(id));

}

void ventanaAdmin::on_pushButton_2_clicked()
{
    int dato = ui->tableWidget->currentRow(); //La fila clickeada
    ui->tableWidget->removeRow(dato);
}

void ventanaAdmin::on_pushButton_4_clicked()
{
    ventanaConfirmar ventanaconfirmar;
    ventanaconfirmar.setModal(true);
    ventanaconfirmar.exec();
    return;
}
