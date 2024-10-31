#ifndef CURSOVA_PAINTING_H
#define CURSOVA_PAINTING_H

#include "DataHandler.h"
#include "Serializable.h"
#include "Artist.h"
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <regex>

/*
 * Клас Painting – представляє картину з атрибутами, такими як назва, художник, дата створення, жанр та статус продажу.
 * Клас надає функціонал для управління картинами, фільтрації та пошуку картин, а також для роботи з файлами.
 */
class Painting : public Serializable, public DataHandler {
private:
    std::string title; // Назва картини
    std::shared_ptr<Artist> artist; // Художник, що створив картину
    std::string creationDate; // Дата створення картини
    std::string genre; // Жанр картини
    bool sold; // Статус продажу
    constexpr static const char* PAINTING_FILE = "painting.txt"; // Файл для збереження даних про картини

public:
    Painting(); // Конструктор за замовчуванням

    // Конструктор з параметрами
    Painting(const std::string& title, std::shared_ptr<Artist> artist, const std::string& creationDate, const std::string& genre);

    Painting(const Painting& other); // Конструктор копіювання
    Painting(Painting&& other) noexcept; // Конструктор переміщення
    Painting& operator=(const Painting& other); // Оператор копіювання
    Painting& operator=(Painting&& other) noexcept; // Оператор переміщення
    ~Painting() override; // Деструктор

    // Геттер для назви картини
    [[nodiscard]] std::string getTitle() const;
    // Сеттер для назви картини
    void setTitle(const std::string& title);

    // Геттер для художника
    [[nodiscard]] Artist* getArtist() const;
    // Сеттер для художника
    void setArtist(std::shared_ptr<Artist> artist);

    // Геттер для дати створення
    [[nodiscard]] std::string getCreationDate() const;
    // Сеттер для дати створення
    void setCreationDate(const std::string& creationDate);

    // Геттер для жанру
    [[nodiscard]] std::string getGenre() const;
    // Сеттер для жанру
    void setGenre(const std::string& genre);

    // Геттер для статусу продажу
    [[nodiscard]] bool getSold() const;
    // Сеттер для статусу продажу
    void setSold(bool sold);

    void input(); // Введення даних про картину
    void displayInfo() const override; // Відображення інформації про картину

    // Сортування картин за назвою
    static void sortPaintingsByTitle(std::vector<Painting>& paintings);

    // Фільтрація картин за жанром
    static std::vector<Painting> filterPaintingsByGenre(const std::vector<Painting>& paintings, const std::string& genre);

    // Пошук картин за назвою
    static std::vector<Painting> searchPaintingsByTitle(const std::vector<Painting>& paintings, const std::string& title);

    // Оновлення статусу продажу
    void updateSaleStatus();

    // Видалення картини
    static void removePainting(std::vector<Painting> &paintings);

    // Серіалізація об'єкта
    void getDataFromObject(std::ostream& os) const override;
    // Десеріалізація об'єкта
    void setDataToObject(std::istream& is) override;

    // Завантаження картин з файлу
    static void loadPaintings(std::vector<Painting>& paintings);
    // Збереження картин у файл
    static void savePaintings(const std::vector<Painting>& paintings);
};

#endif // CURSOVA_PAINTING_H
