#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
class employe
{
public:
    employe();
    employe(int,QString,QString,QString,QString,QString,int,int);
    employe(QString email,QString password);

    int getid();
    QString getnom();
    QString getprenom();
    QString getpost();
    QString getpassword();
    QString getemail();
    int getsalaire();
    int gettel();

    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setpost(QString);
    void setemail(QString);
    void setpassword(QString);
    void setsalaire(int);
    void settel(int);

    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    bool modifier(int id);
    QSqlQueryModel* Find_employe();
    QSqlQueryModel* recherche_employe(QString search);
    QSqlQueryModel* triID();
    QSqlQueryModel* triNOM();
   int statistiquesemployes(QString post);

   private:
    int id,salaire,tel;
    QString nom, prenom,post,password,email;
};

#endif // EMPLOYE_H
