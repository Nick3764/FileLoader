
#ifndef LOADER_FILELOADER_H
#define LOADER_FILELOADER_H

#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QVector>
#include <QString>
#include "Subject.h"

class FileLoader :  public QObject, public Subject{
    Q_OBJECT

public:
    explicit FileLoader(QObject* parent = nullptr);

    void addObserver(Observer* o) override;
    void removeObserver(Observer* o) override;
    void notifyObservers() override;

    long long getProgress() const;
    void setProgress(long long value);

public slots:
    void load(const QVector<QString>& files);

private:
    long long filesNumber;
    long long progress;
    QVector<Observer*> observers;
};

#endif //LOADER_FILELOADER_H
