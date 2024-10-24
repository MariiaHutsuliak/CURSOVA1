#include "Menu.h"
#include "Admin.h"
#include "Artist.h"
#include "Collector.h"
#include "Auctioneer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

// File paths for persistence
const std::string ARTIST_FILE = "artists.txt";
const std::string COLLECTOR_FILE = "collectors.txt";
const std::string AUCTIONEER_FILE = "auctioneers.txt";

// Load and save functions for each role
void Menu::loadArtists(std::vector<Artist>& artists) {
    std::ifstream file(ARTIST_FILE);
    if (file.is_open()) {
        while (!file.eof()) {
            Artist artist;
            artist.setDataToObject(file);
            artists.push_back(artist);
        }
        file.close();
    }
}

void Menu::saveArtists(const std::vector<Artist>& artists) {
    std::ofstream file(ARTIST_FILE);
    for (const auto& artist : artists) {
        artist.getDataFromObject(file);
    }
    file.close();
}

void Menu::loadCollectors(std::vector<Collector>& collectors) {
    std::ifstream file(COLLECTOR_FILE);
    if (file.is_open()) {
        while (!file.eof()) {
            Collector collector;
            collector.setDataToObject(file);
            collectors.push_back(collector);
        }
        file.close();
    }
}

void Menu::saveCollectors(const std::vector<Collector>& collectors) {
    std::ofstream file(COLLECTOR_FILE);
    for (const auto& collector : collectors) {
        collector.getDataFromObject(file);
    }
    file.close();
}

void Menu::loadAuctioneers(std::vector<Auctioneer>& auctioneers) {
    std::ifstream file(AUCTIONEER_FILE);
    if (file.is_open()) {
        while (!file.eof()) {
            Auctioneer auctioneer;
            auctioneer.setDataToObject(file);
            auctioneers.push_back(auctioneer);
        }

        file.close();
    }
}

void Menu::saveAuctioneers(const std::vector<Auctioneer>& auctioneers) {
    std::ofstream file(AUCTIONEER_FILE);
    for (const auto& auctioneer : auctioneers) {
        auctioneer.getDataFromObject(file);
    }
    file.close();
}

// Moderator Menus
void Menu::artistMenu() {
    int choice;
    std::vector<Artist> artists;
    loadArtists(artists);

    do {
        std::cout << "Artist Menu:\n1. Add Artist\n2. View Artists\n3. Sort Artists\n0. Back\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                Artist::addArtist(artists);
                saveArtists(artists);
                break;
            case 2:
                for (const auto& artist : artists) {
                    artist.displayInfo();
                }
                break;
            case 3:
                Artist::sortArtistsByName(artists);
                break;
            case 0:
                return;
            default:
                std::cout << "Invalid option. Try again." << std::endl;
        }
    } while (choice != 0);
}

void Menu::collectorMenu() {
    int choice;
    std::vector<Collector> collectors;
    loadCollectors(collectors);

    do {
        std::cout << "Collector Menu:\n1. Add Collector\n2. View Collectors\n3. Sort Collectors\n0. Back\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                Collector::addCollector(collectors);
                saveCollectors(collectors);
                break;
            case 2:
                for (const auto& collector : collectors) {
                    collector.displayInfo();
                }
                break;
            case 3:
                Collector::sortCollectorsByName(collectors);
                break;
            case 0:
                return;
            default:
                std::cout << "Invalid option. Try again." << std::endl;
        }
    } while (choice != 0);
}

void Menu::auctioneerMenu() {
    int choice;
    std::vector<Auctioneer> auctioneers;
    loadAuctioneers(auctioneers);

    do {
        std::cout << "Auctioneer Menu:\n1. Add Auctioneer\n2. View Auctioneers\n3. List Auctioned Paintings\n0. Back\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                Auctioneer::addAuctioneer(auctioneers);
                saveAuctioneers(auctioneers);
                break;
            case 2:
                for (const auto& auctioneer : auctioneers) {
                    auctioneer.displayInfo();
                }
                break;
            case 3:
                for (const auto& auctioneer : auctioneers) {
                    auctioneer.listAuctionedPaintings();
                }
                break;
            case 0:
                return;
            default:
                std::cout << "Invalid option. Try again." << std::endl;
        }
    } while (choice != 0);
}