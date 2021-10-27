#include "databaseconnector.h"

DatabaseConnector::~DatabaseConnector()
{
    qInfo()<<"obje silindi"<<this;
}

DatabaseConnector::DatabaseConnector(QObject *parent) : QObject(parent)
{
    QSqlDatabase CamTrapDB=QSqlDatabase::addDatabase("QSQLITE");
    CamTrapDB.setDatabaseName("CamTrap.db");



    if(!CamTrapDB.open())
    {
      qInfo()<<"baglanmadı"<<this;

    }
    else
    {
      qInfo()<<"baglandı"<<this;
    }


}
