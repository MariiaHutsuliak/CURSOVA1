#ifndef CURSOVA_DATAHANDLER_H
#define CURSOVA_DATAHANDLER_H

/*
 * Абстрактний клас DataHandler – забезпечує базовий інтерфейс для обробки та відображення інформації об'єктів.
 * Клас визначає чисто віртуальний метод displayInfo(), який має бути реалізований у класах-нащадках.
 */
class DataHandler {
public:
    virtual ~DataHandler() = default; // Віртуальний деструктор за замовчуванням

    // Чисто віртуальний метод для відображення інформації про об'єкт
    virtual void displayInfo() const = 0;
};

#endif //CURSOVA_DATAHANDLER_H
