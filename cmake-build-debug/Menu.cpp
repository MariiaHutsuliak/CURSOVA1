#include "Menu.h"

Menu::Menu() {
    loadAllData();
}

void Menu::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::loadAllData() {
    Admin::getInstance().setUserName("admin");
    Admin::getInstance().setPassword("admin123");
    Admin::getInstance().saveAdmin();
    Admin::getInstance().loadAdmin();;

    Artist::loadArtists(artists);

    Collector::loadCollectors(collectors);

    Auctioneer::loadAuctioneers(auctioneers);

    Museum::loadMuseums(museums);

    CommissionShop::loadShops(shops);

    Painting::loadPaintings(paintings);
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
    std::string input;
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
        std::cout << "4. User Manual\n";
        std::cout << "0. Exit\n";
        std::cout << "===================================================================\n";
        std::cout << "Enter your choice: ";

        std::getline(std::cin, input);
        try {
            choice = std::stoi(input);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        } catch (const std::out_of_range&) {
            std::cout << "Input number is out of range. Please enter a valid option.\n";
            continue;
        }

        switch (choice) {
            case 1: userMenu(); break;
            case 2: moderatorMenu(); break;
            case 3: adminMenu(); break;
            case 4: userManual(); break;
            case 0: std::cout << "Exiting the system...\n"; break;
            default: std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}

void Menu::userManual() {
    std::cout << "===================================================================\n";
    std::cout << "User Manual for Art Lover System\n";
    std::cout << "===================================================================\n";
    std::cout << "The Art Lover System is designed for art enthusiasts to explore and manage\n";
    std::cout << "various aspects of the art world, including artists, collectors, museums,\n";
    std::cout << "auctioneers, and paintings. This guide provides instructions on how to\n";
    std::cout << "navigate the program and utilize its functionalities.\n\n";

    std::cout << "Main Menu Options:\n";
    std::cout << "1. Regular User: Access general information about artists, paintings,\n";
    std::cout << "   collectors, museums, and shops.\n";
    std::cout << "2. Moderator: Access to manage entities like artists, collectors,\n";
    std::cout << "   auctioneers, shops, museums. Requires a code word for entry.\n";
    std::cout << "3. Administrator: Full access to manage users, settings, and program data.\n";
    std::cout << "   Admin login required.\n";
    std::cout << "4. User Manual: View this manual anytime.\n";
    std::cout << "0. Exit: Close the program.\n\n";

    std::cout << "Detailed Information:\n";
    std::cout << "For further details on each menu item, please navigate to the corresponding\n";
    std::cout << "menu options after selecting Regular User, Moderator, or Administrator.\n";
    std::cout << "===================================================================\n";
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
        std::cout << "1. Manage Moderators\n";
        std::cout << "2. Delete Painting\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "===================================================================\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                Admin::manageModerators(artists, collectors, auctioneers, museums, shops);
                break;
            case 2:
                Painting::removePainting(paintings);
                saveAllData();
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                clearInput();
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

void Menu::moderatorMenu() {
    std::cout << "Enter Code Word: ";
    std::string codeWord = "moderator123";
    std::string input;
    std::cin >> input;
    clearInput();
    if (input == codeWord) {
        std::cout << "Successful entry!" << std::endl;
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
            std::cout << "4. Museum Menu\n";
            std::cout << "5. Commission Shop Menu\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "===================================================================\n";
            std::cout << "Enter your choice: ";

            if (!(std::cin >> typeChoice)) {
                std::cout << "Invalid input. Please enter a number.\n";
                clearInput();
                continue;
            }

            switch (typeChoice) {
                case 1: artistMenu(); break;
                case 2: collectorMenu(); break;
                case 3: auctioneerMenu(); break;
                case 4: museumMenu(); break;
                case 5: commissionShopMenu(); break;
                case 0: std::cout << "Returning to Main Menu...\n"; clearInput(); break;
                default: std::cout << "Invalid choice. Try again.\n";
            }
        } while (typeChoice != 0);
    } else {
        std::cout << "Wrong Code Word!" << std::endl;
    }
}

void Menu::museumMenu() {
    int choice;
    do {
        std::cout << "===================================================================\n";
        std::cout << "Art Lover System\n";
        std::cout << "===================================================================\n";
        std::cout << "Museum Menu:\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "1. Add Museum\n";
        std::cout << "2. View All Museums\n";
        std::cout << "3. Remove Painting from Museum\n";
        std::cout << "4. Sort Museums by Name\n";
        std::cout << "0. Back To Moderator Menu\n";
        std::cout << "===================================================================\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                museums.emplace_back();
                museums.back().input();
                saveAllData();
                break;
            case 2:
                for (const auto& museum : museums) museum.displayInfo();
                break;
            case 3:
                Museum::removePaintingFromMuseum(museums);
                break;
            case 4:
                Museum::sortMuseumsByName(museums);
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                clearInput();
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}

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
        std::cout << "6. Add new Painting\n";
        std::cout << "7. View All Paintings\n";
        std::cout << "8. Delete Painting\n";
        std::cout << "0. Back to Moderator Menu\n";
        std::cout << "===================================================================\n";
        std::cout << "Enter your choice: ";

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
            case 6:
                paintings.emplace_back();
                paintings.back().input();
                saveAllData();
                break;
            case 7:
                for (const auto& painting : paintings) painting.displayInfo();
                break;
            case 8:
                Painting::removePainting(paintings);
                saveAllData();
            case 0:
                std::cout << "Returning to Moderator Menu...\n";
                clearInput();
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
                break;
        }
    } while (choice != 0);
}

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
        std::cout << "Enter your choice: ";

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
                clearInput();
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}

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
        std::cout << "Enter your choice: ";

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
                    std::string paintingTitle;
                    std::cout << "Enter the title of the painting to auction: ";
                    std::cin.ignore();
                    std::getline(std::cin, paintingTitle);
                    auto paintingIt = std::find_if(paintings.begin(), paintings.end(),
                                                   [&paintingTitle](const Painting& painting) {
                                                       return painting.getTitle() == paintingTitle;
                                                   });

                    if (paintingIt == paintings.end()) {
                        std::cout << "Painting with title \"" << paintingTitle << "\" not found.\n";
                        return;
                    }
                    std::vector<Collector*> collectorPtrs;
                    for (auto& collector : collectors) {
                        collectorPtrs.push_back(&collector);
                    }
                    auctioneers[0].holdAuction(&(*paintingIt), collectorPtrs);
                    saveAllData();
                } else {
                    std::cout << "No paintings or collectors available for auction.\n";
                }
                break;
            }
            case 4:
                Auctioneer::sortAuctioneersByName(auctioneers);
                break;
            case 0:
                std::cout << "Returning to Moderator Menu...\n";
                clearInput();
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}

