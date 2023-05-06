#include "gvoyageur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

GVoyageur::GVoyageur()
{
 num=0;
 nom=" ";
 prenom=" ";
 dest=" ";
 agence="";
}
GVoyageur::GVoyageur(int num,QString nom,QString prenom,QString dest,QString agence)
{
this->num=num;
this->nom=nom;
this->prenom=prenom;
this->dest=dest;
    this->agence=agence;

}
int GVoyageur::getnum(){return num;}
QString GVoyageur::getnom(){return nom;}
QString GVoyageur::getprenom(){return prenom;}
QString GVoyageur::getdest(){return dest;}
QString GVoyageur::getagence(){return agence;}

void GVoyageur::setnum(int num){this->num=num;}
void GVoyageur::setnom(QString nom){this->nom=nom;}
void GVoyageur::setprenom(QString prenom){this->prenom=prenom;}
void GVoyageur::setdest(QString dest){this->dest=dest;}
void GVoyageur::setagence(QString agence){this->agence=agence;}

bool GVoyageur::ajouter()
{
    QSqlQuery query;
    QString num_string= QString::number(num);
         query.prepare("INSERT INTO GVoyageur (num, nom, prenom, dest, agence) "
                       "VALUES (:id, :forename, :surname, :destination,:agence)");
         query.bindValue(":id", num_string);
         query.bindValue(":forename", nom);
         query.bindValue(":surname", prenom);
         query.bindValue(":destination", dest);
         query.bindValue(":agence", agence);

         return query.exec();

}
bool GVoyageur::supprimer(int num)
{
    QSqlQuery query;
    QString res=QString::number(num);
    query.prepare("Delete from GVoyageur where NUM= :num");
    query.bindValue(":num",res);
    return query.exec();
}
QSqlQueryModel* GVoyageur::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT* FROM GVoyageur");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Destination"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("agence"));

return model;

}
bool GVoyageur::modifier(int num)
{
    QSqlQuery query;

       QString res= QString::number(num);
       query.prepare("UPDATE GVoyageur SET num=:num,nom=:nom,prenom=:prenom ,dest=:dest ,agence=:agence WHERE num=:num");
       query.bindValue(":num", num);
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
       query.bindValue(":dest", dest);

       query.bindValue(":agence", agence);



          return    query.exec();
}
QSqlQueryModel * GVoyageur::triNUM()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM GVoyageur ORDER BY num");
    return model;

}
QSqlQueryModel * GVoyageur::triNOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM GVoyageur ORDER BY NOM");
    return model;

}

QSqlQueryModel * GVoyageur ::recherche_voyageur(QString search)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from GVoyageur where num like '%"+search+"%' or nom like '%"+search+"%' or prenom like '%"+search+"%' or dest like '%"+search+"%'or agence like '%"+search+"%' ";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}
int GVoyageur::statistiquesvoyageur(QString destination)
{
    QSqlQuery query;
    query.prepare("select count(*) from GVoyageur where dest=:dest ");
    query.bindValue(":dest",destination);
    query.exec();
    query.next();
    return query.value(0).toInt();
}



