#ifndef VENTANACONFIRMAR_H
#define VENTANACONFIRMAR_H

#include <QDialog>

namespace Ui {
class ventanaConfirmar;
}

class ventanaConfirmar : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaConfirmar(QWidget *parent = nullptr);
    ~ventanaConfirmar();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::ventanaConfirmar *ui;
};

#endif // VENTANACONFIRMAR_H