void Menu::commissionShopMenu() {
    int choice;

    do {
        std::cout << "===================================================================\n";
        std::cout << "Commission Shop Menu\n";
        std::cout << "===================================================================\n";
        std::cout << "1. View All Shops\n";
        std::cout << "2. Add New Shop\n";
        std::cout << "3. Buy Painting in Shop\n";
        std::cout << "4. Sell Painting from Shop\n";
        std::cout << "0. Back to Moderator Menu\n";
        std::cout << "===================================================================\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                for (const auto& shop : shops) shop.displayInfo();
                break;
            case 2: {
                CommissionShop newShop;
                newShop.input();
                shops.push_back(newShop);
                saveAllData();
                break;
            }
            case 3:
                CommissionShop::buyPaintingInShop(shops);
                saveAllData();
                break;

            case 4:
                CommissionShop::sellPaintingInShop(shops);
                saveAllData();
                break;
            case 0:
                std::cout << "Returning to main menu...\n";
                clearInput();
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}

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
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "5. View Artists\n";
        std::cout << "6. Sort Artists by Name\n";
        std::cout << "7. Search Artists by Name\n";
        std::cout << "8. Filter Artists by Style\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "9. View Auctioneers\n";
        std::cout << "10. Sort Auctioneers by Name\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "11. View Collectors\n";
        std::cout << "12. Sort Collectors by Name\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "13. View Museums\n";
        std::cout << "14. Sort Museums by Name\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "15. View Commission Shops\n";
        std::cout << "-------------------------------------------------------------------\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "===================================================================\n";
        std::cout << "Enter your choice: ";

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
            case 13:
                for (const auto& museum : museums) museum.displayInfo();
                break;
            case 14:
                Museum::sortMuseumsByName(museums);
                break;
            case 15:
                for (const auto& shop : shops) shop.displayInfo();
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                clearInput();
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}
