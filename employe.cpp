
#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

employe::employe()
{
    id=0;
    nom=" ";
    prenom=" ";
    post=" ";
    email=" ";
    password=" ";
    salaire=0;
    tel=0;

}
employe::employe(int id,QString nom,QString prenom,QString post,QString email,QString password,int salaire,int tel)
{
this->id=id;
this->nom=nom;
this->prenom=prenom;
this->post=post;
this->email=email;
this->password=password;
this->salaire=salaire;
this->tel=tel;
}
int employe::getid(){return id;}
QString employe::getnom(){return nom;}
QString employe::getprenom(){return prenom;}
QString employe::getpost(){return post;}
QString employe::getemail(){return email;}
QString employe::getpassword(){return password;}
int employe::getsalaire(){return salaire;}
int employe::gettel(){return tel;}

void employe::setid(int id){this->id=id;}
void employe::setnom(QString nom){this->nom=nom;}
void employe::setprenom(QString prenom){this->prenom=prenom;}
void employe::setpost(QString post){this->post=post;}
void employe::setemail(QString email){this->email=email;}
void employe::setpassword(QString password){this->password=password;}
void employe::setsalaire(int salaire){this->salaire=salaire;}
void employe::settel(int tel){this->tel=tel;}

bool employe::ajouter()
{
    QSqlQuery query;
    QString id_string= QString::number(id);
    QString salaire_string= QString::number(salaire);
    QString tel_string= QString::number(tel);

         query.prepare("INSERT INTO Employe (id, nom, prenom, post,email,password,salaire,tel) "
                       "VALUES (:id, :forename, :surname, :travail, :email, :password, :salaire, :tel)");
         query.bindValue(":id", id_string);
         query.bindValue(":forename", nom);
         query.bindValue(":surname", prenom);
         query.bindValue(":travail", post);
         query.bindValue(":email", email);
         query.bindValue(":password", password);
         query.bindValue(":salaire", salaire_string);
         query.bindValue(":tel", tel_string);

         return query.exec();


}

bool employe::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from employe where ID= :id");
    query.bindValue(":id",res);
    return query.exec();
}
QSqlQueryModel* employe::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

   model->setQuery("SELECT* FROM Employe");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("post"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("password"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("tel"));

return model;

}
bool employe::modifier(int id)
{
    QSqlQuery query;

       QString res= QString::number(id);
       query.prepare("UPDATE Employe SET id=:id,nom=:nom,prenom=:prenom,post=:post,email=:email,password=:password,salaire=:salaire,tel=:tel WHERE id=:id");
       query.bindValue(":id", id);
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
       query.bindValue(":post", post);
       query.bindValue(":email", email);
       query.bindValue(":password", password);
       query.bindValue(":salaire", salaire);
       query.bindValue(":tel", tel);

          return    query.exec();
}
QSqlQueryModel * employe::Find_employe()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT NOM, ID, PRENOM, POST, EMAIL, PASSWORD, SALAIRE, TEL FROM Employe");

    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel * employe::recherche_employe(QString search)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from Employe where id like '%"+search+"%' or nom like '%"+search+"%' or prenom like '%"+search+"%' or post like '%"+search+"%' or email like '%"+search+"%'  or tel like '%"+search+"%'";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}
QSqlQueryModel * employe::triID()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employe ORDER BY id");
    return model;

}
QSqlQueryModel * employe::triNOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employe ORDER BY nom");
    return model;

}
int employe::statistiquesemployes(QString post)
{
    QSqlQuery query;
    query.prepare("select count(*) from employe where post=:post ");
    query.bindValue(":post",post);
    query.exec();
    query.next();

    return query.value(0).toInt();

}
