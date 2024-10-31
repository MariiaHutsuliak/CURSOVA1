#ifndef CURSOVA_COMMISSIONSHOP_H
#define CURSOVA_COMMISSIONSHOP_H

#include "DataHandler.h"
#include "Serializable.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <regex>

/*
 * Клас CommissionShop – представляє комісійний магазин, що зберігає дані про картини для продажу.
 * Клас включає методи для управління покупками та продажами картин, а також для збереження даних у файл.
 */
class CommissionShop : public Serializable, public DataHandler {
private:
    std::string name; // Назва магазину
    std::map<std::string, double> paintingsForSale; // Картини, доступні для продажу
    constexpr static const char* SHOP_FILE = "shops.txt"; // Файл для збереження даних

public:
    CommissionShop(); // Конструктор за замовчуванням
    CommissionShop(const std::string& name, const std::map<std::string, double>& paintingsForSale); // Конструктор з параметрами
    CommissionShop(const CommissionShop &other); // Конструктор копіювання
    CommissionShop(CommissionShop &&other) noexcept; // Конструктор переміщення
    CommissionShop& operator=(const CommissionShop& other); // Оператор копіювання
    CommissionShop& operator=(CommissionShop&& other) noexcept; // Оператор переміщення
    ~CommissionShop() override; // Деструктор

    void setName(const std::string& name); // Встановити назву магазину
    [[nodiscard]] std::string getName() const; // Отримати назву магазину

    void input(); // Введення інформації про магазин
    void buyPainting(const std::string& painting, double price); // Купити картину
    void sellPainting(const std::string& painting); // Продати картину
    void displayInfo() const override; // Відображення інформації про магазин

    // Купити картину в магазині
    static void buyPaintingInShop(std::vector<CommissionShop>& shops);

    // Продати картину в магазині
    static void sellPaintingInShop(std::vector<CommissionShop>& shops);

    // Серіалізація об'єкта
    void getDataFromObject(std::ostream &os) const override;
    // Десеріалізація об'єкта
    void setDataToObject(std::istream &is) override;

    // Завантаження даних магазинів з файлу
    static void loadShops(std::vector<CommissionShop>& shops);
    // Збереження даних магазинів у файл
    static void saveShops(const std::vector<CommissionShop>& shops);
};

#endif // CURSOVA_COMMISSIONSHOP_H
