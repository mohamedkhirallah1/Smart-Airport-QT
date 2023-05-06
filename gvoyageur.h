#ifndef GVOYAGEUR_H
#define GVOYAGEUR_H
#include <QString>
#include <QSqlQueryModel>

class GVoyageur
{
public:
    GVoyageur();
        GVoyageur(int,QString,QString,QString,QString);
        int getnum();
        QString getnom();
        QString getprenom();
        QString getdest();
        QString getagence();

        void setnum(int);
        void setnom(QString);
        void setprenom(QString);
        void setdest(QString);
        void setagence(QString);

        bool ajouter();
        bool supprimer(int num);
        QSqlQueryModel* afficher();
        bool modifier(int num);
        QSqlQueryModel* triNUM();
            QSqlQueryModel* triNOM();
            QSqlQueryModel* recherche_voyageur(QString search);
            int statistiquesvoyageur(QString destination);
             QSqlQueryModel* pourtunisair();
    private:
        int num;
        QString nom, prenom,dest,agence;

};

#endif // GVOYAGEUR_H
