#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include "DataHandler.h"
#include "Person.h"
#include "Artist.h"
#include "Painting.h"
#include "Collector.h"
#include "Museum.h"
#include "Auctioneer.h"
#include "CommissionShop.h"

using namespace std;

void showMainMenu() {
    cout << "1. Add/Create\n";
    cout << "2. View/Purchase\n";
    cout << "3. Save Data\n";
    cout << "4. Load Data\n";
    cout << "5. Instructions\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

void showCreateMenu() {
    cout << "1. Add artist\n";
    cout << "2. Add painting\n";
    cout << "3. Add collector\n";
    cout << "4. Add museum\n";
    cout << "5. Add auctioneer\n";
    cout << "6. Add commission shop\n";
    cout << "7. Back\n";
    cout << "Choose an option: ";
}

void showViewMenu() {
    cout << "1. Buy painting in commission shop\n";
    cout << "2. View data\n";
    cout << "3. Sort data\n";
    cout << "4. Filter data\n";
    cout << "5. Search data\n";
    cout << "6. Back\n";
    cout << "Choose an option: ";
}

void showInstructions() {
    cout << "Instructions:\n";
    cout << "1. Use the menu to add new records for artists, paintings, collectors, museums, auctioneers, and commission shops.\n";
    cout << "2. To save data to a file, choose option 3 in the main menu.\n";
    cout << "3. To load data from a file, choose option 4 in the main menu.\n";
    cout << "4. Use the appropriate options to view and edit data.\n";
}

void saveData(const vector<Artist>& artists, const vector<Painting>& paintings,
              const vector<Collector>& collectors, const vector<Museum>& museums,
              const vector<Auctioneer>& auctioneers, const vector<CommissionShop>& shops) {
    ofstream outFile("data.txt");
    if (!outFile) {
        cerr << "Failed to open file for writing.\n";
        return;
    }

    outFile << artists.size() << "\n";
    for (const auto& artist : artists) {
        artist.save(outFile);
    }

    outFile << paintings.size() << "\n";
    for (const auto& painting : paintings) {
        painting.save(outFile);
    }

    outFile << collectors.size() << "\n";
    for (const auto& collector : collectors) {
        collector.save(outFile);
    }

    outFile << museums.size() << "\n";
    for (const auto& museum : museums) {
        museum.save(outFile);
    }

    outFile << auctioneers.size() << "\n";
    for (const auto& auctioneer : auctioneers) {
        auctioneer.save(outFile);
    }

    outFile << shops.size() << "\n";
    for (const auto& shop : shops) {
        shop.save(outFile);
    }

    outFile.close();
}

void loadData(vector<Artist>& artists, vector<Painting>& paintings,
              vector<Collector>& collectors, vector<Museum>& museums,
              vector<Auctioneer>& auctioneers, vector<CommissionShop>& shops) {
    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "Failed to open file for reading.\n";
        return;
    }

    size_t size;
    inFile >> size;
    inFile.ignore();
    artists.resize(size);
    for (auto& artist : artists) {
        artist.load(inFile);
    }

    inFile >> size;
    inFile.ignore();
    paintings.resize(size);
    for (auto& painting : paintings) {
        painting.load(inFile, artists);
    }

    inFile >> size;
    inFile.ignore();
    collectors.resize(size);
    for (auto& collector : collectors) {
        collector.load(inFile,artists);
    }

    inFile >> size;
    inFile.ignore();
    museums.resize(size);
    for (auto& museum : museums) {
        museum.load(inFile,artists);
    }

    inFile >> size;
    inFile.ignore();
    auctioneers.resize(size);
    for (auto& auctioneer : auctioneers) {
        auctioneer.load(inFile);
    }

    inFile >> size;
    inFile.ignore();
    shops.resize(size);
    for (auto& shop : shops) {
        shop.load(inFile);
    }

    inFile.close();
}

void viewData(const vector<Artist>& artists, const vector<Painting>& paintings,
              const vector<Collector>& collectors, const vector<Museum>& museums,
              const vector<Auctioneer>& auctioneers, const vector<CommissionShop>& shops) {
    cout << "Artists:\n";
    for (const auto& artist : artists) {
        artist.displayInfo();
    }

    cout << "Paintings:\n";
    for (const auto& painting : paintings) {
        painting.displayInfo();
    }

    cout << "Collectors:\n";
    for (const auto& collector : collectors) {
        collector.displayInfo();
    }

    cout << "Museums:\n";
    for (const auto& museum : museums) {
        museum.displayInfo();
    }

    cout << "Auctioneers:\n";
    for (const auto& auctioneer : auctioneers) {
        auctioneer.displayInfo();
    }

    cout << "Commission Shops:\n";
    for (const auto& shop : shops) {
        shop.displayInfo();
    }
}

