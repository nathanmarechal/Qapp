#ifndef SECONDVIEW_H
#define SECONDVIEW_H

#include <QWidget>
#include <QLabel>

class SecondView : public QWidget
{
    Q_OBJECT

public:
    explicit SecondView(QWidget *parent = nullptr);
};

#endif
