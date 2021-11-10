#ifndef CTMAINWINDOW_H
#define CTMAINWINDOW_H

#include "imageform.h"
#include "databaseconnector.h"

#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QMap>
#include <QSharedPointer>
#include <QDebug>
#include <QDesktopServices>

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
    void on_pushButton_leave_select_clicked();
    void on_commandLinkButton_uf_clicked();
    void on_commandLinkButton_un_clicked();
    void on_lineEdit_mu_s_editingFinished();

private:
    Ui::CTMainWindow *ui;
    QList<QString> photo_info;
    QList<QString> select_photo_info;
    QString file_path;
    QList<ImageForm *> photos;
    unsigned int page_id;
    bool select;

private:
    void setCentralWidget();
    void setMainFrame();
    void setMenuFrame();
    void setComboBoxCamera(QList<QString> camlist);
    void setComboxAnimal(QList<QString> anmlist);
    void setGridLayout();
    void setPhotoInfo();
    bool checkFolderPath();
    QString setPhotoName();
};
#endif // CTMAINWINDOW_H
