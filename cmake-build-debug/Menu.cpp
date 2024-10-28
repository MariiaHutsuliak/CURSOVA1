#include "Menu.h"

Menu::Menu() {
    std::cout << "Initializing Menu...\n";
    loadAllData();
    std::cout << "Finished initializing Menu.\n";
}

void Menu::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::loadAllData() {
    std::cout << "Loading all data...\n";
    Admin::getInstance().setUserName("admin");
    Admin::getInstance().setPassword("admin123");
    Admin::getInstance().saveAdmin();
    Admin::getInstance().loadAdmin();
    std::cout << "Admin data loaded.\n";

    Artist::loadArtists(artists);
    std::cout << "Artists loaded.\n";

    Collector::loadCollectors(collectors);
    std::cout << "Collectors loaded.\n";

    Auctioneer::loadAuctioneers(auctioneers);
    std::cout << "Auctioneers loaded.\n";

    Museum::loadMuseums(museums);
    std::cout << "Museums loaded.\n";

    CommissionShop::loadShops(shops);
    std::cout << "Shops loaded.\n";

    Painting::loadPaintings(paintings);
    std::cout << "Paintings loaded.\n";

    std::cout << "Finished loading all data.\n";
}

void Menu::saveAllData() {
    Admin::getInstance().saveAdmin();
    Artist::saveArtists(artists);
    Collector::saveCollectors(collectors);
    Auctioneer::saveAuctioneers(auctioneers);
    Museum::saveMuseums(museums);
    CommissionShop::saveShops(shops);
    Painting::savePaintings(paintings);
}

