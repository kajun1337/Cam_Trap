#ifndef CTMAINWINDOW_H
#define CTMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CTMainWindow; }
QT_END_NAMESPACE

class CTMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CTMainWindow(QWidget *parent = nullptr);
    ~CTMainWindow();

private:
    Ui::CTMainWindow *ui;
};
#endif // CTMAINWINDOW_H
