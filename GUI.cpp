
#include "GUI.h"

GUI::~GUI() {
    fl->removeObserver(this);
    delete layout;
}

GUI::GUI(FileLoader *fl, QWidget *parent) : QMainWindow(parent), fl(fl) {
    this->setWindowTitle("Laboratorio di Programmazione - 2023");
    this->setFixedSize(QSize(550, 350));

    auto *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Layout verticale per la finestra
    layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignCenter);

    // Creazione dei pulsanti
    auto *chooseFilesButton = new QPushButton("Choose File", centralWidget);
    auto *submitButton = new QPushButton("Submit", centralWidget);

    // Creazione della QProgressBar
    progressBar = new QProgressBar();
    progressBar->setFixedWidth(350);
    progressBar->setRange(0, 100);
    progressBar->setAlignment(Qt::AlignCenter);

    // Aggiunta dei pulsanti al layout principale
    layout->addWidget(chooseFilesButton);
    layout->addWidget(progressBar);
    layout->addWidget(submitButton);

    // Connessione dei pulsanti ai rispettivi slot
    connect(chooseFilesButton, &QPushButton::clicked, this, &GUI::openFileDialog);
    connect(submitButton, &QPushButton::clicked, this, &GUI::submit);

    fl->addObserver(this);
}


void GUI::update(int value) {
    progressBar->setValue(value);

    if (value == 100) {
        QMessageBox::information(this, "Completed", "Loading completed!");

        // Resetta la progress bar e cancella i file scelti
        reset();
    }
}

void GUI::reset() {
    progressBar->setValue(0);
    selectedFiles.clear();

    // Rimuovi i widget QLabels dal layout
    QLayoutItem* child;
    while ((child = layout->takeAt(3)) != nullptr) {  // Inizia da index 3, poiché i widget cominciano da quel punto
        if (child->widget()) {
            delete child->widget();  // Dealloca la memoria occupata dai widget
        }
        delete child;  // Dealloca la memoria utilizzata per il layout item
    }
}

void GUI::openFileDialog() {
    QStringList fileNames = QFileDialog::getOpenFileNames(
            this,
            tr("Choose a file to load"),
            QDir::homePath(),
            tr("Text files only (*.txt)")
    );

    if (!fileNames.isEmpty()) {
        for (const QString& fileName : fileNames) {
            auto *fileLabel = new QLabel(fileName, this);
            layout->addWidget(fileLabel);
            selectedFiles.push_back(fileName);
        }
    }
}

void GUI::submit() {
    fl->load(selectedFiles);
}
