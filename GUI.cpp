
#include "GUI.h"

GUI::~GUI() {

    // Rimozione dell'istanza di GUI dalla lista degli osservatori nel fileLoader
    fl->removeObserver(this);

    // Deallocazione della memoria per i pulsanti
    delete chooseFilesButton;
    delete submitButton;

    // Deallocazione della memoria per la QProgressBar
    delete progressBar;

    // Deallocazione della memoria per i layout e i widget
    delete layout;
    delete filesLayout;
    delete filesContainer;
    delete scrollArea;

    // Rilascio della memoria per i QLabel creati in openFileDialog()
    QList<QLabel*> labels = findChildren<QLabel*>();
    for (QLabel* label : labels) {
        delete label;
    }
}

GUI::GUI(FileLoader *fileLoader, QWidget *parent) : QMainWindow(parent), fl(fileLoader) {
    // Impostazione nome e dimensione della finestra
    this->setWindowTitle("Laboratorio di Programmazione - 2023");
    this->setFixedSize(QSize(600, 350));

    // Creazione del widget centrale
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
    chooseFilesButton->setObjectName("chooseFilesButton");
    submitButton->setObjectName("submitButton");
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

    // Aggiunta dell'istanza di GUI come osservatore al fileLoader
    fl->addObserver(this);
}

void GUI::update() {
    // Aggiornamento del valore della QProgressBar
    progressBar->setValue(static_cast<int>(fl->getProgress()));
    if (fl->getProgress() == 100) {
        QMessageBox::information(this, "Completed", "Loading completed!");

        // Riabilitazione dei pulsanti dopo il caricamento completato
        if (chooseFilesButton && submitButton) {
            chooseFilesButton->setEnabled(true);
            submitButton->setEnabled(true);
        }
        // Resettare la progress bar e la scrollArea e cancella i file scelti
        reset();
    }
}

void GUI::reset() {
    // Resettare la QProgressBar e i file selezionati
    progressBar->setValue(0);
    selectedFiles.clear();

    // Rimozione dei widget dei file scelti
    QLayoutItem *child;
    while ((child = filesLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            QWidget *widget = child->widget();
            delete widget;
        }
        // Deallocazione della memoria utilizzata per il layout item
        delete child;
    }
}

void GUI::openFileDialog() {
    // Apertura di una finestra di dialogo per la selezione dei file
    QStringList fileNames = QFileDialog::getOpenFileNames(
            this,
            tr("Choose a file to load"),
            QDir::homePath(),
            tr("Text files only (*.txt)")
    );

    // Aggiunta etichette dei file selezionati all'area scrollabile
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
        // Cattura e gestiione dele eccezioni durante il caricamento
        qDebug() << "Exception captured: " << e.what();
    }
}

long long GUI::getSelectedFilesCount() const {
    // Restituzione del numero di file selezionati
    return selectedFiles.size();
}

int GUI::getProgressBarValue() const {
    // Restituzione iel valore attuale della QProgressBar
    if (progressBar) {
        return progressBar->value();
    } else {
        return 0;}
}

void GUI::setBarProgress(int value) {
    // Impostazione del valore della QProgressBar
    progressBar->setValue(value);
}
