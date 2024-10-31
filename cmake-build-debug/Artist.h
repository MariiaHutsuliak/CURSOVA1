#ifndef CURSOVA_ARTIST_H
#define CURSOVA_ARTIST_H

#include "Person.h"
#include "DataHandler.h"
#include "Serializable.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <regex>

/*
 * Клас Artist – представляє художника в системі з інформацією про стиль.
 * Клас успадковує від базових класів Person і DataHandler, що дозволяє
 * зберігати та обробляти дані про художника, включаючи ім'я, дату народження та стиль.
 */
class Artist: public Person, public DataHandler {
private:
    std::string style; // Стиль художника
    constexpr static const char* ARTIST_FILE = "artists.txt"; // Ім'я файлу для збереження даних про художників

public:
    Artist(); // Конструктор за замовчуванням

    // Конструктор з параметрами, приймає ім'я, дату народження та стиль художника
    Artist(const std::string &name, const std::string &birthDate, const std::string &style);

    Artist(const Artist &other); // Конструктор копіювання
    Artist(Artist &&other) noexcept; // Конструктор переміщення
    Artist& operator=(const Artist& other); // Оператор присвоєння копіюванням
    Artist& operator=(Artist&& other) noexcept; // Оператор присвоєння переміщенням
    ~Artist() override; // Деструктор

    // Метод для відображення інформації про художника
    void displayInfo() const override;

    // Метод для введення даних про художника з консолі
    void input() override;

    // Геттер для отримання стилю художника
    [[nodiscard]] std::string getStyle() const;
    // Сеттер для задання стилю художника
    void setStyle(const std::string &style);

    // Статичний метод для сортування художників за іменем в алфавітному порядку.
    static void sortArtistsByName(std::vector<Artist>& artists);

    // Статичний метод для фільтрації художників за стилем.
    static std::vector<Artist> filterArtistsByStyle(const std::vector<Artist>& artists, const std::string& style);

    // Статичний метод для пошуку художників за іменем.
    static std::vector<Artist> searchArtistsByName(const std::vector<Artist>& artists, const std::string& name);

    // Метод для серіалізації даних об'єкта (збереження в потік)
    void getDataFromObject(std::ostream &os) const override;
    // Метод для десеріалізації даних об'єкта (відновлення з потоку)
    void setDataToObject(std::istream &is) override;

    // Статичний метод для завантаження художників з файлу.
    static void loadArtists(std::vector<Artist>& artists);
     // Статичний метод для збереження художників у файл.
    static void saveArtists(const std::vector<Artist>& artists);
};

#endif //CURSOVA_ARTIST_H
