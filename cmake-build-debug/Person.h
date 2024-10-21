#ifndef CURSOVA_PERSON_H
#define CURSOVA_PERSON_H
#include "DataHandler.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Person: public DataHandler {
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
    virtual ~Person();

    virtual void input();
    void displayInfo() const override = 0;

    std::string getName() const;
    void setName(const std::string &name);

    std::string getBirthDate() const;
    void setBirthDate(const std::string &birthDate);

    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;


};


#endif //CURSOVA_PERSON_H
