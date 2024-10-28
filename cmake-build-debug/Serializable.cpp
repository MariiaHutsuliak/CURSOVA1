#include "Serializable.h"

std::ostream &operator<<(std::ostream &os, const Serializable &object){
    object.getDataFromObject(os);
    return os;
}
std::istream &operator>>(std::istream &is, Serializable &object){
    object.setDataToObject(is);
    return is;
}

Serializable::~Serializable() = default;