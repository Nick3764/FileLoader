
#include "FileLoader.h"

FileLoader::FileLoader(QObject* parent) : QObject(parent), filesNumber(0) {}

void FileLoader::addObserver(Observer *o) {
    observers.push_back(o);
}

void FileLoader::removeObserver(Observer *o) {
    observers.removeAll(o);
}

void FileLoader::notifyObservers() {
    for(Observer* observer : observers)
        observer->update();
}

void FileLoader::load(const QVector<QString>& files) {
    long long  totalSize = 0;
    progress = 0;

    for (const QString& filePath : files) {
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists() || fileInfo.suffix().toLower() != "txt") {
            continue;
        }
        totalSize += fileInfo.size(); // Aggiungi la dimensione del file alla dimensione totale
    }

    //qDebug() << "Total Size:" << totalSize;
    filesNumber = files.size();
    long long  loadedSize = 0;

    for (const QString& filePath : files) {
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists() || fileInfo.suffix().toLower() != "txt") {
            continue;
        }

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while (!file.atEnd()) {
                QByteArray line = file.readLine() + 1;
                loadedSize += line.size(); // Aggiorna la dimensione caricata
                //qDebug() << "Loaded Size:" << loadedSize;
                progress = (loadedSize * 100) / totalSize;
                notifyObservers();
            }

            file.close();
        }
    }
}

long long FileLoader::getProgress() const {
    return progress;
}




