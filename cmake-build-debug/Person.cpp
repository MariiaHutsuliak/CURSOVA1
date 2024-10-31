#include "Person.h"

Person::Person() : name{"None"}, birthDate{"None"} {}

Person::Person(const std::string &name, const std::string &birthDate)
    : name{name}, birthDate{birthDate} {}

Person::Person(const Person& other) : name(other.name), birthDate(other.birthDate) {}

Person::Person(Person&& other) noexcept : name(std::move(other.name)), birthDate(std::move(other.birthDate)) {}

Person& Person::operator=(const Person &other) {
    if (this == &other) return *this;
    name = other.name;
    birthDate = other.birthDate;
    return *this;
}

Person& Person::operator=(Person &&other) noexcept {
    if (this == &other) return *this;
    name = move(other.name);
    birthDate = move(other.birthDate);
    return *this;
}

Person::~Person() {};

std::string Person::getName() const {
    return name;
}

void Person::setName(const std::string &name) {
    this->name = name;
}

std::string Person::getBirthDate() const {
    return birthDate;
}
void Person::setBirthDate(const std::string &birthDate) {
    this->birthDate = birthDate;
}

void Person::input() {
    std::regex latinRegex("^[A-Za-z\\s]+$");
    std::regex dateRegex("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");
    while (true) {
        try {
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            if (name.empty() || !std::regex_match(name, latinRegex)) {
                throw std::runtime_error("Invalid name.");
            }
            std::cout << "Enter birth date (YYYY-MM-DD): ";
            std::getline(std::cin, birthDate);
            if (birthDate.empty() || !std::regex_match(birthDate, dateRegex)) {
                throw std::runtime_error("Invalid birth date format.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input. Please follow the format and try again.\n";
        }
    }
}

void Person::getDataFromObject(std::ostream &os) const {
    os << name << std::endl;
    os << birthDate << std::endl;
}

void Person::setDataToObject(std::istream &is) {
    std::string currentLine;
    std::getline(is, currentLine);
    name = currentLine;
    std::getline(is, currentLine);
    birthDate = currentLine;
}