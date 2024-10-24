#include "Person.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>

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
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty.");
    }
    this->name = name;
}

std::string Person::getBirthDate() const {
    return birthDate;
}
void Person::setBirthDate(const std::string &birthDate) {
    if (birthDate.empty()) {
        throw std::invalid_argument("Birth date cannot be empty.");
    }
    this->birthDate = birthDate;
}

void Person::input() {
    std::cout << "Enter name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty.");
    }

    std::cout << "Enter birth date: ";
    std::getline(std::cin, birthDate);
    if (birthDate.empty()) {
        throw std::invalid_argument("Birth date cannot be empty.");
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