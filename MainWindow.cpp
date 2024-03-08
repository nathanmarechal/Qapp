#include "MainWindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this); // Créer le QStackedWidget
    setCentralWidget(stackedWidget); // Définir comme widget central de QMainWindow

    // Créer les vues
    QWidget *mainView = new QWidget(); // Vue principale
    secondView = new SecondView(); // Vue secondaire

    // Ajouter les vues au QStackedWidget
    stackedWidget->addWidget(mainView);
    stackedWidget->addWidget(secondView);

    // Ici, vous pouvez configurer votre mainView comme vous le souhaitez
    // Exemple : Ajouter un bouton pour basculer vers secondView
    QPushButton *switchViewButton = new QPushButton("Switch to Second View", mainView);
    connect(switchViewButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(secondView);
    });
}
