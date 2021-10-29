#ifndef IMAGEFORM_H
#define IMAGEFORM_H

#include <QWidget>

namespace Ui {
class ImageForm;
}

class ImageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ImageForm(QWidget *parent = nullptr);
    ~ImageForm();

private slots:
    void on_pushButton_settings_clicked();

    void on_pushButton_edit_note_clicked();

private:
    Ui::ImageForm *ui;
};

#endif // IMAGEFORM_H
