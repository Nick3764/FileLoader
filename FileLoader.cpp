
#include "FileLoader.h"
#include <QFile>

#include <QFileInfo>

FileLoader::FileLoader(QObject* parent) : QObject(parent), filesNumber(0) {}

void FileLoader::addObserver(Observer *o) {
    observers.push_back(o);
}

void FileLoader::removeObserver(Observer *o) {
    observers.removeAll(o);
}

void FileLoader::notifyObservers(int value) {
    for(Observer* observer : observers)
        observer->update(value);
}

void FileLoader::load(const QVector<QString>& files) {
    int totalSize = 0;
    for (const QString& filePath : files) {
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists() || fileInfo.suffix().toLower() != "txt") {
            continue;
        }
        totalSize += fileInfo.size(); // Aggiungi la dimensione del file alla dimensione totale
    }

    filesNumber = files.size();
    int loadedSize = 0;

    for (const QString& filePath : files) {
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists() || fileInfo.suffix().toLower() != "txt") {
            continue;
        }

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            loadedSize += fileInfo.size(); // Aggiorna la dimensione caricata

            int progress = (loadedSize * 100) / totalSize;
            notifyObservers(progress);

            file.close();
        }
    }
}




