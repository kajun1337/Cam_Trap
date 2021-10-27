#include "ctmainwindow.h"

#include <QApplication>
#include"databaseconnector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CTMainWindow w;
    w.show();

    DatabaseConnector* connection=new DatabaseConnector();

    delete connection;

    return a.exec();

}
