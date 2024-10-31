#ifndef CURSOVA_PERSON_H
#define CURSOVA_PERSON_H

#include "Serializable.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <limits>

/*
 * Клас Person – базовий клас для зберігання інформації про людину, що містить
 * атрибути і методи для роботи з іменем та датою народження.
 */
class Person : public Serializable {
private:
    std::string name; // Ім'я особи
    std::string birthDate; // Дата народження

public:
    Person(); // Конструктор за замовчуванням
    Person(const std::string &name, const std::string &birthDate); // Конструктор з параметрами
    Person(const Person& other); // Конструктор копіювання
    Person(Person&& other) noexcept; // Конструктор переміщення
    Person& operator=(const Person& other); // Оператор копіювання
    Person& operator=(Person&& other) noexcept; // Оператор переміщення
    ~Person() override; // Деструктор

    virtual void input(); // Метод введення даних особи

    // Геттер для імені особи
    [[nodiscard]] std::string getName() const;
    // Сеттер для імені особи
    void setName(const std::string &name);

    // Геттер для дати народження
    [[nodiscard]] std::string getBirthDate() const;
    // Сеттер для дати народження
    void setBirthDate(const std::string &birthDate);

    // Серіалізація об'єкта
    void getDataFromObject(std::ostream &os) const override;
    // Десеріалізація об'єкта
    void setDataToObject(std::istream &is) override;
};

#endif //CURSOVA_PERSON_H
