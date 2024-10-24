#ifndef CURSOVA_SERIALIZABLE_H
#define CURSOVA_SERIALIZABLE_H
#include <iostream>

class Serializable {
public:
    friend std::ostream &operator<<(std::ostream &os, const Serializable &object);

    friend std::istream &operator>>(std::istream &is, Serializable &object);

    virtual void getDataFromObject(std::ostream &os) const = 0;
    virtual void setDataToObject(std::istream &is) = 0;
    virtual ~Serializable() = default;
};


#endif //CURSOVA_SERIALIZABLE_H
