//
// Created by Utente on 23/12/2023.
//
#include "GUI.h"
#include <QVBoxLayout>
GUI::~GUI() {
    fl->removeObserver(this);
}

GUI::GUI(FileLoader *fl, QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("Laboratorio di Programmazione - 2023");
    this->setFixedSize(QSize(600, 400));

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Layout verticale per centrare la progress bar
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignCenter);

    // Creazione della QProgressBar
    QProgressBar *progressBar = new QProgressBar();
    progressBar->setFixedWidth(350); // Imposta una larghezza fissa desiderata
    progressBar->setRange(0, 100); // Imposta il range della progress bar
    progressBar->setAlignment(Qt::AlignCenter); // Allinea la progress bar al centro

    // Aggiunta della progress bar al layout
    layout->addWidget(progressBar);
}


void GUI::update() {
}

