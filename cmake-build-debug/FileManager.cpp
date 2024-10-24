#include "FileManager.h"
#include "Serializable.h"
#include <fstream>

void FileManager::writeToFile(const std::string &path, const Serializable &object) {
    std::ofstream ofs (path, std::ostream::out);
    ofs<<object;
    ofs.close();
}

void FileManager::downloadFromFile(const std::string &path, Serializable &object) {
    std::ifstream ifs(path, std::ifstream::in);
    ifs>>object;
    ifs.close();
}

void FileManager::renameFile(const std::string &oldPath, const std::string &newPath) {
    std::filesystem::rename(oldPath, newPath);
}