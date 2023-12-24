#include <iostream>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include "GUI.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FileLoader loader;

    GUI mainWindow(&loader);
    mainWindow.show();

    return app.exec();
}
