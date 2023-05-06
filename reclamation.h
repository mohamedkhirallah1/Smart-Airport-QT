#ifndef RECLAMATION_H
#define RECLAMATION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDebug>
class Reclamation
{
   private :
    int id;
    QString subject;
    QString content;
    QString date_rec;
    QString email;



public:
    Reclamation();
    QSqlQueryModel * afficher();
     Reclamation(int,QString,QString,QString,QString);
     int getId();
      QString getSubject();
      QString getDate();
     QString getContent();
      QString getEmail();
     void setSubject(QString subject);
     void setEmail(QString subject);
     void setContent(QString subject);
     //void setSubject(QString subject);
     QSqlQueryModel * afficher_id();
     bool supprimer (int);
     bool modifier (int);
        Reclamation getReclamation(QString);
        bool update(QString id,Reclamation r);
        QSqlQueryModel* triid();
        QSqlQueryModel* recherche_rec(QString search);


      bool ajouter();
      bool supprimer(QString idd);
};

#endif // RECLAMATION_H
