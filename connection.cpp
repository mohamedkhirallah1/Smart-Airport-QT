#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("soumaya");//inserer nom de l'utilisateur
db.setPassword("esprit18");//inserer mot de passe de c
if (db.open())
test=true;





    return  test;
}
