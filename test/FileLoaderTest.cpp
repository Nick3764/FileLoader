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
        fileLoader.load(files);});

    EXPECT_EQ(fileLoader.getProgress(), 100);
}

// Test case per verificare il comportamento con file non validi
TEST(FileLoaderTest, LoadInvalidFiles) {
    FileLoader fileLoader;
    QVector<QString> files;

    // Aggiunta file non validi alla lista
    files.push_back("path/to/non_existing_file_1.txt");
    files.push_back("path/to/non_existing_file_2.txt");

    // Verifica che il caricamento sollevi un'eccezione
    ASSERT_THROW({
        fileLoader.load(files);},
                 std::runtime_error);

    // Verifica che il progresso sia rimasto a 0
    EXPECT_EQ(fileLoader.getProgress(), 0);
}

class TestObserver : public Observer {
public:
    TestObserver() : updateCalls(0) {}

    void update() override {
        // Incrementa il contatore ogni volta che viene chiamato update()
        updateCalls++;
    }

    int getUpdateCalls() const {
        return updateCalls;
    }

private:
    int updateCalls;
};

TEST(FileLoaderTest, CheckUpdateCalls){
    FileLoader fileLoader;
    TestObserver testObserver;
    fileLoader.addObserver(&testObserver);
    QVector <QString> files;

    // Aggiunta file validi alla lista
    files.push_back("C:/Users/Utente/Desktop/1.txt");
    files.push_back("C:/Users/Utente/Desktop/2.txt");

    int expectedUpdateCalls = 0;
    for (const QString& filePath : files) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while (!file.atEnd()) {
                file.readLine();
                expectedUpdateCalls++;
            }
            file.close();
        }
    }
    fileLoader.load(files);
    ASSERT_EQ(testObserver.getUpdateCalls(), expectedUpdateCalls);
}