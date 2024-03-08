#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow; // Créez une instance de MainWindow
    mainWindow.show(); // Affichez-la

    return app.exec(); // Lancez la boucle d'événements
}
