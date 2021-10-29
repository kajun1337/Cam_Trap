#ifndef CTMAINWINDOW_H
#define CTMAINWINDOW_H

#include "imageform.h"

#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QBoxLayout>
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

private:
    Ui::CTMainWindow *ui;
};
#endif // CTMAINWINDOW_H
