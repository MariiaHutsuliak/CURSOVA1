#ifndef CURSOVA_DATAHANDLER_H
#define CURSOVA_DATAHANDLER_H
using namespace std;
#include <fstream>
class DataHandler;

class DataHandler {
public:
    virtual ~DataHandler() {}
    virtual void displayInfo() const = 0;
};
#endif //CURSOVA_DATAHANDLER_H
