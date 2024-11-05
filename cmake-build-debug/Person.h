#ifndef CURSOVA_PERSON_H
#define CURSOVA_PERSON_H

#include "Serializable.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <limits>

class Person : public Serializable {
private:
    std::string name;
    std::string birthDate;

public:
    Person();
    Person(const std::string &name, const std::string &birthDate);
    Person(const Person& other);
    Person(Person&& other) noexcept;
    Person& operator=(const Person& other);
    Person& operator=(Person&& other) noexcept;

    virtual ~Person() override;

    virtual void input() = 0;

    [[nodiscard]] std::string getName() const;
    void setName(const std::string &name);

    [[nodiscard]] std::string getBirthDate() const;
    void setBirthDate(const std::string &birthDate);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;
};

#endif //CURSOVA_PERSON_H
