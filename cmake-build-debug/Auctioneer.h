#ifndef CURSOVA_AUCTIONEER_H
#define CURSOVA_AUCTIONEER_H

#include "Person.h"
#include "Painting.h"
#include "Collector.h"
#include "DataHandler.h"
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <regex>

/*
 * Клас Auctioneer – представляє аукціоніста, який проводить аукціони та зберігає інформацію
 * про продані картини. Клас успадковує функціональність від класів Person і DataHandler.
 */
class Auctioneer : public Person, public DataHandler {
private:
    std::map<std::string, std::pair<std::string, double>> auctionedPaintings; // Картини, продані на аукціоні
    std::string auctionDate; // Дата проведення аукціону
    constexpr static const char* AUCTIONEER_FILE = "auctioneers.txt"; // Ім'я файлу для збереження даних

public:
    Auctioneer(); // Конструктор за замовчуванням

    // Конструктор з параметрами, що приймає ім'я, дату народження та дату аукціону
    Auctioneer(const std::string &name, const std::string &birthDate, const std::string &auctionDate);

    // Конструктор з параметрами, що приймає ім'я, дату народження, дату аукціону та список проданих картин
    Auctioneer(const std::string& name, const std::string& birthDate, const std::string& auctionDate,
               const std::map<std::string, std::pair<std::string, double>>& auctionedPaintings);

    Auctioneer(const Auctioneer &other); // Конструктор копіювання
    Auctioneer(Auctioneer &&other) noexcept; // Конструктор переміщення
    Auctioneer& operator=(const Auctioneer& other); // Оператор присвоєння копіюванням
    Auctioneer& operator=(Auctioneer&& other) noexcept; // Оператор присвоєння переміщенням
    ~Auctioneer() override; // Деструктор

    // Геттер для отримання дати аукціону
    [[nodiscard]] std::string getAuctionDate() const;

    // Сеттер для задання дати аукціону
    void setAuctionDate(const std::string &auctionDate);

    // Геттер для отримання списку проданих картин на аукціоні
    [[nodiscard]] std::map<std::string, std::pair<std::string, double>> getAuctionedPaintings() const;


    // Метод holdAuction – проводить аукціон, отримує картину та список колекціонерів.
    void holdAuction(Painting* painting, std::vector<Collector*>& collectors);

    // Метод для введення даних аукціоніста з консолі
    void input() override;

    // Метод для відображення інформації про аукціоніста
    void displayInfo() const override;

    // Статичний метод для сортування аукціоністів за іменем в алфавітному порядку.
    static void sortAuctioneersByName(std::vector<Auctioneer>& auctioneers);

    // Метод для серіалізації об'єкта (збереження в потік)
    void getDataFromObject(std::ostream &os) const override;
    // Метод для десеріалізації об'єкта (відновлення з потоку)
    void setDataToObject(std::istream &is) override;


    // Статичний метод для завантаження аукціоністів з файлу.
    static void loadAuctioneers(std::vector<Auctioneer>& auctioneers);
    // Статичний метод для збереження аукціоністів у файл.
    static void saveAuctioneers(const std::vector<Auctioneer>& auctioneers);
};

#endif //CURSOVA_AUCTIONEER_H
