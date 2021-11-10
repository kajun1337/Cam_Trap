#ifndef IMAGEFORM_H
#define IMAGEFORM_H

#include "databaseconnector.h"

#include <QWidget>
#include <QWidget>
#include <QObject>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QPixmap>
#include <QList>
#include <QMap>
#include <QDebug>
#include <QDesktopServices>

namespace Ui {
class ImageForm;
}

class ImageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ImageForm(QWidget *parent = nullptr, QList<QString> photo_info = QList<QString> ());
    ~ImageForm();
    void setComboBoxCamera(QList<QString> camlist);
    void setComboxAnimal(QList<QString> anmlist);

private slots:
    void on_pushButton_settings_clicked();
    void on_pushButton_edit_note_clicked();
    void on_pushButton_sc_b_clicked();
    void on_pushButton_clicked();
    void on_commandLinkButton_pn_clicked();
    void on_pushButton_fav_clicked();
    void on_pushButton_maxi_clicked();

private:
    Ui::ImageForm *ui;
    QList<QString> photo_infos;

private:
    void setCentralWidget();
    void setPhotoFrame();
    void setNoteFrame();
    void setSettingFrame();
};

#endif // IMAGEFORM_H
