#ifndef CURSOVA_MUSEUM_H
#define CURSOVA_MUSEUM_H

#include "Serializable.h"
#include "DataHandler.h"
#include "Painting.h"
#include "Artist.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

/*
 * Клас Museum – представляє музей, що зберігає інформацію про своє місцезнаходження,
 * назву та колекцію картин. Клас дозволяє додавати, видаляти картини та працювати з даними музеїв.
 */
class Museum : public Serializable, public DataHandler {
private:
    std::string location; // Місцезнаходження музею
    std::string name; // Назва музею
    std::vector<Painting> collection; // Колекція картин у музеї
    constexpr static const char* MUSEUM_FILE = "museums.txt"; // Файл для збереження даних музею

public:
    Museum(); // Конструктор за замовчуванням
    Museum(const std::string &name, const std::string &location); // Конструктор з параметрами
    Museum(const Museum &other); // Конструктор копіювання
    Museum(Museum &&other) noexcept; // Конструктор переміщення
    Museum& operator=(const Museum& other); // Оператор копіювання
    Museum& operator=(Museum&& other) noexcept; // Оператор переміщення
    ~Museum() override; // Деструктор

    // Отримати місцезнаходження музею
    [[nodiscard]] std::string getLocation() const;
    // Встановити місцезнаходження музею
    void setLocation(const std::string &location);
    // Отримати назву музею
    [[nodiscard]] std::string getName() const;
    // Встановити назву музею
    void setName(const std::string &name);

    // Видалити картину з колекції музею за назвою
    void removePaintingFromCollection(const std::string& paintingName);
    // Видалити картину з одного з музеїв у списку
    static void removePaintingFromMuseum(std::vector<Museum> &museums);

    void input(); // Введення інформації про музей
    void displayInfo() const override; // Відображення інформації про музей

    // Сортування музеїв за назвою
    static void sortMuseumsByName(std::vector<Museum>& museums);

    // Серіалізація об'єкта
    void getDataFromObject(std::ostream &os) const override;
    // Десеріалізація об'єкта
    void setDataToObject(std::istream &is) override;

    // Завантаження музеїв з файлу
    static void loadMuseums(std::vector<Museum>& museums);
    // Збереження музеїв у файл
    static void saveMuseums(const std::vector<Museum>& museums);
};

#endif //CURSOVA_MUSEUM_H
