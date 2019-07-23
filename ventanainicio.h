#ifndef VENTANAINICIO_H
#define VENTANAINICIO_H

#include <QDialog>

namespace Ui {
class ventanaInicio;
}

class ventanaInicio : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaInicio(QWidget *parent = nullptr);
    ~ventanaInicio();

private slots:
    //void on_toolButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::ventanaInicio *ui;
};

#endif // VENTANAINICIO_H
