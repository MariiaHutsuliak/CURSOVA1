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
public:
    // Moderator Menus
    void artistMenu();        // Handles artist-specific actions
    void collectorMenu();     // Handles collector-specific actions
    void auctioneerMenu();    // Handles auctioneer-specific actions

    // File Loaders
    void loadArtists(std::vector<Artist>& artists);         // Load artists from file
    void saveArtists(const std::vector<Artist>& artists);   // Save artists to file

    void loadCollectors(std::vector<Collector>& collectors);         // Load collectors from file
    void saveCollectors(const std::vector<Collector>& collectors);   // Save collectors to file

    void loadAuctioneers(std::vector<Auctioneer>& auctioneers);         // Load auctioneers from file
    void saveAuctioneers(const std::vector<Auctioneer>& auctioneers);   // Save auctioneers to file

private:
    // File paths for persistence
    const std::string ARTIST_FILE = "artists.txt";
    const std::string COLLECTOR_FILE = "collectors.txt";
    const std::string AUCTIONEER_FILE = "auctioneers.txt";
};


#endif //CURSOVA_MENU_H
