#include "pdf.h"
#include "ui_pdf.h"
#include"connection.h"
#include"mainwindow.h"
#include<QPdfWriter>
#include<QMessageBox>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>

pdf::pdf(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pdf)
{
    ui->setupUi(this);
}

pdf::~pdf()
{
    delete ui;
}

void pdf::on_pushButton_clicked() // pdf //
{
    QPdfWriter pdf("C:/Users/mohamed/Documents/waaaw/print");
    QPainter painter(&pdf);
    painter.setPen(Qt::blue);
    QString id = ui->line_pdf->text();
    QSqlQuery test ;
    test.prepare("SELECT COUNT(*) from RECLAM where IDENTIFIANT_E= :id");
    test.bindValue(":id",id);
    test.exec();
    if (test.next())
    {
  if (test.value(0).toInt() == 1)
  {
    QSqlQuery query ;
    query.prepare("select ID , EMAIL ,SUBJECT , CONTENT , DATE_REC from EMPLOYES where IDENTIFIANT_E= :id");
    query.bindValue(":id",id);
    query.exec();
    if (query.next())
    {
    QString ident = query.value(0).toString();
    QString email = query.value(1).toString();
    QString subject = query.value(2).toString();
    QString content = query.value(3).toString();
    QString date = query.value(4).toString();
    painter.drawText(100,300,"successfully export to PDF :)");
    painter.drawText(100,500,"identifiant: ");
     painter.setPen(Qt::black);
    painter.drawText(750,500,ident);
    painter.drawText(100,700,email);
    painter.drawText(100,900,subject);
    painter.drawText(100,1100,content);
    painter.drawText(100,1300,date);
    painter.end();
    QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("pdf done.\n"
                                         "Click ok to exit."), QMessageBox::Ok);
    }
 }
  else
  {
      QMessageBox::information(nullptr, QObject::tr("OK"),
                              QObject::tr("pdf not done.\n"
                                          "Click ok to exit."), QMessageBox::Ok);
  }
  }
}
