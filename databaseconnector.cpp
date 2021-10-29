#include "databaseconnector.h"

DatabaseConnector::DatabaseConnector(QObject *parent) : QObject(parent)
{
    CamTrapDB = QSqlDatabase::addDatabase("QSQLITE");
    CamTrapDB.setDatabaseName("CamTrap.db");
    checkDBConnection(&CamTrapDB);
}


DatabaseConnector::~DatabaseConnector()
{
    qInfo() << "Deconstructed to DatabaseConnector" << this;
}

void DatabaseConnector::checkDBConnection(QSqlDatabase *db)
{
    if(!db->open())
    {
      msgBox.setText("FAILED");
      msgBox.setInformativeText("Connection FAILED to Database");
      msgBox.exec();
    }
    else
    {
      qInfo() << "Connected to Database" << this;
    }
}
