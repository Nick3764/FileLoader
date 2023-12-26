#include <gtest/gtest.h>
#include "../FileLoader.h"

// Test case per verificare il caricamento dei file
TEST(FileLoaderTest, LoadFiles) {
    FileLoader fileLoader;
    QVector <QString> files;

    // Aggiunta file validi alla lista
    files.push_back("C:/Users/Utente/Desktop/1.txt");
    files.push_back("C:/Users/Utente/Desktop/2.txt");

    // Verifica del corretto caricamento
    EXPECT_NO_THROW({
        fileLoader.load(files);
    });

    EXPECT_EQ(fileLoader.getProgress(), 100);

}