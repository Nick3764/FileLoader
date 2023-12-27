
#include <gtest/gtest.h>
#include "../GUI.h"

// Test per verificare il reset della GUI dopo il completamento del caricamento
TEST(GUITest, ResetAfterCompletionTest) {

// Creazione del FileLoader utilizzando il QObject appena creato
    FileLoader fileLoader;
    GUI gui(&fileLoader);

    // Simula l'aggiornamento quando il caricamento è completato (progresso al 100%)
    gui.setBarProgress(100);

    // Simula l'aggiornamento della GUI dopo il completamento del caricamento
    gui.update();

    // Verifica che la GUI sia stata resettata correttamente dopo il completamento
    EXPECT_EQ(gui.getProgressBarValue(), 0);
    EXPECT_EQ(gui.getSelectedFilesCount(), 0);

}


// Test per verificare la corretta visualizzazione dell'interfaccia grafica
TEST(GUITest, InterfaceDisplayTest) {
    FileLoader fileLoader;
    GUI gui(&fileLoader);

    // Verifica che il titolo sia impostato correttamente
    EXPECT_EQ(gui.windowTitle(), "Laboratorio di Programmazione - 2023");

    // Verifica che la dimensione della finestra sia impostata correttamente
    EXPECT_EQ(gui.size(), QSize(600, 350));

    // Verifica che i pulsanti siano presenti e abbiano le dimensioni corrette
    auto *chooseFilesButton = gui.findChild<QPushButton*>("Choose File");
    auto *submitButton = gui.findChild<QPushButton*>("Submit");

    ASSERT_TRUE(chooseFilesButton != nullptr);
    ASSERT_TRUE(submitButton != nullptr);

    EXPECT_EQ(chooseFilesButton->text(), "Choose File");
    EXPECT_EQ(submitButton->text(), "Submit");
    EXPECT_EQ(chooseFilesButton->size().width(), 172);
    EXPECT_EQ(submitButton->size().width(), 172);

    // Verifica che la progress bar sia presente e inizializzata correttamente
    auto *progressBar = gui.findChild<QProgressBar*>();
    ASSERT_TRUE(progressBar != nullptr);
    EXPECT_EQ(progressBar->minimum(), 0);
    EXPECT_EQ(progressBar->maximum(), 100);
    EXPECT_EQ(progressBar->value(), 0);
}