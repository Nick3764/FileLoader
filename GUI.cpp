
#include "GUI.h"

GUI::~GUI() {
    fl->removeObserver(this);
}

GUI::GUI(FileLoader *fileLoader, QWidget *parent) : QMainWindow(parent), fl(fileLoader) {
    this->setWindowTitle("Laboratorio di Programmazione - 2023");
    this->setFixedSize(QSize(600, 350));

    auto *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Titolo sopra la progress bar
    auto *titleLabel = new QLabel("Caricamento file di risorse e <br>aggiornamento di una progress bar", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont font("Arial", 25, QFont::Bold);
    titleLabel->setFont(font);

    // Spazio tra il titolo e la progress bar
    auto *spacer = new QSpacerItem(1, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

    // Layout verticale per il titolo
    auto *titleLayout = new QVBoxLayout();
    titleLayout->setAlignment(Qt::AlignTop);
    titleLayout->addItem(spacer);
    titleLayout->addWidget(titleLabel);
    titleLayout->addItem(spacer);

    // Creazione della QProgressBar
    progressBar = new QProgressBar();
    progressBar->setFixedWidth(350);
    progressBar->setRange(0, 100);
    progressBar->setAlignment(Qt::AlignCenter);

    // Creazione dei pulsanti
    chooseFilesButton = new QPushButton("Choose File", centralWidget);
    submitButton = new QPushButton("Submit", centralWidget);
    chooseFilesButton->setFixedWidth(172);
    submitButton->setFixedWidth(172);
    chooseFilesButton->setStyleSheet("QPushButton { background-color: grey; }");
    submitButton->setStyleSheet("QPushButton { background-color: blue; }");

    // Layout orizzontale per i pulsanti
    auto *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignCenter);
    buttonsLayout->addWidget(chooseFilesButton);
    buttonsLayout->addWidget(submitButton);

    // Layout verticale per la progress bar e i pulsanti
    auto *progressLayout = new QVBoxLayout();
    progressLayout->setAlignment(Qt::AlignCenter);
    progressLayout->addWidget(progressBar);
    progressLayout->addLayout(buttonsLayout);

    // Creazione dell'area scrollabile contenente le etichette dei file selezionati
    filesContainer = new QWidget();
    filesLayout = new QVBoxLayout(filesContainer);
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(filesContainer);
    scrollArea->setStyleSheet("background-color: white;");

    // Layout principale della finestra
    layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignTop);
    layout->addLayout(titleLayout);
    layout->addLayout(progressLayout);
    layout->addWidget(scrollArea);

    // Connessione dei pulsanti ai rispettivi slot
    connect(chooseFilesButton, &QPushButton::clicked, this, &GUI::openFileDialog);
    connect(submitButton, &QPushButton::clicked, this, &GUI::submit);

    fl->addObserver(this);
}

void GUI::update() {
    progressBar->setValue(static_cast<int>(fl->getProgress()));
    if (fl->getProgress() == 100) {
        QMessageBox::information(this, "Completed", "Loading completed!");

        // Riabilita i pulsanti dopo il caricamento completato
        if (chooseFilesButton && submitButton) {
            chooseFilesButton->setEnabled(true);
            submitButton->setEnabled(true);
        }
        // Resetta la progress bar e la scrollArea e cancella i file scelti
        reset();
    }
}

void GUI::reset() {
    progressBar->setValue(0);
    selectedFiles.clear();

    // Rimuove i widget dei file scelti
    QLayoutItem *child;
    while ((child = filesLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            QWidget *widget = child->widget();
            delete widget;
        }
        // Dealloca la memoria utilizzata per il layout item
        delete child;
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
            fileLabel->setStyleSheet("color: black;");
            filesLayout->addWidget(fileLabel);
            selectedFiles.push_back(fileName);
        }
    }
}

void GUI::submit() {
    try {
        // Disabilita i pulsanti durante il caricamento
        if (chooseFilesButton && submitButton) {
            chooseFilesButton->setEnabled(false);
            submitButton->setEnabled(false);

            fl->load(selectedFiles);
        }
    } catch(const std::exception& e) {
        qDebug() << "Exception captured: " << e.what();
    }
}

long long GUI::getSelectedFilesCount() const {
    return selectedFiles.size();
}

int GUI::getProgressBarValue() const {
    if (progressBar) {
        return progressBar->value();
    } else {
        return 0;}
}

void GUI::setBarProgress(int value) {
    progressBar->setValue(value);
}
