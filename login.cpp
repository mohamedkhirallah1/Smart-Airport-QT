#include "login.h"
#include "ui_login.h"
#include "employe.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include "connection.h"
#include "arduino.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pb_login_clicked()
{
   QString email = ui->email_login->text();
    QString password = ui->password_login->text();
    QSqlQuery qry;
    if(qry.exec("select * from employe where email='"+email+"' and password='"+password+"'"))
    {
        int count=0;
        while(qry.next())
        {
            count++;
        }
        if(count==1)
        {
          QMessageBox::information(this, "Login", "Username and password is correct");
            //hide();
             ma = new MainWindow(this);
             ma->show();
        }

         else{
                     QMessageBox::warning(this,"Login", "Username and password is not correct");

        }

     }
}

