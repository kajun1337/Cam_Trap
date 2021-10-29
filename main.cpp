#include "databaseconnector.h"
#include "ctmainwindow.h"
#include "imageform.h"

#include <QApplication>
#include <QtWidgets>
#include <QSharedPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CTMainWindow w;
    DatabaseConnector *connection = new DatabaseConnector();

    w.show();

    delete connection;

    return a.exec();

}
