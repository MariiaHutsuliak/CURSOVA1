#ifndef CURSOVA_SERIALIZABLE_H
#define CURSOVA_SERIALIZABLE_H

#include <iostream>

/*
 * Абстрактний клас Serializable забезпечує інтерфейс для серіалізації та десеріалізації об'єктів.
 * Клас визначає віртуальні методи для збереження та завантаження даних об'єкта з потоку.
 */
class Serializable {
public:
    // Перевантаження оператора виводу для серіалізації об'єкта
    friend std::ostream &operator<<(std::ostream &os, const Serializable &object);

    // Перевантаження оператора вводу для десеріалізації об'єкта
    friend std::istream &operator>>(std::istream &is, Serializable &object);

    // Чисто віртуальна функція для отримання даних об'єкта з потоку
    virtual void getDataFromObject(std::ostream &os) const = 0;

    // Чисто віртуальна функція для встановлення даних об'єкта з потоку
    virtual void setDataToObject(std::istream &is) = 0;

    virtual ~Serializable(); // Віртуальний деструктор за замовчуванням
};

#endif //CURSOVA_SERIALIZABLE_H
