#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QObject>

class DatabaseConnector : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseConnector(QObject *parent = nullptr);

signals:

};

#endif // DATABASECONNECTOR_H
