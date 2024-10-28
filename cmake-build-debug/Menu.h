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
#include <iostream>
#include <limits>

class Menu {
private:
    std::vector<Artist> artists;
    std::vector<Collector> collectors;
    std::vector<Auctioneer> auctioneers;
    std::vector<Museum> museums;
    std::vector<CommissionShop> shops;
    std::vector<Painting> paintings;

public:
    Menu();
    static void clearInput();

    void loadAllData();
    void saveAllData();

    void mainMenu();
    void adminMenu();
    void moderatorMenu();
    void artistMenu();
    void collectorMenu();
    void auctioneerMenu();
    void museumMenu();
    void commissionShopMenu();
    void userMenu();
};



#endif // CURSOVA_MENU_H
