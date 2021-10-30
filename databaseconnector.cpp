#include "databaseconnector.h"

DatabaseConnector::DatabaseConnector(QObject *parent) : QObject(parent)
{
    CamTrapDB = QSqlDatabase::addDatabase("QSQLITE");
    CamTrapDB.setDatabaseName("../Cam_Trap/CamTrapDB.db");
    checkDBConnection(&CamTrapDB);
}


DatabaseConnector::~DatabaseConnector()
{
    CamTrapDB.close();
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

void DatabaseConnector::selectDB()
{
    unsigned short int i = 0;
    QSqlQuery *qry = new QSqlQuery(CamTrapDB);
    *qry = CamTrapDB.exec("SELECT * FROM Hayvanlar");

    if(!qry->lastError().isValid())
    {
        while(qry->next())
        {
            qDebug()<<qry->value(i).toString();
            i++;
        }
        qInfo() << "query run";
    }
    else
        qDebug() << qry->lastError().text();

    delete qry;
    qry = nullptr;
}

void DatabaseConnector::insertDB()
{

}

void DatabaseConnector::updateDB()
{

}
