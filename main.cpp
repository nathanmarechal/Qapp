//
// Created by timon on 08/02/24.
//

#include <QApplication>
#include <QPushButton>

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);

    QPushButton button;
    QFont font("Courier");
    QIcon icon(QIcon::fromTheme("face_smile"));
    button.setText("hello world");
    button.setToolTip("un tooltip");
    button.setFont(font);
    button.setIcon(icon);
    button.show();

    return app.exec();
}