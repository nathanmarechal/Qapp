#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_unscrambleGameButton_clicked();
    void on_flappyGameButton_clicked();

private:
    Ui::MenuWindow *ui;
};

#endif // MENUWINDOW_H
