#ifndef CURSOVA_FILEMANAGER_H
#define CURSOVA_FILEMANAGER_H

#include <iostream>
#include <filesystem>

class Serializable;

class FileManager {
private:
    FileManager() = delete;

public:
    static void writeToFile(const std::string &path, const Serializable &object);

    static void downloadFromFile(const std::string &path, Serializable &object);

    static void renameFile(const std::string &oldPath, const std::string &newPath);
};


#endif //CURSOVA_FILEMANAGER_H
