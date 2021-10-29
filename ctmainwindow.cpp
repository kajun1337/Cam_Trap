#include "ctmainwindow.h"
#include "./ui_ctmainwindow.h"

CTMainWindow::CTMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CTMainWindow)
{
    ImageForm *imageui = new ImageForm;

    ui->setupUi(this);
    ui->menu_frame->hide();
    ui->user_frame->hide();
    ui->gridLayout->addWidget(imageui, 0, 0);
}

CTMainWindow::~CTMainWindow()
{
    delete ui;
}


void CTMainWindow::on_pushButton_mu_mb_clicked()
{
    ui->menu_frame->setVisible(ui->pushButton_mu_mb->isChecked());
}

void CTMainWindow::on_pushButton_mu_ub_clicked()
{
    ui->user_frame->setVisible(ui->pushButton_mu_ub->isChecked());
}

