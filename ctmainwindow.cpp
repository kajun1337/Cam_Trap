#include "ctmainwindow.h"
#include "./ui_ctmainwindow.h"

CTMainWindow::CTMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CTMainWindow)
{
    page_id = 1;
    select = false;
    ui->setupUi(this);
    setCentralWidget();
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

void CTMainWindow::setCentralWidget()
{
    ui->menu_frame->hide();
    ui->user_frame->hide();

    setMenuFrame();
    setMainFrame();

    ui->label_pg->setText(QString::number(page_id));
    ui->pushButton_leave_select->hide();
}

void CTMainWindow::setPhotoInfo()
{
    unsigned int limit_min = (page_id == 1) ? 0 : (page_id - 1) * 8;
    unsigned int limit_max = (page_id == 1) ? 8 : (page_id + 1) * 8;
    if(select)
    {
        photo_info.clear();
        for(int i = limit_min; i < limit_max; i++)
        {
            if(!select_photo_info.value(i).isNull())
            {
                photo_info.append(select_photo_info.value(i));
            }
            else
                return ;
        }
    }
    else
    {
        DatabaseConnector *db = new DatabaseConnector();
        QString query_c = " LIMIT " + QString::number(limit_min) + "," + QString::number(limit_max);
        photo_info.clear();
        photo_info = db->selectDB("Fotograflar", 0, query_c);
        delete db;
        db = nullptr;
    }
}

bool CTMainWindow::checkFolderPath()
{
    bool result = false;
    QMap<QString, QString> where_map;
    where_map.insert("FotoVeriYolu", file_path);
    DatabaseConnector *db = new DatabaseConnector();
    if(db->whereDB("Fotograflar", 0, where_map).isEmpty())
    {
        result = true;
    }
    else
        QMessageBox::critical(this, "HATA", "Secilen Dosya Zaten Kayitli!");

    delete db;
    db = nullptr;

    return result;
}

QString CTMainWindow::setPhotoName()
{
    QString photo_name = "";

    for(unsigned short int i = file_path.length() - 1; i > 0; i--)
    {
        if(file_path[i] != '/')
            photo_name.push_front(file_path[i]);
        else
            break ;
    }

    return photo_name;
}

void CTMainWindow::setMainFrame()
{
    //Set the main frame add the photos into gridLayout
    setPhotoInfo();
    if(!photo_info.isEmpty())
    {
        setGridLayout();
    }
    else
        return ;
}

void CTMainWindow::setMenuFrame()
{
    ui->dateEdit_ap_df->setDate(QDate::currentDate());
    ui->dateEdit_pp_df->setDate(QDate::currentDate());

    DatabaseConnector *db = new DatabaseConnector();
    setComboBoxCamera(db->selectDB("Makineler", 1, ""));
    setComboxAnimal(db->selectDB("Hayvanlar", 1, ""));
    delete db;
    db = nullptr;
}

void CTMainWindow::setComboBoxCamera(QList<QString> camlist)
{
    ui->comboBox_pp_cf->addItems(camlist);
    ui->comboBox_ap_cf->addItems(camlist);
    ui->comboBox_cs_cc_cc->addItems(camlist);
    ui->comboBox_ap_cf_2->addItems(camlist);
}

void CTMainWindow::setComboxAnimal(QList<QString> anmlist)
{
    ui->comboBox_pp_af->addItems(anmlist);
    ui->comboBox_ap_af->addItems(anmlist);
    ui->comboBox_ra->addItems(anmlist);
}

void CTMainWindow::setGridLayout()
{
    unsigned short int c = 0;

    qDeleteAll(photos);
    photos.clear();

    for (int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(photo_info.length() > c)
            {
                DatabaseConnector *db = new DatabaseConnector();
                QList<QString> photo_infos = db->selectAllDB("Fotograflar", " WHERE FotografID='" +
                                                             photo_info.at(c) + "'", 9);
                ImageForm *imageui = new ImageForm(this, photo_infos);
                photos.append(imageui);
                imageui->setComboBoxCamera(db->selectDB("Makineler", 1, ""));
                imageui->setComboxAnimal(db->selectDB("Hayvanlar", 1, ""));
                ui->gridLayout->addWidget(imageui, i, j);
                delete db;
                db = nullptr;
                c++;
            }
            else
                return ;
        }
    }
}

