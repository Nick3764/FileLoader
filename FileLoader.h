
#ifndef LOADER_FILELOADER_H
#define LOADER_FILELOADER_H

#include "Subject.h"
#include <QObject>
#include <QVector>
#include <list>
#include <QString>

class FileLoader :  public QObject, public Subject{
    Q_OBJECT

public:
    explicit FileLoader(QObject* parent = nullptr);

    void addObserver(Observer* o) override;
    void removeObserver(Observer* o) override;
    void notifyObservers(int value) override;

public slots:
    void load(const QVector<QString>& files);

private:
    int filesNumber;
    QVector<Observer*> observers;
};

#endif //LOADER_FILELOADER_H
