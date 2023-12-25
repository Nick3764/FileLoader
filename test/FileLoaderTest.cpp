#include <gtest/gtest.h>
#include "../FileLoader.h"
#include <../QVector>

// Test case per verificare il caricamento dei file
TEST(FileLoaderTest, LoadFiles) {
    FileLoader fileLoader;
    QVector <QString> files;
// Aggiungi file validi alla lista
    files.push_back("path/to/valid_file1.txt");
    files.push_back("path/to/valid_file2.txt");

// Verifica che il caricamento avvenga correttamente
    EXPECT_NO_THROW({
                        fileLoader.load(files);
                    });
}