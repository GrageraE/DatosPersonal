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
#include <fstream>

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
    recogerDatos();
}

struct{
    int id[100];
    QString nombre[100];
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
    QSqlQuery query;
    //Esto de aquí es un poco largo:
    if(!query.exec("INSERT INTO person" + QString::number(dato.count) + "(id, nombre) VALUES (" + id + ",'" + nombre + "');"))
    {
        QMessageBox::information(this, "Error", query.lastError().text());
        ui->result->setText("Ha habido un error al insertar los datos");
        return;
    }
    //Guardar el count
    std::ofstream cuenta;
    cuenta.open("usuario/cuenta.txt", std::ios::out);
    cuenta <<dato.count;
    cuenta.close();
    return;
}

void ventanaAdmin::on_pushButton_2_clicked()
{
    int datoTabla = ui->tableWidget->currentRow(); //La fila clickeada
    ui->tableWidget->removeRow(datoTabla);
    QSqlQuery query;
    if(!query.exec("DROP TABLE person" + QString::number(datoTabla) + ";"))
    {
        QMessageBox::information(this, "Error", query.lastError().text());
        QMessageBox::information(this, "Información", "Puede que sea necesario activar el tool button.");
        return;
    }
    std::ofstream cuenta;
    cuenta.open("usuario/cuenta.txt", std::ios::out);
    dato.count--;
    cuenta <<dato.count;
    cuenta.close();
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
    //PASO 1 - Extraer la cuenta
    std::ifstream cuenta;
    std::string temp;
    cuenta.open("usuario/cuenta.txt", std::ios::in);
    if(cuenta.fail())
    {
        QMessageBox::information(this, "Información", "No tienes una tabla creada ni registros guardados. Abortando...");
        return;
    }
    while (!cuenta.eof()) {
        std::getline(cuenta, temp);
    }
    dato.count = std::stoi(temp);
    cuenta.close();
    //PASO 2 - Seleccionar de las tablas
    QSqlQuery query;
    int i = 0;
    while(i<=dato.count)
    {
        query.exec("SELECT * FROM person" + QString::number(i) + ";");
        while(query.next())
        {
            dato.id[i] = query.value(0).toInt();
            dato.nombre[i] = query.value(1).toString();
        }
        i++;
    }
    //PASO 3 - Mostrarlo en la tabla (QTableWidget)
}

void ventanaAdmin::crearTabla(int count)
{
    ui->result->setText("Creando tabla");
    std::string comando = "CREATE TABLE person";
    comando = comando + std::to_string(count);
    comando = comando + "(id int, nombre varchar(100));";
    QSqlQuery query;
    if(!query.exec(QString::fromStdString(comando)))
    {
        QMessageBox::information(this, "Error", query.lastError().text());
        return;
    }
    ui->result->setText("La tabla se ha creado correctamente");
    return;
}

void ventanaAdmin::on_toolButton_clicked()
{
    std::ofstream cuenta;
    cuenta.open("usuario/cuenta.txt", std::ios::out);
    cuenta <<-1;
    cuenta.close();
    dato.count = -1;
}
