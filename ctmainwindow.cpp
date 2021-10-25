#include "ctmainwindow.h"
#include "./ui_ctmainwindow.h"

CTMainWindow::CTMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CTMainWindow)
{
    ui->setupUi(this);
}

CTMainWindow::~CTMainWindow()
{
    delete ui;
}

