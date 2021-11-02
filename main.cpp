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
    w.show();

    return a.exec();

}