void sortData(vector<Artist>& artists, vector<Painting>& paintings,
              vector<Collector>& collectors, vector<Museum>& museums,
              vector<Auctioneer>& auctioneers) {
    int choice;
    cout << "1. Sort artists by name\n";
    cout << "2. Sort paintings by title\n";
    cout << "3. Sort collectors by name\n";
    cout << "4. Sort museums by name\n";
    cout << "5. Sort auctioneers by name\n";
    cout << "Choose an option: ";
    cin >> choice;

    switch (choice) {
        case 1:
            Artist::sortArtistsByName(artists);
            break;
        case 2:
            Painting::sortPaintingsByTitle(paintings);
            break;
        case 3:
            Collector::sortCollectorsByName(collectors);
            break;
        case 4:
            Museum::sortMuseumsByName(museums);
            break;
        case 5:
            Auctioneer::sortAuctioneersByName(auctioneers);
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
    }
}

void filterData(const vector<Artist>& artists, const vector<Painting>& paintings) {
    int choice;
    string key;
    cout << "1. Filter artists by style\n";
    cout << "2. Filter paintings by genre\n";
    cout << "Choose an option: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            cout << "Enter style: ";
            getline(cin, key);
            {
                auto filteredArtists = Artist::filterArtistsByStyle(artists, key);
                for (const auto& artist : filteredArtists) {
                    artist.displayInfo();
                }
            }
            break;
        case 2:
            cout << "Enter genre: ";
            getline(cin, key);
            {
                auto filteredPaintings = Painting::filterPaintingsByGenre(paintings, key);
                for (const auto& painting : filteredPaintings) {
                    painting.displayInfo();
                }
            }
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
    }
}

void searchData(const vector<Artist>& artists, const vector<Painting>& paintings) {
    int choice;
    string key;
    cout << "1. Search artists by name\n";
    cout << "2. Search paintings by title\n";
    cout << "Choose an option: ";
    cin >> choice;
    cin.ignore();  // Ignore remaining newline

    switch (choice) {
        case 1:
            cout << "Enter name: ";
            getline(cin, key);
            {
                auto foundArtists = Artist::searchArtistsByName(artists, key);
                for (const auto& artist : foundArtists) {
                    artist.displayInfo();
                }
            }
            break;
        case 2:
            cout << "Enter title: ";
            getline(cin, key);
            {
                auto foundPaintings = Painting::searchPaintingsByTitle(paintings, key);
                for (const auto& painting : foundPaintings) {
                    painting.displayInfo();
                }
            }
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
    }
}

int main() {
    vector<Artist> artists;
    vector<Painting> paintings;
    vector<Collector> collectors;
    vector<Museum> museums;
    vector<Auctioneer> auctioneers;
    vector<CommissionShop> shops;

    int mainChoice;
    int subChoice;
    do {
        showMainMenu();
        while (!(cin >> mainChoice)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please enter a number: ";
        }

        switch (mainChoice) {
            case 1: // Add/Create
                do {
                    showCreateMenu();
                    while (!(cin >> subChoice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number: ";
                    }

                    switch (subChoice) {
                        case 1:
                            Artist::addArtist(artists);
                            break;
                        case 2:
                            Painting::addPainting(paintings, artists);
                            break;
                        case 3:
                            Collector::addCollector(collectors);
                            break;
                        case 4:
                            Museum::addMuseum(museums);
                            break;
                        case 5:
                            Auctioneer::addAuctioneer(auctioneers);
                            break;
                        case 6:
                            CommissionShop::addCommissionShop(shops);
                            break;
                        case 7:
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (subChoice != 7);
                break;
            case 2: // View/Purchase
                do {
                    showViewMenu();
                    while (!(cin >> subChoice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number: ";
                    }

                    switch (subChoice) {
                        case 1:
                            CommissionShop::buyPaintingInShop(shops);
                            break;
                        case 2:
                            viewData(artists, paintings, collectors, museums, auctioneers, shops);
                            break;
                        case 3:
                            sortData(artists, paintings, collectors, museums, auctioneers);
                            break;
                        case 4:
                            filterData(artists, paintings);
                            break;
                        case 5:
                            searchData(artists, paintings);
                            break;
                        case 6:
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                    }
                } while (subChoice != 6);
                break;
            case 3:
                saveData(artists, paintings, collectors, museums, auctioneers, shops);
                break;
            case 4:
                loadData(artists, paintings, collectors, museums, auctioneers, shops);
                break;
            case 5:
                showInstructions();
                break;
            case 6:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (mainChoice != 6);

    return 0;
}
