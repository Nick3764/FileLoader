
#ifndef LOADER_RESOURCEFILE_H
#define LOADER_RESOURCEFILE_H

#include <string>
#include <iostream>

class ResourceFile{
public:
    explicit ResourceFile(const std::string& filename);
    ~ResourceFile() = default;

    int getSize() const {
        return size;
    }

private:
    int size;
    FILE* file;
};

#endif //LOADER_RESOURCEFILE_H
