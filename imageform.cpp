#include "imageform.h"
#include "ui_imageform.h"

ImageForm::ImageForm(QWidget *parent,  QList<QString> photo_info) :
    QWidget(parent),
    ui(new Ui::ImageForm)
{
    photo_infos = photo_info;
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
    setPhotoFrame();
    setSettingFrame();
}

void ImageForm::setPhotoFrame()
{
    QString name = "", photo_p = photo_infos.at(3);
    QPixmap photo;
    photo.load(photo_p);
    for(unsigned short int i = photo_p.length() - 1; i > 0; i--)
    {
        if(photo_p[i] != '/')
            name.push_front(photo_p[i]);
        else
            break ;
    }
    photo_name = name;
    ui->photo->setPixmap(photo);
    ui->photo_name->setText(name);
}

void ImageForm::setNoteFrame()
{

}

void ImageForm::setSettingFrame()
{
    ui->label_n->setText(photo_name);
    ui->label_d->setText(photo_infos.at(2));
    ui->label_c->setText(photo_infos.at(1));
    ui->label_an->setText(photo_infos.at(4));
    ui->label_l_d->setText(photo_infos.at(7));
    ui->label_fav->setText(photo_infos.at(5));
    ui->label_1f->setText(photo_infos.at(3));
}

void ImageForm::setComboBoxCamera(QList<QString> camlist)
{
    ui->comboBox_sc->addItems(camlist);
}

void ImageForm::setComboxAnimal(QList<QString> anmlist)
{
    ui->comboBox_sca->addItems(anmlist);
}


void ImageForm::on_pushButton_sc_b_clicked()
{
    //Cahnge Photo Infos
    QMap<QString, QString> set_map, where_map;
    set_map.insert("Tarih", ui->dateEdit_sd->date().toString());
    set_map.insert("MakineAdi", ui->comboBox_sc->currentText());
    set_map.insert("HayvanAdi", ui->comboBox_sca->currentText());
    set_map.insert("Konum", ui->lineEdit_sc_l->text());
    QString photoName = photo_name;
    QString msg_text = "Secilen Fotograf: " + photoName + " Guncellensin mi?";
    where_map.insert("FotografID", photo_infos.at(0));
    QMessageBox::StandardButton res = QMessageBox::question(nullptr, "Fotograf Guncelleme İslemi", msg_text,
                                                            QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        DatabaseConnector *db = new DatabaseConnector();

        db->updateDB("fotograflar", set_map, where_map);

        delete  db;
        db = nullptr;
        //Reset Photo infos
    }
    else
        return ;
}


void ImageForm::on_pushButton_clicked()
{
    //Delete Photo actions
    QString msg_text = "Secilen Fotograf: " + photo_name + " Silinsin mi?";
    QMessageBox::StandardButton res = QMessageBox::question(nullptr, "Fotograf Silme İslemi", msg_text,
                                                            QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        DatabaseConnector *db = new DatabaseConnector();

        db->deleteDB("Fotograflar", "FotografID", photo_infos.at(0));

        delete  db;
        db = nullptr;
    }
    else
        return ;
}


void ImageForm::on_commandLinkButton_pn_clicked()
{
    //Save Note
}


void ImageForm::on_pushButton_fav_clicked()
{
    //Add favorite to chosen photo
    QMap<QString, QString> set_map, where_map;
    QString msg_text = "";
    if(photo_infos.at(5) == "")
    {
        set_map.insert("Favori", "Evet");
        msg_text = "Secilen Fotograf: " + photo_name + " Favoriye Eklensin mi?";
    }
    else
    {
        set_map.insert("Favori", "");
        msg_text = "Secilen Fotograf: " + photo_name + " Favoriden Cikarilsin mi?";
    }
    where_map.insert("FotografID", photo_infos.at(0));
    QMessageBox::StandardButton res = QMessageBox::question(nullptr, "Fotograf Favori İslemi", msg_text,
                                                            QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        DatabaseConnector *db = new DatabaseConnector();

        db->updateDB("fotograflar", set_map, where_map);

        delete  db;
        db = nullptr;
        //Reset Photo infos
    }
    else
        return ;
}