void CTMainWindow::on_commandLinkButton_tb_pp_clicked()
{
    //Filter button
    QMap<QString, QString> where_map;
    QString msg_text = "Yapilan Secimlere Gore Filtre Uygulansin mi?";
    QMessageBox::StandardButton res = QMessageBox::question(this, "Fotograf Filtreleme İslemi", msg_text,
                                                            QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        DatabaseConnector *db = new DatabaseConnector();
        where_map.insert("MakineAdi", ui->comboBox_pp_cf->currentText());
        where_map.insert("Tarih", ui->dateEdit_pp_df->date().toString());
        where_map.insert("HayvanAdi", ui->comboBox_pp_af->currentText());
        where_map.insert("Konum", ui->lineEdit_tb_pp_lf->text());

        select_photo_info.clear();
        select_photo_info = db->whereDB("Fotograflar", 0, where_map);

        delete db;
        db = nullptr;
        //Set the main frame
        if(!select_photo_info.isEmpty())
        {
            select = true;
            page_id = 1;
            ui->label_pg->setText(QString::number(page_id));
            ui->pushButton_leave_select->setVisible(true);
            setMainFrame();
        }
        else
            QMessageBox::critical(this, "HATA", "Secilen Ozelliklerde Fotograf(lar) Bulunamadi!");
    }
    else
        return ;
}

void CTMainWindow::on_commandLinkButton_tb_ap_clicked()
{
    //Add a new photo button
    QList<QString> column_ap, item_ap;
    column_ap << "FotoAdi" << "MakineAdi" << "Tarih" << "FotoVeriYolu" <<
                "HayvanAdi" << "Konum";
    QString msg_text = "Secilen Fotograf: " + file_path + " Eklensin mi?";
    QMessageBox::StandardButton res = QMessageBox::question(this, "Fotograf Ekleme İslemi", msg_text,
                                                            QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        if(file_path != "")
        {
            item_ap.append(setPhotoName());
            item_ap.append(ui->comboBox_ap_cf->currentText());
            item_ap.append(ui->dateEdit_ap_df->date().toString());
            item_ap.append(file_path);
            item_ap.append(ui->comboBox_ap_af->currentText());
            item_ap.append(ui->lineEdit_tb_ap_al->text());
            //Insert photo to DB
            DatabaseConnector *db = new DatabaseConnector();
            if(db->insertDB("Fotograflar", column_ap, item_ap))      
            {
                setMainFrame();
                file_path = "";
                ui->label_ap_f->setText(file_path);               
            }
            delete db;
            db = nullptr;
        }
        else
            QMessageBox::critical(this, "HATA", "Dosya Secimi Yapilmali!");
    }
    else
        return ;
}

