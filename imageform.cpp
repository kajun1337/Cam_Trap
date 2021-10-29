#include "imageform.h"
#include "ui_imageform.h"

ImageForm::ImageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageForm)
{
    ui->setupUi(this);
    ui->frame_ps->hide();
    ui->frame_photo_notes->hide();
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

