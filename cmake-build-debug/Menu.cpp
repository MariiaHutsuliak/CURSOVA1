#include "Menu.h"
#include "Admin.h"
#include "Artist.h"
#include "Collector.h"
#include "Auctioneer.h"
#include "Museum.h"
#include "CommissionShop.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

// File paths for persistence
const std::string ADMIN_FILE = "admins.txt";
const std::string ARTIST_FILE = "artists.txt";
const std::string COLLECTOR_FILE = "collectors.txt";
const std::string AUCTIONEER_FILE = "auctioneers.txt";
const std::string MUSEUM_FILE = "museums.txt";
const std::string SHOP_FILE = "shops.txt";

void Menu::mainManu() {
    std::cout << "==============================================================\n";
    std::cout << "Welcome to the Art Lover System\n";
    std::cout << "==============================================================\n";
    std::cout << "Choose your role:\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "1. Regular User\n";
    std::cout << "2. Moderator(Artist, Auctioneer, Collector)\n";
    std::cout << "3. Admin\n";
    std::cout << "==============================================================\n";
}

void Menu::userMenu() {
        std::cout << "==============================================================\n";
        std::cout << "Art Lover System";
        std::cout << "==============================================================\n";
        std::cout << "User Menu:\n";
        std::cout << "--------------------------------------------------------------\n";
        std::cout << "1. Paintings\n";
        std::cout << "2. Artists\n";
        std::cout << "3. Auctioneers\n";
        std::cout << "4. Collectors\n";
        std::cout << "5. Museums\n";
        std::cout << "6. Commission Shops\n";
        std::cout << "0. Exit\n";
        std::cout << "==============================================================\n";
}

void Menu::viewPaintings() {
    std::vector<Artist> artists;
    loadArtists(artists);
    std::cout << "Available Paintings:\n";
    for (const auto& artist : artists) {
        artist.displayInfo();  // Show paintings by each artist
    }
}

// Load and Save Functions for Admin
void Menu::loadAdmins(std::vector<Admin>& admins) {
    std::ifstream file(ADMIN_FILE);
    if (file.is_open()) {
        while (!file.eof()) {
            Admin admin;
            admin.setDataToObject(file);
            admins.push_back(admin);
        }
        file.close();
    }
}

void Menu::saveAdmins(const std::vector<Admin>& admins) {
    std::ofstream file(ADMIN_FILE);
    for (const auto& admin : admins) {
        admin.getDataFromObject(file);
    }
    file.close();
}

// Admin Menu
bool Menu::authenticateAdmin(std::vector<Admin>& admins) {
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;

    for (auto& admin : admins) {
        if (admin.getUserName() == username && admin.getPassword() == password) {
            return true;
        }
    }
    std::cout << "Invalid credentials!" << std::endl;
    return false;
}

void Menu::adminMenu(std::vector<Admin>& admins) {
        std::cout << "==============================================================\n";
        std::cout << "Art Lover System\n";
        std::cout << "==============================================================\n";
        std::cout << "Admin Menu:\n";
        std::cout << "--------------------------------------------------------------\n";
        std::cout << "1. Manage Moderators\n";
        std::cout << "2. Manage Museums\n";
        std::cout << "3. Manage Commission Shops\n";
}

// Moderator Menus
void Menu::artistMenu() {
    std::vector<Artist> artists;
    loadArtists(artists);
    std::cout << "==============================================================\n";
    std::cout << "Art Lover System\n";
    std::cout << "==============================================================\n";
    std::cout << "Artist Menu:\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "1. Create profile\n";


}

void Menu::collectorMenu() {
    std::vector<Collector> collectors;
    loadCollectors(collectors);
    std::cout << "==============================================================\n";
    std::cout << "Art Lover System\n";
    std::cout << "==============================================================\n";
    std::cout << "Collector Menu:\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Create profile\n";
}

void Menu::auctioneerMenu() {
    std::vector<Auctioneer> auctioneers;
    loadAuctioneers(auctioneers);
    std::cout << "==============================================================\n";
    std::cout << "Art Lover System\n";
    std::cout << "==============================================================\n";
    std::cout << "Auctioneer Menu:\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Create profile\n";

}

// Museum Menu
void Menu::museumMenu() {
    std::vector<Museum> museums;
    loadMuseums(museums);
    std::vector<Auctioneer> auctioneers;
    loadAuctioneers(auctioneers);
    std::cout << "==============================================================\n";
    std::cout << "Art Lover System\n";
    std::cout << "==============================================================\n";
    std::cout << "Museum Menu:\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Add new\n";
}

// Commission Shop Menu
void Menu::commissionShopMenu() {
    std::vector<CommissionShop> shops;
    loadShops(shops);
    std::cout << "==============================================================\n";
    std::cout << "Art Lover System\n";
    std::cout << "==============================================================\n";
    std::cout << "Commission Shop Menu:\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Add new\n";
}

