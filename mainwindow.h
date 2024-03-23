#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void checkAnswer();
    void nextWord();
    void on_menuButton_clicked();

private:
    Ui::MainWindow *ui;
    QString currentWord;
    QStringList wordList = {
        "maison", "arbre", "fenêtre", "ordinateur", "livre", "tableau", "chaise", "école",
        "voiture", "avion", "chocolat", "bouteille", "téléphone", "lampe", "soleil", "lune",
        "étoile", "ciel", "fleur", "oiseau", "chat", "chien", "poisson", "papillon", "abeille",
        "fourmi", "lion", "tigre", "ours", "serpent", "pomme", "banane", "orange", "raisin",
        "fraise", "cerise", "melon", "courgette", "carotte", "tomate", "pomme de terre", "oignon",
        "ail", "poireau", "brocoli", "chou", "salade", "concombre", "poivron", "haricot",
        "lait", "fromage", "beurre", "yaourt", "glace", "gâteau", "pain", "croissant", "chocolatine",
        "café", "thé", "jus", "eau", "vin", "bière", "cocktail", "whisky", "vodka", "rhum",
        "soda", "sport", "football", "basketball", "tennis", "golf", "natation", "danse", "musique",
        "guitare", "piano", "violon", "batterie", "flûte", "saxophone", "trompette", "clarinette",
        "peinture", "dessin", "sculpture", "cinéma", "théâtre", "livre", "roman", "poésie", "bande dessinée",
        "histoire", "géographie", "mathématiques", "physique", "biologie", "chimie", "philosophie", "psychologie"
    };
    int score = 0;
    void generateWord();
    void updateScore(int points);
};
#endif // MAINWINDOW_H
