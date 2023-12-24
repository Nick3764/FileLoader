
#ifndef LOADER_GUI_H
#define LOADER_GUI_H

#include "Observer.h"
#include <QMainWindow>
#include "FileLoader.h"
#include <QProgressBar>

class GUI : public QMainWindow, public Observer{
    Q_OBJECT
public:
    GUI(FileLoader* fl, QWidget* parent = nullptr);

    ~GUI() override;

    void update() override;

private:
    FileLoader* fl;
};

#endif //LOADER_GUI_H
