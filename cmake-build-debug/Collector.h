#ifndef CURSOVA_COLLECTOR_H
#define CURSOVA_COLLECTOR_H

#include "Person.h"
#include "Painting.h"
#include "DataHandler.h"
#include "Serializable.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <regex>

/*
 * Клас Collector – представляє колекціонера, який володіє оригінальними та копіями картин.
 * Клас забезпечує функції для управління колекцією картин, участі в аукціонах,
 * збереження та завантаження даних колекціонерів.
 */
class Collector : public Person, public DataHandler {
private:
    std::vector<Painting> originalPaintings; // Оригінальні картини
    std::vector<Painting> copiedPaintings;   // Копії картин
    constexpr static const char* COLLECTOR_FILE = "collectors.txt"; // Файл для збереження даних

public:
    Collector(); // Конструктор за замовчуванням
    Collector(const std::string &name, const std::string &birthDate); // Конструктор з параметрами

    // Конструктор з параметрами для ініціалізації картин
    Collector(const std::string& name, const std::string& birthDate,
              const std::vector<Painting>& originalPaintings, const std::vector<Painting>& copiedPaintings);

    Collector(const Collector &other); // Конструктор копіювання
    Collector(Collector &&other) noexcept; // Конструктор переміщення
    Collector& operator=(const Collector& other); // Оператор копіювання
    Collector& operator=(Collector&& other) noexcept; // Оператор переміщення
    ~Collector() override; // Деструктор

    // Отримати оригінальні картини
    [[nodiscard]] std::vector<Painting> getOriginalPaintings() const;

    // Отримати копії картин
    [[nodiscard]] std::vector<Painting> getCopiedPaintings() const;

    void input() override; // Введення даних колекціонера
    void displayInfo() const override; // Відображення інформації про колекціонера

    // Участь у торгах, повертає ставку
    int placeBid(Painting* painting);

    // Придбати картину за вказаною ціною
    void purchasePainting(Painting* painting, int price);

    // Сортування колекціонерів за іменем
    static void sortCollectorsByName(std::vector<Collector>& collectors);

    // Серіалізація об'єкта
    void getDataFromObject(std::ostream &os) const override;
    // Десеріалізація об'єкта
    void setDataToObject(std::istream &is) override;

    // Завантаження колекціонерів з файлу
    static void loadCollectors(std::vector<Collector>& collectors);
    // Збереження колекціонерів у файл
    static void saveCollectors(const std::vector<Collector>& collectors);
};

#endif // CURSOVA_COLLECTOR_H
