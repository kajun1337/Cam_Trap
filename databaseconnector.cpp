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
    if(db->open())
    {
        qInfo() << "Connected to Database" << this;
    }
    else
    {
        QMessageBox::critical(nullptr, "HATA", "Veri Tabani Baglantisi Kurulamadi!");
    }
}

QString DatabaseConnector::setQuery(QString query_init, QList<QString> columnlist, QList<QString> valuelist)
{
    foreach(QString item_c, columnlist)
    {
        query_init+=item_c;
        if(!columnlist.endsWith(item_c))
            query_init+=",";
        else
            query_init += ") VALUES (";
    }

    foreach(QString item_v, valuelist)
    {
        query_init+="'";
        query_init+=item_v;
        query_init+="'";
        if(!valuelist.endsWith(item_v))
            query_init+=",";
        else
            query_init += ")";
    }

    return query_init;
}

QString DatabaseConnector::setQuery(QString query_init, QMap<QString, QString> set_map, QMap<QString, QString> where_map)
{
    foreach(QString key, set_map.keys())
    {
        query_init+=key;
        query_init+="='";
        query_init+=set_map[key];
        query_init+="'";
        if(key != set_map.lastKey())
            query_init+=",";
        else
            query_init = query_init + " WHERE " + where_map.lastKey() + "='" + where_map.last() + "'";
    }
    qInfo() << query_init;
    return query_init;
}

QList<QString> DatabaseConnector::selectAllDB(QString table, QString query_c, unsigned short int tblcolumn)
{
    QList<QString> values;
    QString value = "";
    QSqlQuery *qry = new QSqlQuery(CamTrapDB);
    QString query = "SELECT * FROM " + table + query_c;
    *qry = CamTrapDB.exec(query);

    if(!qry->lastError().isValid())
    {
        while(qry->next())
        {
            for(unsigned short int i = 0; i < tblcolumn; i++)
            {
                    value = qry->value(i).toString();
                    values << value;
            }
        }
    }
    else
        QMessageBox::critical(nullptr, "VERI TABANI HATASI", qry->lastError().text());

    delete qry;
    qry = nullptr;

    return values;
}

QList<QString> DatabaseConnector::selectDB(QString table, unsigned short int qrycolumn, QString query_c)
{
    QList<QString> values;
    QString value = "";
    QSqlQuery *qry = new QSqlQuery(CamTrapDB);
    QString query = "SELECT * FROM " + table + query_c;
    *qry = CamTrapDB.exec(query);

    if(!qry->lastError().isValid())
    {
        while(qry->next())
        {
            value = qry->value(qrycolumn).toString();
            values << value;
        }
    }
    else
        QMessageBox::critical(nullptr, "VERI TABANI HATASI", qry->lastError().text());

    delete qry;
    qry = nullptr;

    return values;
}

QList<QString> DatabaseConnector::whereDB(QString table, unsigned short int qrycolumn, QMap<QString, QString> where_map)
{
    QList<QString> values;
    QString value = "";
    QSqlQuery *qry = new QSqlQuery(CamTrapDB);
    QString query = "SELECT * FROM " + table + " WHERE ";

    foreach(QString key, where_map.keys())
    {
        query+=key;
        query+="='";
        query+=where_map[key];
        query+="'";
        if(key != where_map.lastKey())
            query+=" AND ";
    }
    *qry = CamTrapDB.exec(query);

    if(!qry->lastError().isValid())
    {
        while(qry->next())
        {
            value = qry->value(qrycolumn).toString();
            values << value;
        }
    }
    else
        QMessageBox::critical(nullptr, "VERI TABANI HATASI", qry->lastError().text());

    delete qry;
    qry = nullptr;

    return values;
}

bool DatabaseConnector::insertDB(QString table,  QList<QString> columnlist, QList<QString> valuelist)
{
    bool result = false;
    QSqlQuery *qry = new QSqlQuery(CamTrapDB);
    QString query = "INSERT INTO " + table + "(";
    query = setQuery(query, columnlist, valuelist);
    *qry = CamTrapDB.exec(query);

    if(!qry->lastError().isValid())
    {
        QMessageBox::information(nullptr, "ISLEM MESAJI", "Ekleme Islemi Tamamlandi!");
        result = true;
    }
    else
        QMessageBox::critical(nullptr, "VERI TABANI HATASI", qry->lastError().text());

    delete qry;
    qry = nullptr;

    return result;
}

bool DatabaseConnector::updateDB(QString table, QMap<QString, QString> set_map, QMap<QString, QString> where_map)
{
    bool result = false;
    QSqlQuery *qry = new QSqlQuery(CamTrapDB);
    QString query = "UPDATE " + table + " SET ";
    query = setQuery(query, set_map, where_map);
    *qry = CamTrapDB.exec(query);

    if(!qry->lastError().isValid())
    {
        QMessageBox::information(nullptr, "ISLEM MESAJI", "Guncelleme Islemi Tamamlandi!");
        result = true;
    }
    else
        QMessageBox::critical(nullptr, "VERI TABANI HATASI", qry->lastError().text());

    delete qry;
    qry = nullptr;

    return result;
}

bool DatabaseConnector::deleteDB(QString table, QString column, QString item)
{
    bool result = false;
    QSqlQuery *qry = new QSqlQuery(CamTrapDB);
    QString query = "DELETE FROM " + table + " WHERE " + column + "='" + item + "'";
    *qry = CamTrapDB.exec(query);

    QString infomsg = "Secilen " + item + " Silindi!";

    if(!qry->lastError().isValid())
    {
        QMessageBox::information(nullptr, "ISLEM MESAJI", infomsg);
        result = true;
    }
    else
        QMessageBox::critical(nullptr, "VERI TABANI HATASI", qry->lastError().text());

    delete qry;
    qry = nullptr;

    return result;
}
