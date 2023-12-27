
#include "FileLoader.h"

FileLoader::FileLoader(QObject* parent) : QObject(parent), filesNumber(0), progress(0) {}

void FileLoader::addObserver(Observer *o) {
    // Aggiunta di un osservatore alla lista degli osservatori
    observers.push_back(o);
}

void FileLoader::removeObserver(Observer *o) {
    // Rimozione di un osservatore alla lista degli osservatori
    observers.removeAll(o);
}

void FileLoader::notifyObservers() {
    // Notifica a tutti gli osservatori registrati chiamando il loro metodo 'update'
    for(Observer* observer : observers)
        observer->update();
}

void FileLoader::load(const QVector<QString>& files) {
    // Caricamento dei file e aggiornamento del progresso
    long long  totalSize = 0;
    setProgress(0);

    // Calcolo della dimensione totale dei file
    for (const QString& filePath : files) {
        // Verifica dell'esistenza e del formato dei file
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists() || fileInfo.suffix().toLower() != "txt") {
            continue;
        }
        // Aggiunta della dimensione del file alla dimensione totale
        totalSize += fileInfo.size();
    }

    // Impostazione iel numero totale di file
    filesNumber = files.size();
    long long  loadedSize = 0;

    // Caricamento dei file e aggiornamento del progresso
    for (const QString& filePath : files) {
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists() || fileInfo.suffix().toLower() != "txt") {
            // Solleva un'eccezione se il file non esiste o non ha il formato .txt
            throw std::runtime_error("File not found or non .txt: " + filePath.toStdString());
        }

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // Lettura del contenuto del file e aggiornamento del progresso
            while (!file.atEnd()) {
                QByteArray line = file.readLine() + 1;
                loadedSize += line.size();
                setProgress((loadedSize * 100) / totalSize);
                notifyObservers();
            }
            // Chiusura file dopo averlo letto
            file.close();
        }else{
            // Solleva un'eccezione se il file non può essere aperto
            throw std::runtime_error("File can not be opened: " + filePath.toStdString());
        }
    }
}

long long FileLoader::getProgress() const {
    // Restituzione del valore progress
    return progress;
}

void FileLoader::setProgress(long long value) {
    // Impostazione del valore progress
    progress = value;
}
