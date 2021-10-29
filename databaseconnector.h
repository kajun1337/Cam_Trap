#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QObject>
#include<QtSql/QSql>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlDriver>
#include<QtSql/QSqlQuery>
#include<QMessageBox>
#include<QtDebug>

class DatabaseConnector : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseConnector(QObject *parent = nullptr);
    ~DatabaseConnector();
    void checkDBConnection(QSqlDatabase *db);

signals:

private:
    QSqlDatabase CamTrapDB;
    QMessageBox msgBox;

};

#endif // DATABASECONNECTOR_H
