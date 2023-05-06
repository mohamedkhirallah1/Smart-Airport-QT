#include "gvol.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <qdatetime.h>
GVol::GVol()
{
    num=0;
    des=" ";
    dated=" ";
    datea=" ";
    etat=" ";

}
GVol::GVol(int num,QString des,QString dated,QString datea,QString etat)
{
this->num=num;
this->des=des;
this->dated=dated;
this->datea=datea;
this->etat=etat;

}
int GVol::getnum(){return num;}
QString GVol::getdes(){return des;}
QString GVol::getdated(){return dated;}
QString GVol::getdatea(){return datea;}
QString GVol::getetat(){return etat;}

void GVol::setnum(int num){this->num=num;}
void GVol::setdes(QString des){this->des=des;}
void GVol::setdated(QString dated){this->dated=dated;}
void GVol::setdatea(QString datea){this->datea=datea;}
void GVol::setetat(QString etat){this->etat=etat;}

bool GVol::ajouter()
{
    QSqlQuery query;
    QString num_string= QString::number(num);
         query.prepare("INSERT INTO vol (num, des, dated, datea, etat) "
                       "VALUES (:num, :des, :dated, :datea, :etat)");
         query.bindValue(":num", num_string);
         query.bindValue(":des", des);
         query.bindValue(":dated", dated);
         query.bindValue(":datea", datea);
         query.bindValue(":etat", etat);

         return query.exec();


}
bool GVol::supprimer(int num)
{
    QSqlQuery query;
    QString res=QString::number(num);
    query.prepare("Delete from vol where NUM= :num");
    query.bindValue(":num",res);
    return query.exec();
}
QSqlQueryModel* GVol::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT* FROM vol");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("des"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("dated"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("datea"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("etat"));

return model;

}
bool GVol::modifier(int num)
{
    QSqlQuery query;

       QString res= QString::number(num);
       query.prepare("UPDATE vol SET num=:num,des=:des,dated=:dated ,datea=:datea, etat=:etat WHERE num=:num");
       query.bindValue(":num", num);
       query.bindValue(":des", des);
       query.bindValue(":dated", dated);
       query.bindValue(":datea", datea);
       query.bindValue(":etat", etat);



          return    query.exec();
}
int GVol::statistiquesvol(QString des)
{
    QSqlQuery query;
        query.prepare("select count(*) from vol where des=:des ");
        query.bindValue(":des",des);
        query.exec();
        query.next();
        return query.value(0).toInt();
}
QSqlQueryModel* GVol:: triervol()
{

    QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from vol order by num ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("num")); //donner nom au colonne
     model->setHeaderData(1, Qt::Horizontal, QObject::tr(" des"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("dated "));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("datea"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));


    return model;
}
QSqlQueryModel* GVol::recherche_vol(QString search)
{
    QSqlQueryModel * model= new QSqlQueryModel();
         QString qry="select * from vol where num like '%"+search+"%' or des like '%"+search+"%' or dated like '%"+search+"%' or datea like '%"+search+"%' or etat like '%"+search+"%' ";
         qDebug()<<qry;
         model->setQuery(qry);
         return model;
}
QSqlQueryModel* GVol:: trieretat()
{

    QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from vol order by etat ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("num")); //donner nom au colonne
     model->setHeaderData(1, Qt::Horizontal, QObject::tr(" des"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("dated "));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("datea"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));


    return model;
}
bool GVol::ajouter_etat(QByteArray ID)
{
QSqlQuery query;
if(ID=="1")
{
    QSqlQuery query;

query.prepare("INSERT INTO historique (porte_histo) "
              "VALUES ('door is locked')");
return query.exec();

}
if (ID=="0")
{
    QSqlQuery query;

    query.prepare("INSERT INTO historique (porte_histo) "
                  "VALUES ('door is opened')");
    return query.exec();

}
}
QSqlQueryModel* GVol::afficher_pointage()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM historique");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("pointage"));


 return model;
}
