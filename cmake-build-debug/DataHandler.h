#ifndef CURSOVA_DATAHANDLER_H
#define CURSOVA_DATAHANDLER_H

class DataHandler {
public:
    virtual ~DataHandler() = default;
    virtual void displayInfo() const = 0;
};

#endif //CURSOVA_DATAHANDLER_H
