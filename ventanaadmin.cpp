#include "ventanaadmin.h"
#include "ui_ventanaadmin.h"
#include "ventanaconfirmar.h"
//Sqlite
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <string>

ventanaAdmin::ventanaAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaAdmin)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2); //Configurar las columnas
    QStringList columnas;
    columnas <<"Nombre" <<"ID";
    ui->tableWidget->setHorizontalHeaderLabels(columnas);

    //Conectar a Sql
    conectarSql();
    //recogerDatos();
}

struct{
    int id[10];
    QString nombre[10];
    int count = -1;
}dato;

ventanaAdmin::~ventanaAdmin()
{
    delete ui;
}

void ventanaAdmin::on_pushButton_3_clicked()
{
    reject();
}

void ventanaAdmin::on_pushButton_clicked() //Añadir
{
    //Recogemos los datos - PASO 1
    QSqlDatabase db;
    QString nombre = ui->nombre->text();
    QString id = ui->id->text();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount()); //Crear fila
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, NOMBRE, //Añadir datos en la fila
                             new QTableWidgetItem(nombre));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ID,
                             new QTableWidgetItem(id));
    dato.count++; //Aumentamos la cuenta
    if(!db.tables().contains("person" + QString::number(dato.count)))
    {
        crearTabla(dato.count); //Creamos tabla; si no existe - PASO 2
    }
    //Guardar los datos - PASO 3
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

void ventanaAdmin::conectarSql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("qt");
    if(db.open())
        ui->result->setText("Se ha conectado a MySql");
    else {
        ui->result->setText("Ha habido un problema");
        QMessageBox::information(this, "Error", db.lastError().text());
    }
    return;
}

void ventanaAdmin::recogerDatos() //Del servidor
{
    return;
}

void ventanaAdmin::crearTabla(int count)
{
    ui->result->setText("Creando tabla");
    std::string comando = "CREATE TABLE person";
    comando = comando + std::to_string(count);
    comando = comando + "(id int, nombre varchar(100));";
    QMessageBox::information(this, "Info", QString::fromStdString(comando));
    QSqlQuery query;
    if(!query.exec(QString::fromStdString(comando)))
    {
        QMessageBox::information(this, "Error", query.lastError().text());
        return;
    }
    ui->result->setText("La tabla se ha creado correctamente");
    return;
}
