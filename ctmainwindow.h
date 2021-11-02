#ifndef CTMAINWINDOW_H
#define CTMAINWINDOW_H

#include "imageform.h"
#include "databaseconnector.h"

#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QMap>
#include <QSharedPointer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class CTMainWindow; }
QT_END_NAMESPACE

class CTMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CTMainWindow(QWidget *parent = nullptr);
    ~CTMainWindow();

private slots:
    void on_pushButton_mu_mb_clicked();

    void on_pushButton_mu_ub_clicked();

    void on_commandLinkButton_tb_pp_clicked();

    void on_commandLinkButton_tb_ap_clicked();

    void on_commandLinkButton_cs_cc_cc_clicked();

    void on_commandLinkButton_ac_clicked();

    void on_commandLinkButton_rc_clicked();

    void on_commandLinkButton_aa_clicked();

    void on_commandLinkButton_ra_clicked();

    void on_pushButton_ap_ff_clicked();

    void on_pushButton_pg_bb_clicked();

    void on_pushButton_pg_fb_clicked();

private:
    Ui::CTMainWindow *ui;
    DatabaseConnector *db = new DatabaseConnector();
    QList<QString> photo_info = QList<QString> ();
    QString file_path = "";
    unsigned int page_id;

private:
    void setCentralWidget();
    void setMainFrame();
    void setMenuFrame();
    void setUserFrame();
    void setComboBoxCamera(QList<QString> camlist);
    void setComboxAnimal(QList<QString> anmlist);
    void setGridLayout();
};
#endif // CTMAINWINDOW_H
