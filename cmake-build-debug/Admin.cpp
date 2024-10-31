#include "Admin.h"

Admin::Admin() : userName("admin"), password("password") {}

Admin& Admin::getInstance() {
    static Admin instance;
    return instance;
}

const std::string &Admin::getUserName() const { return userName; }
void Admin::setUserName(const std::string &userName) { this->userName = userName; }

const std::string &Admin::getPassword() const { return password; }
void Admin::setPassword(const std::string &password) { this->password = password; }

bool Admin::authenticateAdmin() {
    Admin& admin = getInstance();
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;

    if (admin.userName == username && admin.password == password) {
        std::cout << "Authentication successful!\n";
        return true;
    } else {
        std::cout << "Invalid credentials!\n";
        return false;
    }
}

void Admin::manageModerators(std::vector<Artist>& artists, std::vector<Collector>& collectors, std::vector<Auctioneer>& auctioneers,
                            std::vector<Museum>& museums, std::vector<CommissionShop>& shops) {
    int typeChoice, actionChoice;
    do {
        std::cout << "Select Moderator Type:\n";
        std::cout << "1. Artist\n";
        std::cout << "2. Collector\n";
        std::cout << "3. Auctioneer\n";
        std::cout << "4. Museum\n";
        std::cout << "5. Commission Shop\n";
        std::cout << "0. Back\n";
        std::cin >> typeChoice;

        if (typeChoice == 0) return;

        std::cout << "Choose Action:\n";
        std::cout << "1. Add\n";
        std::cout << "2. Remove\n";
        std::cout << "3. View All\n";
        std::cout << "0. Back\n";
        std::cin >> actionChoice;

        if (actionChoice == 0) continue;

        switch (typeChoice) {
            case 1:
                manageSpecificModerator(artists, actionChoice);
                break;
            case 2:
                manageSpecificModerator(collectors, actionChoice);
                break;
            case 3:
                manageSpecificModerator(auctioneers, actionChoice);
                break;
            case 4:
                manageSpecificModerator(museums, actionChoice);
                break;
            case 5:
                manageSpecificModerator(shops, actionChoice);
                break;
            default:
                std::cout << "Invalid moderator type. Try again.\n";
        }
    } while (typeChoice != 0);
}

template<typename T>
void Admin::manageSpecificModerator(std::vector<T>& moderators, int actionChoice) {
    switch (actionChoice) {
        case 1:
            addModerator(moderators);
            break;
        case 2:
            removeModerator(moderators);
            break;
        case 3:
            viewModerators(moderators);
            break;
        default:
            std::cout << "Invalid action. Try again.\n";
    }
}

template <typename T>
void Admin::saveModeratorsToFile(const std::vector<T>& moderators, const char* fileName) {
    std::ofstream file(fileName, std::ios::trunc);
    if (file.is_open()) {
        for (const auto& moderator : moderators) {
            moderator.getDataFromObject(file);
        }
        file.close();
    }
}

template <typename T>
void Admin::addModerator(std::vector<T>& moderators) {
    T newModerator;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    newModerator.input();
    moderators.push_back(std::move(newModerator));
    std::cout << "Moderator added successfully.\n";

    if constexpr (std::is_same<T, Artist>::value) {
        saveModeratorsToFile(moderators, ARTIST_FILE);
    } else if constexpr (std::is_same<T, Collector>::value) {
        saveModeratorsToFile(moderators, COLLECTOR_FILE);
    } else if constexpr (std::is_same<T, Auctioneer>::value) {
        saveModeratorsToFile(moderators, AUCTIONEER_FILE);
    } else if constexpr (std::is_same<T, Museum>::value) {
        saveModeratorsToFile(moderators, MUSEUM_FILE);
    } else if constexpr (std::is_same<T, CommissionShop>::value) {
        saveModeratorsToFile(moderators, SHOP_FILE);
    }
}

template <typename T>
void Admin::removeModerator(std::vector<T>& moderators) {
    std::string name;
    std::cout << "Enter the username of the moderator to remove: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    auto it = std::find_if(moderators.begin(), moderators.end(), [&](const T& mod) {
        return mod.getName() == name;
    });

    if (it != moderators.end()) {
        moderators.erase(it);
        std::cout << "Moderator removed successfully.\n";

        if constexpr (std::is_same<T, Artist>::value) {
            saveModeratorsToFile(moderators, ARTIST_FILE);
        } else if constexpr (std::is_same<T, Collector>::value) {
            saveModeratorsToFile(moderators, COLLECTOR_FILE);
        } else if constexpr (std::is_same<T, Auctioneer>::value) {
            saveModeratorsToFile(moderators, AUCTIONEER_FILE);
        } else if constexpr (std::is_same<T, Museum>::value) {
            saveModeratorsToFile(moderators, MUSEUM_FILE);
        } else if constexpr (std::is_same<T, CommissionShop>::value) {
            saveModeratorsToFile(moderators, SHOP_FILE);
        }
    } else {
        std::cout << "Moderator not found.\n";
    }
}

template <typename T>
void Admin::viewModerators(const std::vector<T>& moderators) {
    if (moderators.empty()) {
        std::cout << "No moderators found.\n";
    } else {
        std::cout << "List of Moderators:\n";
        for (const auto& mod : moderators) {
            mod.displayInfo();
        }
    }
}

void Admin::getDataFromObject(std::ostream &os) const {
    os << userName << std::endl;
    os << password << std::endl;
}

void Admin::setDataToObject(std::istream &is) {
    std::getline(is, userName);
    std::getline(is, password);
}

void Admin::loadAdmin() {
    std::ifstream file(ADMIN_FILE);
    if (file.is_open()) {
        setDataToObject(file);
        file.close();
    }
}

void Admin::saveAdmin() const {
    std::ofstream file(ADMIN_FILE);
    if (file.is_open()) {
        getDataFromObject(file);
        file.close();
    }
}