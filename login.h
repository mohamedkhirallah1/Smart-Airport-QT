#ifndef LOGIN_H
#define LOGIN_H
#include "employe.h"
#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QMainWindow>
#include "arduino.h"
#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
private slots:
    void on_pb_login_clicked();

private:
    Ui::login *ui;
    MainWindow *ma;
    QSqlDatabase mydb;
    Arduino A;
    QByteArray data;
};

#endif // LOGIN_H
