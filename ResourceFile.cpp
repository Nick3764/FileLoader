
#include "ResourceFile.h"

ResourceFile::ResourceFile(const std::string& filename) {
    file = fopen(filename.c_str(), "r");
    if (!file) {
        throw std::runtime_error("Could not find the file!");
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        throw std::runtime_error("Error seeking to end of file");
    }

    long fileSize = ftell(file);
    if (fileSize == -1) {
        fclose(file);
        throw std::runtime_error("Error getting file size");
    }

    size = static_cast<int>(fileSize);
    std::cout << "File " << filename << " opened successfully, size is " << size << " bytes." << std::endl;

}