void CTMainWindow::on_commandLinkButton_cs_cc_cc_clicked()
{
    //Change the info of chosen camera button (Update the camera info)
    QMap<QString, QString> set_map, where_map;
    QString cb_text = ui->comboBox_cs_cc_cc->currentText();
    unsigned int cb_index = ui->comboBox_cs_cc_cc->currentIndex();
    QString msg_text = "Secilen Makine: " + cb_text + " Guncellensin mi?";
    where_map.insert("MakineAdi", cb_text);
    QMessageBox::StandardButton res = QMessageBox::question(this, "Makine Guncelleme İslemi", msg_text,
                                                            QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        if(ui->lineEdit_cs_cc_cc->text() != "")
        {
            set_map.insert("MakineAdi", ui->lineEdit_cs_cc_cc->text());
            set_map.insert("MakineKonum", ui->lineEdit_cs_cc_cl->text());
            //Update camera from DB
            DatabaseConnector *db = new DatabaseConnector();
            if(db->updateDB("Makineler", set_map, where_map))
            {
                //Remove old camera name camera comboBoxes
                ui->comboBox_pp_cf->removeItem(cb_index);
                ui->comboBox_ap_cf->removeItem(cb_index);
                ui->comboBox_cs_cc_cc->removeItem(cb_index);
                ui->comboBox_ap_cf_2->removeItem(cb_index);
                //Add new camera name to camera comboBoxes
                ui->comboBox_pp_cf->addItem(ui->lineEdit_cs_cc_cc->text());
                ui->comboBox_ap_cf->addItem(ui->lineEdit_cs_cc_cc->text());
                ui->comboBox_cs_cc_cc->addItem(ui->lineEdit_cs_cc_cc->text());
                ui->comboBox_ap_cf_2->addItem(ui->lineEdit_cs_cc_cc->text());
            }
            delete db;
            db = nullptr;
        }
        else
            QMessageBox::critical(this, "HATA", "Kamera Adi Bos Olmamali!");
    }
    else
        return ;
}

void CTMainWindow::on_commandLinkButton_ac_clicked()
{
    //Add a new camera button
    QList<QString> column_a, item_a;
    column_a << "MakineAdi" << "MakineKonum";

    if(ui->lineEdit_cam_name->text() != "")
    {
        item_a.append(ui->lineEdit_cam_name->text());
        item_a.append(ui->lineEdit_cs_ac_al->text());
        //Insert to DB
        DatabaseConnector *db = new DatabaseConnector();
        if(db->insertDB("Makineler", column_a, item_a))
        {
             ui->comboBox_pp_cf->addItem(ui->lineEdit_cam_name->text());
             ui->comboBox_ap_cf->addItem(ui->lineEdit_cam_name->text());
             ui->comboBox_cs_cc_cc->addItem(ui->lineEdit_cam_name->text());
             ui->comboBox_ap_cf_2->addItem(ui->lineEdit_cam_name->text());
        }
        delete db;
        db = nullptr;
    }
    else
        QMessageBox::critical(this, "HATA", "Kamera Adi Bos Olmamali!");
}

void CTMainWindow::on_commandLinkButton_rc_clicked()
{
    //Delete the chosen camera button
    unsigned int cb_index = ui->comboBox_ap_cf_2->currentIndex();
    QString cb_text = ui->comboBox_ap_cf_2->currentText();
    QString msg_text = "Secilen Makine: " + cb_text + " Silinsin mi?";
    QMessageBox::StandardButton res = QMessageBox::question(this, "Makine Silme İslemi", msg_text,
                                                            QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        //Delete from db
        DatabaseConnector *db = new DatabaseConnector();
        if(db->deleteDB("Makineler", "MakineAdi", cb_text))
        {
            ui->comboBox_pp_cf->removeItem(cb_index);
            ui->comboBox_ap_cf->removeItem(cb_index);
            ui->comboBox_cs_cc_cc->removeItem(cb_index);
            ui->comboBox_ap_cf_2->removeItem(cb_index);
        }
        delete db;
        db = nullptr;
    }
    else
        return ;
}

void CTMainWindow::on_commandLinkButton_aa_clicked()
{
    //Add a new animal button
    QList<QString> column_a, item_a;
    column_a << "HayvanAdi";

    if(ui->lineEdit_an->text() != "")
    {
        item_a.append(ui->lineEdit_an->text());
        //Insert to DB
        DatabaseConnector *db = new DatabaseConnector();
        if(db->insertDB("Hayvanlar", column_a, item_a))
        {
             ui->comboBox_pp_af->addItem(ui->lineEdit_an->text());
             ui->comboBox_ap_af->addItem(ui->lineEdit_an->text());
             ui->comboBox_ra->addItem(ui->lineEdit_an->text());
        }
        delete db;
        db = nullptr;
    }
    else
        QMessageBox::critical(this, "HATA", "Hayvan Adi Bos Olmamali!");

}

