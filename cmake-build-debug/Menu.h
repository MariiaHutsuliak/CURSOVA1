#ifndef CURSOVA_MENU_H
#define CURSOVA_MENU_H

#include <iostream>
#include <vector>
#include <string>
#include "Admin.h"
#include "Artist.h"
#include "Collector.h"
#include "Auctioneer.h"
#include "Museum.h"
#include "CommissionShop.h"

class Menu {
public:
    // Main User Menu
    void mainManu();
    void userMenu();
    void viewPaintings();

    // Admin Menu
    bool authenticateAdmin(std::vector<Admin>& admins);
    void adminMenu(std::vector<Admin>& admins);
    void addAdmin(std::vector<Admin>& admins);
    void manageModerators();

    // Moderator Menus
    void artistMenu();
    void collectorMenu();
    void auctioneerMenu();

    // Museum and Shop Menus
    void museumMenu();
    void commissionShopMenu();

    // File Loaders and Savers
    void loadAdmins(std::vector<Admin>& admins);
    void saveAdmins(const std::vector<Admin>& admins);

    void loadArtists(std::vector<Artist>& artists);
    void saveArtists(const std::vector<Artist>& artists);

    void loadCollectors(std::vector<Collector>& collectors);
    void saveCollectors(const std::vector<Collector>& collectors);

    void loadAuctioneers(std::vector<Auctioneer>& auctioneers);
    void saveAuctioneers(const std::vector<Auctioneer>& auctioneers);

    void loadMuseums(std::vector<Museum>& museums);
    void saveMuseums(const std::vector<Museum>& museums);

    void loadShops(std::vector<CommissionShop>& shops);
    void saveShops(const std::vector<CommissionShop>& shops);

private:
    // File paths for persistence
    const std::string ADMIN_FILE = "admins.txt";
    const std::string ARTIST_FILE = "artists.txt";
    const std::string COLLECTOR_FILE = "collectors.txt";
    const std::string AUCTIONEER_FILE = "auctioneers.txt";
    const std::string MUSEUM_FILE = "museums.txt";
    const std::string SHOP_FILE = "shops.txt";
};

#endif // CURSOVA_MENU_H
