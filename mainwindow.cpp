#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gvoyageur.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QTextStream>
#include <QTextDocument>
#include <QDataStream>
#include <QPrinter>
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include"QrCode.hpp"
#include<qsqlquery.h>
#include"arduino.h"
#include "gvol.h"
#include <QSqlRecord>
#include "mainwindow.h"
#include "employe.h"
#include <QApplication>
#include <QMessageBox>
#include <QTableView>
#include <qmessagebox.h>
#include <QIntValidator>
#include <QSqlQuery>
#include <QScrollBar>
#include <qfiledialog.h>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QDate>
#include <QComboBox>
#include <QPrinter>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
#include "qrwidget.h"
#include "qrcodegenratorworke.h"
#include <fstream>
#include <QString>
#include <QSystemTrayIcon>
#include "reclamation.h"
#include "pdf.h"


using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //pour gestion des voyageurs
    ui->le_num->setValidator(new QIntValidator(0, 9999999, this));
   ui->tab_voyageur->setModel(voy.afficher());
   //pour gestion des vols
    ui->le_numv->setValidator(new QIntValidator(0, 9999999, this));
    ui->tab_vol->setModel(V.afficher());
   //gestion employe
    ui->le_id_e->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_tel_e->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_salaire_e->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_id_e1->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_tel_e1->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_salaire_e1->setValidator(new QIntValidator(0, 99999999, this));

    {
        ui->le_poste_e->addItem("Agent de piste");
        ui->le_poste_e->addItem("Ag entretien avion");
        ui->le_poste_e->addItem("Ag bagages");
        ui->le_poste_e->addItem("Agent accueil");
        ui->le_poste_e->addItem("prestations alimentaires");
        ui->le_poste_e->addItem("Service de netoyage");
    }
        {
            ui->le_post_e1->addItem("Agent de piste");
            ui->le_post_e1->addItem("Ag entretien avion");
            ui->le_post_e1->addItem("Ag bagages");
            ui->le_post_e1->addItem("Agent accueil");
            ui->le_post_e1->addItem("prestations alimentaires");
            ui->le_post_e1->addItem("Service de netoyage");
        }


   ui->tab_employe->setModel(Etmp.afficher());
   //for email tab
   connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
   connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

  // ****arduino****
   int ret=A.connect_arduino(); // lancer la connexion à arduino
              switch(ret){
              case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                  break;
              case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                 break;
              case(-1):qDebug() << "arduino is not available";
              }
               QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_update_clicked())); // permet de lancer
               //le slot update_label suite à la reception du signal readyRead (reception des données).


              // refresh();
               ui->pushButton_->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    int num=ui->le_num->text().toInt();
        QString nom=ui->le_nom->text();
        QString prenom=ui->le_prenom->text();
        QString dest=ui->le_dest->text();
        QString agence=ui->le_agence->text();

        GVoyageur voy(num,nom,prenom,dest,agence);
        bool test=voy.ajouter();
        if(test)
       {
            ui->tab_voyageur->setModel(voy.afficher());

          QMessageBox::information(nullptr, QObject::tr("ok"),
          QObject::tr("ajout effectuee.\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_voyageur->setModel(voy.afficher());

       }
        else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("ajout non effectuÃ©.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_2_clicked()
{
    int num =ui->le_numS->text().toInt();
       bool test=voy.supprimer(num);
       if(test)
      {
           ui->tab_voyageur->setModel(voy.afficher());

         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectuÃ©.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectuÃ©.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_3_clicked()
{

    int num = ui->le_num_2->text().toInt();
        QString nom= ui->le_nom_2->text();
         QString prenom= ui->le_prenom_2->text();
         QString dest = ui->le_dest_2->text();
         QString agence = ui->le_agence_2->text();

        GVoyageur voy(num,nom,prenom,dest,agence);
        bool test=voy.modifier(num);
        if(test)
        {

            ui->tab_voyageur->setModel(voy.afficher());//refresh

                   QMessageBox::information(nullptr, QObject::tr("effectuÃ©"),
                        QObject::tr(" ModifiÃ©.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
                   ui->le_num_2->clear();
                   ui->le_nom_2->clear();
                   ui->le_prenom_2->clear();
                   ui->le_dest_2->clear();
                   ui->le_agence_2->clear();

       }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("non effectuÃ©"),
                        QObject::tr("non modifiÃ© !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->le_num_2->clear();
            ui->le_nom_2->clear();
            ui->le_prenom_2->clear();
            ui->le_dest_2->clear();
            ui->le_agence_2->clear();



        }

}


void MainWindow::on_pushButton_5_clicked()
{
  ui->tab_voyageur->setModel(voy.triNUM());
}

void MainWindow::on_pushButton_6_clicked()
{
     ui->tab_voyageur->setModel(voy.triNOM());
}

void MainWindow::on_pushButton_4_clicked()
{
    GVoyageur voy;
        ui->tab_voyageur->setModel(voy.recherche_voyageur(ui->recherche->text()));
}

void MainWindow::on_pushButton_7_clicked()
{


    //pdf : vous trouver le fichier dans le dossier build

        QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tab_voyageur->model()->rowCount();
                    const int columnCount =ui->tab_voyageur->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("voyageur")
                            <<  "</head>\n"
                            "<body bgcolor=#55ffff link=#5000A0>\n"
                                "<h1>Liste des voyageurs</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tab_voyageur->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_voyageur->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tab_voyageur->isColumnHidden(column)) {
                                       QString data = ui->tab_voyageur->model()->data(ui->tab_voyageur->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";



            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);


            //QTextDocument document;
            //document.setHtml(html);
            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("mypdffile1.pdf");
            document->print(&printer);


}

void MainWindow::on_stat_clicked()

    {
        GVoyageur voy;
        QBarSet *set0 = new QBarSet("statistique : courbe");

        *set0 << voy.statistiquesvoyageur("tunis") <<voy.statistiquesvoyageur("france")<<voy.statistiquesvoyageur("allemagne");


        QColor color(0x0000ff);
        set0->setColor(color);

        QBarSeries *series = new QBarSeries();
        series->append(set0);




        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setBackgroundVisible(false);

        QColor bgColor(0xa9a9a9);
                       chart->setBackgroundBrush(QBrush(QColor(bgColor)));

                       chart->setBackgroundVisible(true);

        QStringList categories;
        categories << "Tunis" << "France"<< "Allemagne";
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        QChartView *chartView = new QChartView(chart);

        chartView->setMinimumWidth(500);
        chartView->setMinimumHeight(300);
        chartView->setParent(ui->stat_2);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chartView->show();


}

void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("mohamedsalah.bedoui@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("mohamedsalah.bedoui@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("mohamedsalah.bedoui@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

}

void MainWindow::on_browseBtn_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}






void MainWindow::on_Qr_clicked()
{ int tabvoy=ui->tab_voyageur->currentIndex().row();
    QVariant idd=ui->tab_voyageur->model()->data(ui->tab_voyageur->model()->index(tabvoy,0));
    QString num= idd.toString();
    QSqlQuery qry;
    qry.prepare("select * from GVoyageur where num=:num");
    qry.bindValue(":num",num);
    qry.exec();
    QString nom, prenom, dest, agence,ids;
    while(qry.next()){
        nom=qry.value(1).toString();
        prenom=qry.value(2).toString();
        dest=qry.value(3).toString();
        agence=qry.value(4).toString();
    }
    ids=QString(num);
    ids="num: "+ids+" Nom: "+nom+" prenom: "+prenom+" dest: "+dest+"agence : "+agence;
    QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if(color==0)
                im.setPixel(x, y,qRgb(254, 254, 254));
            else
                im.setPixel(x, y,qRgb(0, 0, 0));
        }
    }
    im=im.scaled(200,200);
    ui->label_14->setPixmap(QPixmap::fromImage(im));



}

void MainWindow::on_tunisair_clicked()
{
    int agence_tunisair; //gain mteha 0.8%
       int totale ; // totale bech nestaamloha lel calcul mtaa gain
        QSqlQuery query;
            query.prepare("select count(*) from GVoyageur where agence = 'tunisair' ");
            query.exec();
            query.first();
            agence_tunisair = (query.value(0).toInt());

            query.prepare("select count(*) from GVoyageur ");
                query.exec();
                query.first();
                totale =(query.value(0).toInt());
            agence_tunisair=(((double)agence_tunisair)*100 /(double)totale);
            agence_tunisair=agence_tunisair+(agence_tunisair*(0.8/100));


            QString agence_tunisair2=QString::number(agence_tunisair);
            ui->tunisair_2->setText(agence_tunisair2);
}

void MainWindow::on_kounouz_clicked()
{
    int agence_kounouz; //gain mteha 0.8%
       int totale ; // totale bech nestaamloha lel calcul mtaa gain
        QSqlQuery query;
            query.prepare("select count(*) from GVoyageur where agence = 'kounouz' ");
            query.exec();
            query.first();
            agence_kounouz = (query.value(0).toInt());

            query.prepare("select count(*) from GVoyageur ");
                query.exec();
                query.first();
                totale =(query.value(0).toInt());
            agence_kounouz=(((double)agence_kounouz)*100 /(double)totale);
            agence_kounouz=agence_kounouz+(agence_kounouz*(0.2/100));


            QString agence_kounouz2=QString::number(agence_kounouz);
            ui->kounouz_2->setText(agence_kounouz2);
}
void MainWindow::on_tls_2_clicked()
{
    int agence_tls; //gain mteha 0.8%
       int totale ; // totale bech nestaamloha lel calcul mtaa gain
        QSqlQuery query;
            query.prepare("select count(*) from GVoyageur where agence = 'tls' ");
            query.exec();
            query.first();
            agence_tls = (query.value(0).toInt());

            query.prepare("select count(*) from GVoyageur ");
                query.exec();
                query.first();
                totale =(query.value(0).toInt());
            agence_tls=(((double)agence_tls)*100 /(double)totale);
            agence_tls=agence_tls+(agence_tls*(0.5/100));


            QString agence_tls2=QString::number(agence_tls);
            ui->tls->setText(agence_tls2);
}


//gestion des vols ****************
//***************************************************************************************************************************************

void MainWindow::on_ajoutervol_clicked()
{
    int num=ui->le_numv->text().toInt();
        QString des=ui->le_destv->text();
        QString dated=ui->le_date_d->text();
        QString datea=ui->le_date_a->text();
        QString etat=ui->le_etat->text();

        GVol V(num,des,dated,datea,etat);
        bool test=V.ajouter();
        if(test)
       {
               ui->tab_vol->setModel(V.afficher());
          QMessageBox::information(nullptr, QObject::tr("ok"),
          QObject::tr("ajout effectué.\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);

       }
        else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("ajout non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supprimervol_clicked()
{
    int num =ui->s_numv->text().toInt();
       bool test=V.supprimer(num);
       if(test)
      {
          ui->tab_vol->setModel(V.afficher());
         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tab_vol->setModel(V.afficher());
      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_modifiervol_clicked()
{
    int num = ui->m_numv->text().toInt();
            QString des= ui->m_des->text();
             QString dated= ui->m_date_d->text();
             QString datea = ui->m_date_a->text();
             QString etat = ui->le_etat_m->text();

            GVol V(num,des,dated,datea,etat);
            bool test=V.modifier(num);
            if(test)
            {
  ui->tab_vol->setModel(V.afficher());

                       QMessageBox::information(nullptr, QObject::tr("effectué"),
                            QObject::tr(" Modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                       ui->m_numv->clear();
                       ui->m_des->clear();
                       ui->m_date_d->clear();
                       ui->m_date_a->clear();
                       ui->le_etat_m->clear();

           }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                            QObject::tr("non modifié !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->m_numv->clear();
                ui->m_des->clear();
                ui->m_date_d->clear();
                ui->m_date_a->clear();
                ui->le_etat_m->clear();



            }
}

void MainWindow::on_stati_clicked()
{
    GVol v;

                QBarSet *set0 = new QBarSet("statistique : courbe");

                *set0 << v.statistiquesvol("tunis") <<v.statistiquesvol("france")<<v.statistiquesvol("allemagne");


                QColor color(0x6568F3);
                set0->setColor(color);

                QBarSeries *series = new QBarSeries();
                series->append(set0);




                QChart *chart = new QChart();
                chart->addSeries(series);
                chart->setTitle("");
                chart->setAnimationOptions(QChart::SeriesAnimations);
                chart->setBackgroundVisible(false);

                QColor bgColor(0xF4DCD3);
                               chart->setBackgroundBrush(QBrush(QColor(bgColor)));

                               chart->setBackgroundVisible(true);

                QStringList categories;
                categories << "Tunis" << "France"<< "Allemagne";
                QBarCategoryAxis *axis = new QBarCategoryAxis();
                axis->append(categories);
                chart->createDefaultAxes();
                chart->setAxisX(axis, series);

                QChartView *chartView = new QChartView(chart);

                chartView->setMinimumWidth(500);
                chartView->setMinimumHeight(300);
                chartView->setParent(ui->st);
                chart->legend()->setAlignment(Qt::AlignBottom);
                chartView->show();
}

void MainWindow::on_tri_clicked()
{
     ui->tab_vol->setModel(V.triervol());
}

void MainWindow::on_rech_clicked()
{
     ui->tab_vol->setModel(V.recherche_vol(ui->re->text()));
}

void MainWindow::on_generationpdfvol_clicked()
{
    //pdf : vous trouver le fichier dans le dossier build

            QString strStream;
                        QTextStream out(&strStream);
                        const int rowCount = ui->tab_vol->model()->rowCount();
                        const int columnCount =ui->tab_vol->model()->columnCount();


                        out <<  "<html>\n"
                                "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                <<  QString("<title>%1</title>\n").arg("voyageur")
                                <<  "</head>\n"
                                "<body bgcolor=#55ffff link=#5000A0>\n"
                                    "<h1>Liste des vols</h1>"

                                    "<table border=1 cellspacing=0 cellpadding=2>\n";

                        // headers
                            out << "<thead><tr bgcolor=#f0f0f0>";
                            for (int column = 0; column < columnCount; column++)
                                if (!ui->tab_vol->isColumnHidden(column))
                                    out << QString("<th>%1</th>").arg(ui->tab_vol->model()->headerData(column, Qt::Horizontal).toString());
                            out << "</tr></thead>\n";
                            // data table
                               for (int row = 0; row < rowCount; row++) {
                                   out << "<tr>";
                                   for (int column = 0; column < columnCount; column++) {
                                       if (!ui->tab_vol->isColumnHidden(column)) {
                                           QString data = ui->tab_vol->model()->data(ui->tab_vol->model()->index(row, column)).toString().simplified();
                                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                       }
                                   }
                                   out << "</tr>\n";
                               }
                               out <<  "</table>\n"
                                   "</body>\n"
                                   "</html>\n";



                QTextDocument *document = new QTextDocument();
                document->setHtml(strStream);


                //QTextDocument document;
                //document.setHtml(html);
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("mypdffile1.pdf");
                document->print(&printer);
}









void MainWindow::on_updatemap_clicked()
{
    int etat;
                QSqlQuery query;
                    query.prepare("select count(*) from vol where etat = 'en cours' ");
                    query.exec();
                    query.first();
                    etat = (query.value(0).toInt());
                    QString etat2=QString::number(etat);
                    ui->lineEdit1->setText(etat2);
                    query.prepare("select count(*) from vol where etat = 'arrivee' ");
                    query.exec();
                    query.first();
                    etat = (query.value(0).toInt());
                    QString etat3=QString::number(etat);
                    ui->line3->setText(etat3);
                    query.prepare("select count(*) from vol where etat = 'non arrivee' ");
                    query.exec();
                    query.first();
                    etat = (query.value(0).toInt());
                    QString etat4=QString::number(etat);
                    ui->line2->setText(etat4);
}

void MainWindow::on_tri_par_etat_clicked()
{
    ui->tab_vol->setModel(V.trieretat());
}




//************ fin gestion des vols




void MainWindow::on_update_clicked()
{
    ID=A.read_from_arduino();

            bool test=V.ajouter_etat( ID);
            if(test==true)
           {
                  ui->tab_pointage->setModel(V.afficher_pointage());
              //QMessageBox::information(nullptr, QObject::tr("ok"),
              //QObject::tr("door is opened.\n"
                          //"Click Cancel to exit."), QMessageBox::Cancel);

           }

               { ui->tab_pointage->setModel(V.afficher_pointage());

             //QMessageBox::critical(nullptr, QObject::tr("not ok"),
           //  QObject::tr("door is closed.\n"
                      //   "Click Cancel to exit."), QMessageBox::Cancel);


        }
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    {

            this->select_date = date.toString("yyyy-MM-dd");

            this->selected_day_json = this->json[date.toString("yyyy-MM-dd")].toArray();

            if (selected_day_json.size()) {

               // ui->comboBox->clear();

                for (int i = 0; i < selected_day_json.size(); i++) {

                    auto context_name =

                        selected_day_json[i].toObject()["context_name"].toString();

                }

            } else {

                ui->lineEdit_vol->setText("vol");

                auto format = ui->calendarWidget->dateTextFormat(

                    ui->calendarWidget->selectedDate());

                format.setBackground(QColor("#FFFFFF"));

                ui->calendarWidget->setDateTextFormat(

                    ui->calendarWidget->selectedDate(), format);

            }
}}

void MainWindow::on_addvol_clicked()
{
    bool ok;

            QString text = QInputDialog::getText(

                this, tr("Evenement d'entré"), tr("Veuillez entrer le nom de vol"), QLineEdit::Normal, 0, &ok);

            if (!ok || text.isEmpty()) return;



            auto date = ui->calendarWidget->selectedDate();



            QString event_title = text;

            QString event_start = "";

            QString event_end = "";

            QString event_local = "";

            QString _method = "POST";

            date = date.addDays(-1);

            event_start = event_end = date.toString("yyyy-MM-ddT16%3A00%3A00Z");



            QByteArray byte;

            byte.append("calendar_event%5Btitle%5D=" + event_title.toUtf8());

            byte.append("&calendar_event%5Bstart_at%5D=" + event_start.toUtf8());

            byte.append("&calendar_event%5Bend_at%5D=" + event_end.toUtf8());

            byte.append("&calendar_event%5Blocation_name%5D=" + event_local.toUtf8());

         //   byte.append("&calendar_event%5Bcontext_code%5D=user_" + user);

            byte.append("&_method=POST");

           // byte.append("&authenticity_token=" + token);

            QString url = "http://canvas.tongji.edu.cn/api/v1/calendar_events";

            //auto re = post(url, byte, "application/x-www-form-urlencoded");



           /* auto document = QJsonDocument::fromJson(re);

            auto object = document.object();

            auto value = object.value("id");

            auto plid = value.toInt();*/



            QJsonObject temp;

            temp.insert("context_name", QString(name));

            temp.insert("context_type", "User");

            QString d = date.toString("yyyy-MM-dd");

            d = d + "T16:00:00Z";

            temp.insert("plannable_date", d);

            QJsonObject pl;

            pl.insert("title", text);

            temp.insert("plannable", QJsonValue(pl));

           // temp.insert("plannable_id", plid);

           /* QJsonValueRef ref = this->json.find(this->select_date).value();

            QJsonArray arr = ref.toArray();

            arr.append(temp);

            ref = arr;*/



            auto format =

                ui->calendarWidget->dateTextFormat(ui->calendarWidget->selectedDate());

            format.setBackground(QColor("#00FFFF"));

            ui->calendarWidget->setDateTextFormat(ui->calendarWidget->selectedDate(),

                                                  format);



          //  on_calendarWidget_clicked(ui->calendarWidget->selectedDate());


}
                 // GESTION EMPLOYE

void MainWindow::on_pb_ajouter_e_clicked()
{
    int id=ui->le_id_e->text().toInt();
    QString nom=ui->le_nom_e->text();
    QString prenom=ui->le_prenom_e->text();
    QString post=ui->le_poste_e->currentText();
    QString email=ui->le_email_e->text();
    QString password=ui->le_password_e->text();
    int salaire=ui->le_salaire_e->text().toInt();
    int tel=ui->le_tel_e->text().toInt();

    employe E(id,nom,prenom,post,email,password,salaire,tel);
    bool test=E.ajouter();
    if(test)
   {
        foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                                       le->clear();}
                                  QFile file("C:/Users/pc/Desktop/Nouveau dossier/historique.txt");
                                  if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                                      return;
                                  QTextStream cout(&file);
                                  QString d_info = QDateTime::currentDateTime().toString();
                                  QString message2=" + "+d_info+" Une employe a été ajouté sous le nom de mr/mme : "+nom+" " ""+prenom+"\n";
                                  cout << message2;
        ui->tab_employe->setModel(Etmp.afficher());
      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("ajout effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);

   }
    else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("ajout non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer_2_clicked()
{
   int id =ui->le_idS_2->text().toInt();
   bool test=Etmp.supprimer(id);
   if(test)
  {
       foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                            le->clear();}
                       QFile file("C:/Users/pc/Desktop/Nouveau dossier/historique.txt");
                       if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                           return;
                       QTextStream cout(&file);//variable de pointeur aal fichier
                       QString d_info = QDateTime::currentDateTime().toString();// trajaalek el date de systeme
                       QString message2=" - "+d_info+" Une réservation a été supprimé sous la ID : "+id+"\n";
                       cout << message2;
       ui->tab_employe->setModel(Etmp.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),
     QObject::tr("suppression effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
ui->tab_employe->setModel(Etmp.afficher());
  }
   else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("suppression non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pb_modifier_2_clicked()
{
    int id = ui->le_id_e1->text().toInt();
        QString nom= ui->le_nom_e1->text();
         QString prenom= ui->le_prenom_e1->text();
         QString post = ui->le_post_e1->currentText();
         QString email=ui->le_email_e1->text();
         QString password=ui->le_password_e1->text();
         int salaire=ui->le_salaire_e1->text().toInt();
         int tel=ui->le_tel_e1->text().toInt();

        employe Etmp(id,nom,prenom,post,email,password,salaire,tel);
        bool test=Etmp.modifier(id);
        if(test)
        {
            foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                                 le->clear();}
                            QFile file("C:/Users/pc/Desktop/Nouveau dossier/historique.txt");
                            if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                                return;
                            QTextStream cout(&file);
                            QString d_info = QDateTime::currentDateTime().toString();
                            QString message2=" ~ "+d_info+" Une employe a été modifié sous le nom de mr/mme : "+nom+" " ""+prenom+"\n";
                            cout << message2;

            ui->tab_employe->setModel(Etmp.afficher());//refresh

                   QMessageBox::information(nullptr, QObject::tr("effectué"),
                        QObject::tr(" Modifié.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
                   ui->le_id_e1->clear();
                   ui->le_nom_e1->clear();
                   ui->le_prenom_e1->clear();
                   ui->le_post_e1->clear();
                   ui->le_email_e1->clear();
                   ui->le_password_e1->clear();
                   ui->le_salaire_e1->clear();
                   ui->le_tel_e1->clear();

       }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                        QObject::tr("non modifié !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->le_id_e1->clear();
            ui->le_nom_e1->clear();
            ui->le_prenom_e1->clear();
            ui->le_post_e1->clear();
            ui->le_email_e1->clear();
            ui->le_password_e1->clear();
            ui->le_salaire_e1->clear();
            ui->le_tel_e1->clear();

        }

}

void MainWindow::on_pb_rechercher_clicked()
{

    employe Etmp;
    ui->tab_employe->setModel(Etmp.recherche_employe(ui->recherche_2->text()));
}

void MainWindow::on_pb_excel_clicked()
{
    employe Etmp;
               QSqlQueryModel * model=new QSqlQueryModel();
               model=Etmp.Find_employe();
               QString textData= "id                       nom                         prenom                     post                       email                       password                         salaire                     tel \n";
               int rows=model->rowCount();
               int columns=model->columnCount();
               for (int i = 0; i < rows; i++)
               {
                   for (int j = 0; j < columns; j++)
                   {
                       textData += model->data(model->index(i,j)).toString();
                       textData +=" ; ";
                   }
                   textData += "\n";
               }
               QString fileName = QFileDialog::getSaveFileName(this, "Export Excel", QString(), "*.csv");
               if (!fileName.isEmpty())
                   if (QFileInfo(fileName).suffix().isEmpty())
                       fileName.append(".csv");
               QFile csvfile(fileName);
               if(csvfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
               {
                   QTextStream out(&csvfile);
                   out<<textData;
               }
               csvfile.close();
}





void MainWindow::on_id_clicked()
{
    ui->tab_employe->setModel(Etmp.triID());
}

void MainWindow::on_nom_clicked()
{
    ui->tab_employe->setModel(Etmp.triNOM());

}


void MainWindow::on_pushButtone_clicked()
{
    QPdfWriter pdf("C:/Users/pc/Desktop/pdf/Liste_Employe.pdf");

       QPainter painter(&pdf);
       int i = 4100;
       const QImage image(":/Resources/client_img/logo.png");
                   const QPoint imageCoordinates(155,0);
                   int width1 = 1600;
                   int height1 = 1600;
                   QImage img=image.scaled(width1,height1);
                   painter.drawImage(imageCoordinates, img );


              QColor dateColor(0x4a5bcf);
              painter.setPen(dateColor);

              painter.setFont(QFont("Montserrat SemiBold", 11));
              QDate cd = QDate::currentDate();
              painter.drawText(8400,250,cd.toString("Tunis"));
              painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

              QColor titleColor(0x341763);
              painter.setPen(titleColor);
              painter.setFont(QFont("Montserrat SemiBold", 25));

              painter.drawText(3000,2700,"Liste des Employes");

              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,3300,9400,500);

              painter.setFont(QFont("Montserrat SemiBold", 10));

              painter.drawText(500,3600,"Id");
              painter.drawText(2000,3600,"Nom");
              painter.drawText(3300,3600,"prenom");
              painter.drawText(4500,3600,"post");
              painter.drawText(7500,3600,"email");
              painter.setFont(QFont("tel", 10));
              painter.drawRect(100,3300,9400,9000);

              QSqlQuery query;
              query.prepare("select * from employe");
              query.exec();
              int y=4300;
              while (query.next())
              {
                  painter.drawLine(100,y,9490,y);
                  y+=500;
                  painter.drawText(500,i,query.value(0).toString());
                  painter.drawText(2000,i,query.value(1).toString());
                  painter.drawText(3300,i,query.value(2).toString());
                  painter.drawText(4500,i,query.value(3).toString());
                  painter.drawText(7500,i,query.value(4).toString());

                 i = i + 500;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pb_stat_clicked()
{
    employe etmp;
        QBarSet *set0 = new QBarSet("posts des employés ");

        *set0 << etmp.statistiquesemployes("Agent de piste") << etmp.statistiquesemployes("Ag entretien avion") << etmp.statistiquesemployes("Ag bagages") << etmp.statistiquesemployes("Agent accueil") << etmp.statistiquesemployes("prestations alimentaires") << etmp.statistiquesemployes("Service de netoyage");


        QColor color(0x6568F3);
        set0->setColor(color);

        QBarSeries *series = new QBarSeries();
        series->append(set0);




        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setBackgroundVisible(false);

        QColor bgColor(0xF4DCD3);
                       chart->setBackgroundBrush(QBrush(QColor(bgColor)));

                       chart->setBackgroundVisible(true);

        QStringList categories;
        categories << "Agent de piste" << "Ag entretien avion" << "Ag bagages" << "Agent accueil" << "prestations alimentaires" << "Service de netoyage";
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        QChartView *chartView = new QChartView(chart);

        chartView->setMinimumWidth(500);
        chartView->setMinimumHeight(300);
        chartView->setParent(ui->stat_3);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chartView->show();

}

void MainWindow::on_qr_clicked()
{ int tabvoy=ui->tab_employe->currentIndex().row();
    QVariant idd=ui->tab_employe->model()->data(ui->tab_employe->model()->index(tabvoy,0));
    QString id= idd.toString();
    QSqlQuery qry;
    qry.prepare("select * from employe where id=:id");
    qry.bindValue(":id",id);
    qry.exec();
    QString nom, prenom, post,ids;
    while(qry.next()){
        nom=qry.value(1).toString();
        prenom=qry.value(2).toString();
        post=qry.value(3).toString();
    }
    ids=QString(id);
    ids="id: "+ids+" Nom: "+nom+" prenom: "+prenom+" post: "+post;
    QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if(color==0)
                im.setPixel(x, y,qRgb(254, 254, 254));
            else
                im.setPixel(x, y,qRgb(0, 0, 0));
        }
    }
    im=im.scaled(200,200);
    ui->qrcode->setPixmap(QPixmap::fromImage(im));



}


void MainWindow::readfile(){
    QString filename="C:/Users/pc/Desktop/Nouveau dossier/historique.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "fichier not existed ! "<<filename;
    }else{
        qDebug() << filename<<" ok ...";
    }
    QString line;
    ui->textHisto_2->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            ui->textHisto_2->setText(ui->textHisto_2->toPlainText()+line+"\n");
        }
    }
    file.close();
}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    readfile();
}
//_________________________________________________gestion reclamations
void MainWindow::on_pushButton_10_clicked()
{
    int id = ui->line_pdf->text().toInt();
    QString email = ui->lineEdit_4->text();
    QString subject = ui->lineEdit_3->text();
    QString content = ui->lineEdit_5->text();
    QString date = ui->daate->text();

    //int id,QString content,QString date_rec,QString email,QString subject
    Reclamation rec(id,content,date,email,subject);

    if(rec.ajouter()){
        refresh();

        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->showMessage("ALERTE NOTIF","un element ajoutée ",QSystemTrayIcon::Information,15000);

    }
    else{QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->showMessage("ALERTE NOTIF","un element non ajoutée ",QSystemTrayIcon::Critical,15000);
        refresh();
    }
}
void MainWindow::refresh(){
    Reclamation r;
        ui->tableView_3->setModel(r.afficher());
        ui->comboBox_3->setModel(r.afficher_id());



}
void MainWindow::on_pushButton_11_clicked()
{
    QString id = ui->comboBox_3->currentText();
  Reclamation rec;
    Reclamation r = rec.getReclamation(id);
    qDebug()<<r.getSubject();
    ui->lineEdit_4->setText(r.getEmail());
       ui->lineEdit_3->setText(r.getSubject());
       ui->pushButton_->show();
       //ui->pushButton_11->hide();
       ui->comboBox_3->hide();
      // ui->pushButton_12->hide();




}

void MainWindow::on_pushButton_12_clicked()
{
    Reclamation r ;
    if(r.supprimer(ui->comboBox_3->currentText())){

        refresh();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->showMessage("ALERTE NOTIF","un element supprimé ",QSystemTrayIcon::Information,15000);
    }
    else{
        refresh();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->showMessage("ALERTE NOTIF","un element non supprimé ",QSystemTrayIcon::Critical,15000);

    }

}


void MainWindow::on_pushButton_4__clicked()

{
    refresh();
}
/*{
    Reclamation r ;
    if(r.supprimer(ui->comboBox_3->currentText())){

        refresh();
    }
    else{
        refresh();
    }

}*/

void MainWindow::on_pushButton__clicked()
{
    int id = ui->line_pdf->text().toInt();
    QString email = ui->lineEdit_4->text();
    QString subject = ui->lineEdit_3->text();
    QString content = ui->lineEdit_5->text();
    QString date = ui->daate->text();

    Reclamation r(id,content,date,email,subject);

    QString ids=QString::number(id);

    r.update(ids,r);
    refresh();
    ui->pushButton->hide();
    ui->pushButton_11->show();
    ui->comboBox_3->show();
    ui->pushButton_12->show();

}

void MainWindow::on_pushButton_2__clicked()
{
    refresh();
}

void MainWindow::on_pushButton_3__clicked()
{
    //pdf : vous trouver le fichier dans le dossier build

            QString strStream;
                        QTextStream out(&strStream);
                        const int rowCount = ui->tableView_3->model()->rowCount();
                        const int columnCount =ui->tableView_3->model()->columnCount();


                        out <<  "<html>\n"
                                "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                <<  QString("<title>%1</title>\n").arg("voyageur")
                                <<  "</head>\n"
                                "<body bgcolor=#55ffff link=#5000A0>\n"
                                    "<h1>Liste des voyageurs</h1>"

                                    "<table border=1 cellspacing=0 cellpadding=2>\n";

                        // headers
                            out << "<thead><tr bgcolor=#f0f0f0>";
                            for (int column = 0; column < columnCount; column++)
                                if (!ui->tableView_3->isColumnHidden(column))
                                    out << QString("<th>%1</th>").arg(ui->tableView_3->model()->headerData(column, Qt::Horizontal).toString());
                            out << "</tr></thead>\n";
                            // data table
                               for (int row = 0; row < rowCount; row++) {
                                   out << "<tr>";
                                   for (int column = 0; column < columnCount; column++) {
                                       if (!ui->tableView_3->isColumnHidden(column)) {
                                           QString data = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, column)).toString().simplified();
                                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                       }
                                   }
                                   out << "</tr>\n";
                               }
                               out <<  "</table>\n"
                                   "</body>\n"
                                   "</html>\n";



                QTextDocument *document = new QTextDocument();
                document->setHtml(strStream);


                //QTextDocument document;
                //document.setHtml(html);
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("mypdffile1.pdf");
                document->print(&printer);
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                    notifyIcon->show();
                    notifyIcon->showMessage("ALERTE NOTIF","pdf ajoutée ",QSystemTrayIcon::Information,15000);
}




void MainWindow::on_trienom_clicked()
{ Reclamation r;
    ui->tableView_3->setModel(r.triid());
}

void MainWindow::on_recherche_clicked()
{ Reclamation r;
            ui->tableView_3->setModel(r.recherche_rec(ui->recherche_2->text()));

}

void MainWindow::on_frame_2_customContextMenuRequested(const QPoint &pos)
{

}

void MainWindow::on_comboBox_3_activated(const QString &arg1)
{

}


void MainWindow::on_recherche_3_clicked()
{
    Reclamation r;
               ui->tableView_3->setModel(r.recherche_rec(ui->recherche_4->text()));
}
