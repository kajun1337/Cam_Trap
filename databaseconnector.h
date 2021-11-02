#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QObject>
#include<QtSql/QSql>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlDriver>
#include<QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include<QMessageBox>
#include <QList>
#include <QMap>
#include<QtDebug>

class DatabaseConnector : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseConnector(QObject *parent = nullptr);
    ~DatabaseConnector();
    QList<QString> selectAllDB(QString table = "", QString query_c = "", unsigned short int tblcolumn = 0);
    QList<QString> selectDB(QString table = "", unsigned short int qrycolumn = 0, QString query_c = "");
    QList<QString> whereDB( QString table = "", unsigned short int qrycolumn = 0, QMap<QString, QString> where_map = QMap<QString, QString> {});
    bool insertDB(QString table = "", QList<QString> columnlist = QList<QString> (), QList<QString> valuelist = QList<QString> ());
    bool updateDB(QString table = "", QMap<QString, QString> set_map = QMap<QString, QString> {}, QMap<QString, QString> where_map = QMap<QString, QString> {});
    bool deleteDB(QString table = "", QString column = "", QString item = "");

signals:

private:
    QSqlDatabase CamTrapDB;

private:
    void checkDBConnection();
    QString setQuery(QString query_init = "", QList<QString> columnlist = QList<QString> (), QList<QString> valuelist = QList<QString> ());
    QString setQuery(QString query_init = "", QMap<QString, QString> set_map = QMap<QString, QString> {},  QMap<QString, QString> where_map = QMap<QString, QString> {});

};

#endif // DATABASECONNECTOR_H
