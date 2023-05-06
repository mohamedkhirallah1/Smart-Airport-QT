#include "reclamation.h"

Reclamation::Reclamation()
{


}
int Reclamation::getId(){
    return this->id;

}
QString Reclamation::getSubject(){
    return this->subject;

}
QString Reclamation::getContent(){
    return this->content;

}
QString Reclamation::getEmail(){
    return this->email;

}

Reclamation::Reclamation(int id,QString content,QString date_rec,QString email,QString subject)
{
    this->id = id;
    this->content = content;
    this->date_rec = date_rec;
    this->email = email;
    this->subject = subject;

}
bool Reclamation::ajouter(){
    QSqlQuery query;
    QString ids=QString::number(id);

    query.prepare("INSERT INTO reclam (id,email, subject, content, date_rec) VALUES (:id,:email, :subject, :content, :date_rec)" );
    query.bindValue(":id",ids);
    query.bindValue(":email",email);
    query.bindValue(":subject", subject);
    query.bindValue(":content", content);
    query.bindValue(":date_rec", date_rec);


    return  query.exec();


}
QSqlQueryModel * Reclamation::afficher(){
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from reclam");



    return  model;

}
QSqlQueryModel * Reclamation::afficher_id(){
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id from reclam");




    return  model;

}
Reclamation Reclamation::getReclamation(QString id){
    QSqlQuery q;
    qDebug()<<"the id is"<<id<<"";
    q.prepare("select * from reclam where id=?;");
     q.addBindValue(id);
        int i=0;
        QString email;

            QString subject;
            QString content;

     if(q.exec()){
         while(q.next()){

             email=q.value(1).toString();

              subject=q.value(2).toString();
                content=q.value(3).toString();
                 i++;
         }

     }

     Reclamation rec(0,"waaaaw","",email,subject);

      qDebug()<<""<<rec.getEmail()<<" "<< rec.getSubject()<<" "<<"";
    return rec;








}
bool Reclamation::supprimer(QString idd)
{
    //QString ids=QString::number(id);

    QSqlQuery query;
    query.prepare("Delete from reclam where id = :id");
    query.bindValue(":id", idd);
    return  query.exec();
}

bool Reclamation::update(QString idd,Reclamation r){

    QSqlQuery query;
    QString ids=QString::number(id);

    query.prepare("update reclam set content = :content, email = :email, subject = :subject  where id = :id");

    query.bindValue(":id", ids);
    query.bindValue(":email", r.getEmail());
    query.bindValue(":content",r.getContent());
    query.bindValue(":subject", r.getSubject());

    return  query.exec();

}
QSqlQueryModel * Reclamation ::triid()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM reclam ORDER BY SUBJECT");
    return model;

}
QSqlQueryModel * Reclamation ::recherche_rec(QString search)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from reclam where id like '%"+search+"%' or content like '%"+search+"%' or date_rec like '%"+search+"%' or subject like '%"+search+"%'  ";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}

