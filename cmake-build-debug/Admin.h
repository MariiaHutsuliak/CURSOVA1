#ifndef CURSOVA_ADMIN_H
#define CURSOVA_ADMIN_H

#include "Serializable.h"
#include "Artist.h"
#include "Auctioneer.h"
#include "Collector.h"
#include "Museum.h"
#include "CommissionShop.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

/*
 * Клас Admin – представляє адміністратора системи, який може керувати різними типами
 * користувачів, такими як художники, колекціонери, аукціоністи, музеї та комісійні магазини.
 * Клас реалізує інтерфейс Serializable для забезпечення збереження даних в файли.
 */
class Admin : public Serializable {
private:
    std::string userName; // Ім'я користувача адміністратора
    std::string password; // Пароль адміністратора

    // Константи з назвами файлів для збереження даних
    constexpr static const char* ADMIN_FILE = "admins.txt";
    constexpr static const char* ARTIST_FILE = "artists.txt";
    constexpr static const char* COLLECTOR_FILE = "collectors.txt";
    constexpr static const char* MUSEUM_FILE = "museums.txt";
    constexpr static const char* SHOP_FILE = "shops.txt";
    constexpr static const char* AUCTIONEER_FILE = "auctioneers.txt";

public:
    Admin(); // Конструктор за замовчуванням

    // Заборона копіювання та переміщення для унікальності об'єкта
    Admin(const Admin&) = delete;
    Admin& operator=(const Admin&) = delete;
    Admin(Admin&&) = delete;
    Admin& operator=(Admin&&) = delete;

    // Метод для отримання єдиного екземпляра класу Admin (синглтон)
    static Admin& getInstance();

    // Методи доступу до імені користувача
    [[nodiscard]] const std::string &getUserName() const;
    void setUserName(const std::string &userName);

    // Методи доступу до пароля
    [[nodiscard]] const std::string &getPassword() const;
    void setPassword(const std::string &password);

    // Метод для автентифікації адміністратора
    static bool authenticateAdmin();

    /*
     * Метод manageModerators дозволяє адміністратору керувати різними типами
     * користувачів-модераторів, переданими в параметрах.
     */
    static void manageModerators(std::vector<Artist>& artists, std::vector<Collector>& collectors, std::vector<Auctioneer>& auctioneers,
                                 std::vector<Museum>& museums, std::vector<CommissionShop>& shops);

    // Шаблонний метод для управління конкретним типом модераторів
    template<typename T>
    static void manageSpecificModerator(std::vector<T> &moderators, int actionChoice);

    // Шаблонний метод для додавання модератора
    template<typename T>
    static void addModerator(std::vector<T>& moderators);

    // Шаблонний метод для збереження модераторів у файл
    template<typename T>
    static void saveModeratorsToFile(const std::vector<T>& moderators, const char* fileName);

    // Шаблонний метод для видалення модератора
    template<typename T>
    static void removeModerator(std::vector<T>& moderators);

    // Шаблонний метод для перегляду списку модераторів
    template<typename T>
    static void viewModerators(const std::vector<T>& moderators);

    // Методи для серіалізації об'єкта (збереження та відновлення даних)
    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

    // Завантаження даних адміністратора з файлу
    void loadAdmin();
    // Збереження даних адміністратора у файл
    void saveAdmin() const;
};

#endif // CURSOVA_ADMIN_H
