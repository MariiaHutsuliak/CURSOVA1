#include "Menu.h"

bool Menu::mainMenu() {
    int choice;
    cin >> choice;
    switch (choice) {
        case 1 :{

        }


    }
}

void Menu::showPainting(Painting painting1) {
    painting1.displayInfo(paintings);
}
//bool Menu::authenticateAdmin() {
//    std::string username, password;
//    std::cout << "Enter admin username: ";
//    std::cin >> username;
//    std::cout << "Enter admin password: ";
//    std::cin >> password;
//
//    // For simplicity, we are just checking hardcoded credentials
//    if (username == "admin" && password == "adminpass") {
//        admin.setRole(AdminRole::SUPER_ADMIN);
//        return true;
//    }
//    std::cout << "Invalid admin credentials!" << std::endl;
//    return false;
//}
//
//bool Menu::authenticateModerator() {
//    std::string username, password;
//    std::cout << "Enter moderator username: ";
//    std::cin >> username;
//    std::cout << "Enter moderator password: ";
//    std::cin >> password;
//
//    // For simplicity, we are just checking hardcoded credentials
//    if (username == "moderator" && password == "modpass") {
//        admin.setRole(AdminRole::ADMIN);
//        return true;
//    }
//    std::cout << "Invalid moderator credentials!" << std::endl;
//    return false;
//}
//
//void Menu::showAdminMenu() {
//    int choice;
//    do {
//        std::cout << "Admin Menu:\n";
//        std::cout << "1. Manage Artists\n2. Manage Collectors\n3. Manage Auctions\n4. View Paintings\n5. Exit\nEnter your choice: ";
//        std::cin >> choice;
//
//        switch (choice) {
//            case 1:
//                manageArtists();
//                break;
//            case 2:
//                manageCollectors();
//                break;
//            case 3:
//                manageAuctions();
//                break;
//            case 4:
//                viewPaintings();
//                break;
//            case 5:
//                std::cout << "Exiting Admin Menu..." << std::endl;
//                break;
//            default:
//                std::cout << "Invalid choice!" << std::endl;
//                break;
//        }
//    } while (choice != 5);
//}
//
//void Menu::showModeratorMenu() {
//    int choice;
//    do {
//        std::cout << "Moderator Menu:\n";
//        std::cout << "1. Manage Artists\n2. Manage Collectors\n3. View Paintings\n4. Exit\nEnter your choice: ";
//        std::cin >> choice;
//
//        switch (choice) {
//            case 1:
//                manageArtists();
//                break;
//            case 2:
//                manageCollectors();
//                break;
//            case 3:
//                viewPaintings();
//                break;
//            case 4:
//                std::cout << "Exiting Moderator Menu..." << std::endl;
//                break;
//            default:
//                std::cout << "Invalid choice!" << std::endl;
//        }
//    } while (choice != 4);
//}
//
//void Menu::showViewerMenu() {
//    std::cout << "Viewer Menu:\n";
//    viewPaintings(); // View-only access for paintings
//}
//
//void Menu::showMainMenu() {
//    int choice;
//    std::cout << "1. Admin Login\n2. Moderator Login\n3. Viewer Access\nEnter your choice: ";
//    std::cin >> choice;
//    switch (choice) {
//        case 1:
//            if (authenticateAdmin()) {
//                showAdminMenu();
//            }
//            break;
//        case 2:
//            if (authenticateModerator()) {
//                showModeratorMenu();
//            }
//            break;
//        case 3:
//            showViewerMenu();
//            break;
//        default:
//            std::cout << "Invalid choice!" << std::endl;
//    }
//}
//
// void Menu::start() {
//    showMainMenu();
//}
//
//void Menu::manageArtists() {
//    std::cout << "Managing artists...\n";
//    // Here you would call functions related to artists, such as adding, removing, or viewing artists
//}
//
//void Menu::manageCollectors() {
//    std::cout << "Managing collectors...\n";
//    // Here you would call functions related to collectors, such as adding, removing, or viewing collectors
//}
//
//void Menu::manageAuctions() {
//    std::cout << "Managing auctions...\n";
//    // Here you would call functions related to auction management, such as scheduling or viewing auctions
//}
//
//void Menu::viewPaintings() {
//    std::cout << "Viewing paintings...\n";
//    // Here you would use the Painting class to list available paintings
//}
