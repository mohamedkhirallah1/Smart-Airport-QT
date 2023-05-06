#ifndef GVOL_H
#define GVOL_H
#include <QString>
#include <QSqlQueryModel>

class GVol
{
public:
    GVol();
    GVol(int,QString,QString,QString,QString);
        int getnum();
        QString getdes();
        QString getdated();
        QString getdatea();
        QString getetat();

        void setnum(int);
        void setdes(QString);
        void setdated(QString);
        void setdatea(QString);
        void setetat(QString);
 // integration mtaa khouna chaabi
        bool ajouter();
        bool supprimer(int num);
         QSqlQueryModel* afficher();
        bool modifier(int num);
        int statistiquesvol(QString des);
        QSqlQueryModel* triervol();
        QSqlQueryModel* recherche_vol(QString search);
        QString* total();
        QString* calcul(QString x );
    QSqlQueryModel* trieretat();
    bool ajouter_etat(QByteArray);
            QSqlQueryModel* afficher_pointage();

private:
        int num;
        QString des,dated,datea,etat;
};

#endif // GVOL_H
