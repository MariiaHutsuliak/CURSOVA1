#ifndef CURSOVA_DATAHANDLER_H
#define CURSOVA_DATAHANDLER_H
using namespace std;
#include <fstream>

class DataHandler {
public:
    virtual ~DataHandler() {}
    virtual void displayInfo() const = 0;
    virtual void save(std::ofstream &out) const = 0;
    virtual void load(std::ifstream &in) = 0;
};
#endif //CURSOVA_DATAHANDLER_H