void CTMainWindow::on_commandLinkButton_ra_clicked()
{
    //Delete the chosen animal button
    unsigned int cb_index = ui->comboBox_ra->currentIndex();
    QString cb_text = ui->comboBox_ra->currentText();
    QString msg_text = "Secilen Hayvan: " + cb_text + " Silinsin mi?";
    QMessageBox::StandardButton res = QMessageBox::question(this, "Hayvan Silme İslemi", msg_text,
                                                            QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        //Delete from db
        DatabaseConnector *db = new DatabaseConnector();
        if(db->deleteDB("Hayvanlar", "HayvanAdi", cb_text))
        {
            ui->comboBox_pp_af->removeItem(cb_index);
            ui->comboBox_ap_af->removeItem(cb_index);
            ui->comboBox_ra->removeItem(cb_index);
        }
        delete db;
        db = nullptr;
    }
    else
        return ;
}

void CTMainWindow::on_pushButton_ap_ff_clicked()
{
    //Open the file dialog button
    file_path = QFileDialog::getOpenFileName(this, "Resim Secimi", "C://", "Resim Dosyalari (*.png *.jpg *.bmp)");
    if(checkFolderPath())
        ui->label_ap_f->setText(file_path);
    else
        file_path = "";
}

void CTMainWindow::on_pushButton_pg_bb_clicked()
{
    //Page back button
    if(page_id != 1)
    {
        page_id--;
        setMainFrame();
        ui->label_pg->setText(QString::number(page_id));
    }
    else
        return ;
}

void CTMainWindow::on_pushButton_pg_fb_clicked()
{
    //Page forward button
    page_id++;
    setMainFrame();
    if(photo_info.isEmpty())
    {
        page_id--;
    }
    ui->label_pg->setText(QString::number(page_id));
}

void CTMainWindow::on_pushButton_leave_select_clicked()
{
    //Leave the Selection Filter Frame
    page_id = 1;
    ui->label_pg->setText(QString::number(page_id));
    ui->pushButton_leave_select->hide();
    select = false;
    setMainFrame();
}

void CTMainWindow::on_commandLinkButton_uf_clicked()
{
    //Filter the favorite photos
    QMap<QString, QString> where_map;
    where_map.insert("Favori", "Evet");

    DatabaseConnector *db = new DatabaseConnector();
    select_photo_info.clear();
    select_photo_info = db->whereDB("Fotograflar", 0, where_map);

    delete db;
    db = nullptr;
    //Set the main frame
    if(!select_photo_info.isEmpty())
    {
        select = true;
        page_id = 1;
        ui->label_pg->setText(QString::number(page_id));
        ui->pushButton_leave_select->setVisible(true);
        setMainFrame();
    }
    else
        QMessageBox::critical(this, "HATA", "Secilen Ozelliklerde Fotograf(lar) Bulunamadi!");
}

void CTMainWindow::on_commandLinkButton_un_clicked()
{
    //Show the Notes Directory
    QDesktopServices::openUrl(QUrl::fromLocalFile("../Cam_Trap/Notlar"));
}

void CTMainWindow::on_lineEdit_mu_s_editingFinished()
{
    //Search the lineEdit Text in the DB
    QMap<QString, QString> where_map;
    where_map.insert("FotoAdi", ui->lineEdit_mu_s->text());

    DatabaseConnector *db = new DatabaseConnector();
    select_photo_info.clear();
    select_photo_info = db->whereDB("Fotograflar", 0, where_map);

    delete db;
    db = nullptr;
    //Set the main frame
    if(!select_photo_info.isEmpty())
    {
        select = true;
        page_id = 1;
        ui->label_pg->setText(QString::number(page_id));
        ui->pushButton_leave_select->setVisible(true);
        setMainFrame();
    }
    else
        QMessageBox::critical(this, "HATA", "Girilen Isimde Fotograf Bulunamadi!");
}

