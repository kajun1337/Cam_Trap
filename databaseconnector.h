#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QObject>
#include<QtSql/QSql>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlDriver>
#include<QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include<QMessageBox>
#include<QtDebug>

class DatabaseConnector : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseConnector(QObject *parent = nullptr);
    ~DatabaseConnector();
    void selectDB();
    void insertDB();
    void updateDB();

signals:

private:
    QSqlDatabase CamTrapDB;
    QMessageBox msgBox;
    void checkDBConnection(QSqlDatabase *db);

};

#endif // DATABASECONNECTOR_H