void Menu::mainMenu() {
    int choice;
    do {
        std::cout << "===================================================================\n";
        std::cout << "Welcome to the Art Lover System\n";
        std::cout << "===================================================================\n";
        std::cout << "Select your role:\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "1. Regular User\n";
        std::cout << "2. Moderator\n";
        std::cout << "3. Administrator\n";
        std::cout << "0. Exit\n";
        std::cout << "===================================================================\n";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: userMenu(); break;
            case 2: moderatorMenu(); break;
            case 3: adminMenu(); break;
            case 0: std::cout << "Exiting the system...\n"; break;
            default: std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}

void Menu::adminMenu() {
    if (!Admin::authenticateAdmin()) return;

    int choice;
    do {
        std::cout << "===================================================================\n";
        std::cout << "Art Lover System\n";
        std::cout << "===================================================================\n";
        std::cout << "Administrator Menu:\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "1. Change Admin Credentials\n";
        std::cout << "2. Manage Moderators\n";
        std::cout << "3. Delete Painting";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "===================================================================\n";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: {
                std::string newUserName, newPassword;
                std::cout << "Enter new admin username: ";
                std::cin >> newUserName;
                std::cout << "Enter new admin password: ";
                std::cin >> newPassword;
                Admin::getInstance().setUserName(newUserName);
                Admin::getInstance().setPassword(newPassword);
                saveAllData();
                break;
            }
            case 2:
                Admin::manageModerators(artists, collectors, auctioneers);
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

void Menu::moderatorMenu() {
    int typeChoice;
    do {
        std::cout << "===================================================================\n";
        std::cout << "Art Lover System\n";
        std::cout << "===================================================================\n";
        std::cout << "Moderator Menu:\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "1. Artist Menu\n";
        std::cout << "2. Collector Menu\n";
        std::cout << "3. Auctioneer Menu\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "===================================================================\n";

        if (!(std::cin >> typeChoice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (typeChoice) {
            case 1: artistMenu(); break;
            case 2: collectorMenu(); break;
            case 3: auctioneerMenu(); break;
            case 0: std::cout << "Returning to Main Menu...\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (typeChoice != 0);
}

// Artist menu
void Menu::artistMenu() {
    int choice;
    do {
        std::cout << "===================================================================\n";
        std::cout << "Art Lover System\n";
        std::cout << "===================================================================\n";
        std::cout << "Artist Menu:\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "1. Add New Artist\n";
        std::cout << "2. View All Artists\n";
        std::cout << "3. Sort Artists by Name\n";
        std::cout << "4. Search Artists by Name\n";
        std::cout << "5. Filter Artists by Style\n";
        std::cout << "0. Back to Moderator Menu\n";
        std::cout << "===================================================================\n";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                artists.emplace_back();
                artists.back().input();
                saveAllData();
                break;
            case 2:
                for (const auto& artist : artists) artist.displayInfo();
                break;
            case 3:
                Artist::sortArtistsByName(artists);
                break;
            case 4: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, name);

                auto results = Artist::searchArtistsByName(artists, name);
                for (const auto& artist : results) artist.displayInfo();
                break;
            }
            case 5: {
                std::string style;
                std::cout << "Enter style to filter: ";
                std::cin >> style;
                auto results = Artist::filterArtistsByStyle(artists, style);
                for (const auto& artist : results) artist.displayInfo();
                break;
            }
            case 0:
                std::cout << "Returning to Moderator Menu...\n";
                break;
            default:{
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice, please try again.\n";
                break;
            }

        }
    } while (choice != 0);
}

// Collector menu
void Menu::collectorMenu() {
    int choice;
    do {
        std::cout << "===================================================================\n";
        std::cout << "Art Lover System\n";
        std::cout << "===================================================================\n";
        std::cout << "Collector Menu:\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "1. Add New Collector\n";
        std::cout << "2. View All Collectors\n";
        std::cout << "3. Sort Collectors by Name\n";
        std::cout << "0. Back to Moderator Menu\n";
        std::cout << "===================================================================\n";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                collectors.emplace_back();
                collectors.back().input();
                saveAllData();
                break;
            case 2:
                for (const auto& collector : collectors) collector.displayInfo();
                break;
            case 3:
                Collector::sortCollectorsByName(collectors);
                break;
            case 0:
                std::cout << "Returning to Moderator Menu...\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}

// Auctioneer menu
void Menu::auctioneerMenu() {
    int choice;
    do {
        std::cout << "===================================================================\n";
        std::cout << "Art Lover System\n";
        std::cout << "===================================================================\n";
        std::cout << "Auctioneer Menu:\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "1. Add New Auctioneer\n";
        std::cout << "2. View All Auctioneers\n";
        std::cout << "3. Hold Auction\n";
        std::cout << "4. Sort Auctioneers by Name\n";
        std::cout << "0. Back to Moderator Menu\n";
        std::cout << "===================================================================\n";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                auctioneers.emplace_back();
                auctioneers.back().input();
                saveAllData();
                break;
            case 2:
                for (const auto& auctioneer : auctioneers) auctioneer.displayInfo();
                break;
            case 3: {
                if (!paintings.empty() && !collectors.empty()) {
                    std::vector<Collector*> collectorPtrs;
                    for (auto& collector : collectors) {
                        collectorPtrs.push_back(&collector);
                    }
                    Auctioneer::holdAuction(&paintings[0], collectorPtrs);
                    saveAllData();
                }
                break;
            }
            case 4:
                Auctioneer::sortAuctioneersByName(auctioneers);
                break;
            case 0:
                std::cout << "Returning to Moderator Menu...\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}

// User menu
void Menu::userMenu() {
    int choice;
    do {
        std::cout << "===================================================================\n";
        std::cout << "Art Lover System\n";
        std::cout << "===================================================================\n";
        std::cout << "User Menu:\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "1. View Paintings\n";
        std::cout << "2. Sort Paintings by Title\n";
        std::cout << "3. Search Paintings by Title\n";
        std::cout << "4. Filter Paintings by Genre\n";
        std::cout << "5. View Artists\n";
        std::cout << "6. Sort Artists by Name\n";
        std::cout << "7. Search Artists by Name\n";
        std::cout << "8. Filter Artists by Style\n";
        std::cout << "9. View Auctioneers\n";
        std::cout << "10. Sort Auctioneers by Name\n";
        std::cout << "11. View Collectors\n";
        std::cout << "12. Sort Collectors by Name\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "===================================================================\n";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                for (const auto& painting : paintings) painting.displayInfo();
                break;
            case 2:
                Painting::sortPaintingsByTitle(paintings);
                break;
            case 3: {
                std::string title;
                std::cout << "Enter title to search: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin,title);

                auto results = Painting::searchPaintingsByTitle(paintings, title);
                for (const auto& painting : results) painting.displayInfo();
                break;
            }
            case 4: {
                std::string genre;
                std::cout << "Enter genre to filter: ";
                std::cin >> genre;
                auto results = Painting::filterPaintingsByGenre(paintings, genre);
                for (const auto& painting : results) painting.displayInfo();
                break;
            }
            case 5:
                for (const auto& artist : artists) artist.displayInfo();
                break;
            case 6:
                Artist::sortArtistsByName(artists);
                break;
            case 7: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, name);

                auto results = Artist::searchArtistsByName(artists, name);
                for (const auto& artist : results) artist.displayInfo();
                break;
            }
            case 8: {
                std::string style;
                std::cout << "Enter style to filter: ";
                std::cin >> style;
                auto results = Artist::filterArtistsByStyle(artists, style);
                for (const auto& artist : results) artist.displayInfo();
                break;
            }
            case 9:
                for (const auto& auctioneer : auctioneers) auctioneer.displayInfo();
                break;
            case 10:
                Auctioneer::sortAuctioneersByName(auctioneers);
                break;
            case 11:
                for (const auto& collector : collectors) collector.displayInfo();
                break;
            case 12:
                Collector::sortCollectorsByName(collectors);
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}
