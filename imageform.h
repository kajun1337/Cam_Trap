#ifndef IMAGEFORM_H
#define IMAGEFORM_H

#include "databaseconnector.h"

#include <QWidget>
#include <QWidget>
#include <QObject>
#include <QMessageBox>
#include <QFile>
#include <QPixmap>
#include <QList>
#include <QMap>
#include <QDebug>

namespace Ui {
class ImageForm;
}

class ImageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ImageForm(QWidget *parent = nullptr, QString imageid = "");
    ~ImageForm();

private slots:
    void on_pushButton_settings_clicked();

    void on_pushButton_edit_note_clicked();

private:
    Ui::ImageForm *ui;
    QString id;

private:
    void setCentralWidget();
    void setPhotoFrame();
    void setNoteFrame();
    void setSettingFrame();
    void setComboBoxCamera(QList<QString> camlist);
    void setComboxAnimal(QList<QString> anmlist);
};

#endif // IMAGEFORM_H
