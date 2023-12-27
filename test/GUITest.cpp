
#include <gtest/gtest.h>
#include "../GUI.h"

// Test per verificare il reset della GUI dopo il completamento del caricamento
TEST(GUITest, ResetAfterCompletionTest) {
    FileLoader fileLoader;
    GUI gui(&fileLoader);

    // Simula l'aggiornamento quando il caricamento è completato (progresso al 100%)
    gui.setProgress(100);

    // Simula l'aggiornamento della GUI dopo il completamento del caricamento
    gui.update();

    // Verifica che la GUI sia stata resettata correttamente dopo il completamento
    EXPECT_EQ(gui.getProgressBarValue(), 0);
    EXPECT_EQ(gui.getSelectedFilesCount(), 0);
}