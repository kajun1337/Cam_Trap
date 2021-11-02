#include "imageform.h"
#include "ui_imageform.h"

ImageForm::ImageForm(QWidget *parent, QString imageid) :
    QWidget(parent),
    ui(new Ui::ImageForm)
{
    id = imageid;
    ui->setupUi(this);
    setCentralWidget();
}

ImageForm::~ImageForm()
{
    delete ui;
}

void ImageForm::on_pushButton_settings_clicked()
{
    ui->frame_ps->setVisible(ui->pushButton_settings->isChecked());
}


void ImageForm::on_pushButton_edit_note_clicked()
{
    ui->frame_photo_notes->setVisible(ui->pushButton_edit_note->isChecked());
}

void ImageForm::setCentralWidget()
{
    ui->frame_ps->hide();
    ui->frame_photo_notes->hide();
    //setPhotoFrame();
}

void ImageForm::setPhotoFrame()
{
    /*
    //QPixmap photo;
    //photo.load(photo_p);
    for(unsigned short int i = photo_p.length() - 1; i > 0; i--)
    {
        if(photo_p[i] != '/')
            name.push_front(photo_p[i]);
        else
            break ;
    }
    qInfo() << photo_p << name;
    //ui->photo->setPixmap(photo);
    //ui->photo_name->setText(name);*/
}

void ImageForm::setNoteFrame()
{

}

void ImageForm::setSettingFrame()
{

}

void ImageForm::setComboBoxCamera(QList<QString> camlist)
{

}

void ImageForm::setComboxAnimal(QList<QString> anmlist)
{

}

