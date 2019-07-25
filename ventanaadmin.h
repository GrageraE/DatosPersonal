#ifndef VENTANAADMIN_H
#define VENTANAADMIN_H

#include <QDialog>

namespace Ui {
class ventanaAdmin;
}

class ventanaAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaAdmin(QWidget *parent = nullptr);
    ~ventanaAdmin();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ventanaAdmin *ui;

    enum columna{  //Alias de las columnas (simbólico // No usar como label)
        NOMBRE, ID
    };
};

#endif // VENTANAADMIN_H
