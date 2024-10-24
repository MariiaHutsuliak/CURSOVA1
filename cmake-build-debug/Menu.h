#ifndef CURSOVA_MENU_H
#define CURSOVA_MENU_H
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "Admin.h"
#include "Artist.h"
#include "Collector.h"
#include "Auctioneer.h"
#include "Painting.h"
#include "FileManager.h"
#include "Serializable.h"
#include "CommissionShop.h"
#include "Museum.h"
#include "Person.h"

class Menu {
private:
     Admin admin; // Admin object for authentication and role management
    Artist artist; // Artist object for artist-specific actions
    Collector collector; // Collector object for collector-specific actions
    Auctioneer auctioneer; // Auctioneer object for auction-related actions
    Painting painting; // Painting object to manage paintings
    CommissionShop commissionShop; // CommissionShop object for shop-related actions
    Museum museum; // Museum object for museum-related actions
    FileManager fileManager; // FileManager object for file operations

    vector<Painting> paintings;
    vector<Artist> artists;

    static bool mainMenu();
    static void showPainting(Painting painting1);


//
//     bool authenticateAdmin(); // Method to authenticate admin
//     bool authenticateModerator(); // Method to authenticate moderator
//     void showAdminMenu(); // Admin-specific actions
//    void showModeratorMenu(); // Moderator-specific actions
//     void showViewerMenu(); // Viewer-specific actions
//    static void showMainMenu(); // Displays the main menu
//
//    void manageArtists(); // Admin and moderator functionality
//    void manageCollectors(); // Admin and moderator functionality
//    void manageAuctions(); // Admin and moderator functionality
//    static void viewPaintings(); // Function to view paintings (for all roles)
//
//public:
//    static void start(); // Entry point to start the menu
};

#endif //CURSOVA_MENU_H
