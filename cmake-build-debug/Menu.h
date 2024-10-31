#ifndef CURSOVA_MENU_H
#define CURSOVA_MENU_H

#include "Admin.h"
#include "Artist.h"
#include "Collector.h"
#include "Auctioneer.h"
#include "Museum.h"
#include "CommissionShop.h"
#include "Painting.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

/*
 * Клас Menu – забезпечує інтерфейс користувача для навігації по функціям системи.
 * Клас містить різні підменю для управління даними про художників, колекціонерів, аукціоністів,
 * музеї, комісійні магазини та картини.
 */
class Menu {
private:
    std::vector<Artist> artists; // Колекція художників
    std::vector<Collector> collectors; // Колекція колекціонерів
    std::vector<Auctioneer> auctioneers; // Колекція аукціоністів
    std::vector<Museum> museums; // Колекція музеїв
    std::vector<CommissionShop> shops; // Колекція комісійних магазинів
    std::vector<Painting> paintings; // Колекція картин

public:
    Menu(); // Конструктор за замовчуванням

    // Статичний метод для очищення потоку вводу після помилкових операцій
    static void clearInput();

    // Методи для завантаження і збереження всіх даних
    void loadAllData();
    void saveAllData();

    // Головне меню програми
    void mainMenu();

    // Меню для адміністратора
    void adminMenu();

    // Меню для модератора
    void moderatorMenu();

    // Меню для художників
    void artistMenu();

    // Меню для колекціонерів
    void collectorMenu();

    // Меню для аукціоністів
    void auctioneerMenu();

    // Меню для музеїв
    void museumMenu();

    // Меню для комісійних магазинів
    void commissionShopMenu();

    // Меню для звичайного користувача
    void userMenu();

    // Метод для відображення керівництва користувача
    void userManual();
};

#endif // CURSOVA_MENU_H
