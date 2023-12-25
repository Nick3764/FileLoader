
#ifndef LOADER_GUI_H
#define LOADER_GUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QFileDialog>
#include <QLabel>
#include <QVector>
#include <iostream>
#include "FileLoader.h"

class GUI : public QMainWindow, public Observer{
    Q_OBJECT
public:
    explicit GUI(FileLoader* fl, QWidget* parent = nullptr);
    ~GUI() override;

    void update() override;
    void reset();

private slots:
    void openFileDialog();
    void submit();

private:
    QProgressBar* progressBar;
    QVBoxLayout* layout;
    QVBoxLayout *filesLayout;
    QWidget *filesContainer;
    QScrollArea *scrollArea;
    QVector<QString> selectedFiles;
    FileLoader* fl;
};

#endif //LOADER_GUI_H
