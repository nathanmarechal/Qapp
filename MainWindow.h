#include <QMainWindow>
#include <QStackedWidget>
#include "SecondView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stackedWidget;
    SecondView *secondView;
};
