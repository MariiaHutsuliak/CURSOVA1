#include "CommissionShop.h"

CommissionShop::CommissionShop() : name("Unnamed Shop") {}

CommissionShop::CommissionShop(const std::string& name, const std::map<std::string, double>& paintingsForSale)
        : name(name), paintingsForSale(paintingsForSale) {}

CommissionShop::CommissionShop(const CommissionShop& other)
        : name(other.name), paintingsForSale(other.paintingsForSale) {}

CommissionShop::CommissionShop(CommissionShop&& other) noexcept
        : name(std::move(other.name)), paintingsForSale(std::move(other.paintingsForSale)) {}

CommissionShop& CommissionShop::operator=(const CommissionShop& other) {
    if (this == &other) return *this;
    name = other.name;
    paintingsForSale = other.paintingsForSale;
    return *this;
}

CommissionShop& CommissionShop::operator=(CommissionShop&& other) noexcept {
    if (this == &other) return *this;
    name = std::move(other.name);
    paintingsForSale = std::move(other.paintingsForSale);
    return *this;
}

CommissionShop::~CommissionShop() {}

void CommissionShop::setName(const std::string& name) {
    this->name = name;
}

std::string CommissionShop::getName() const {
    return name;
}

void CommissionShop::input() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Regex for validating painting title and shop name
    std::regex latinRegex("^[A-Za-z\\s]+$");

    // Input for shop name with validation
    while (true) {
        try {
            std::cout << "Enter the name of the shop: ";
            std::getline(std::cin, name);
            if (name.empty() || !std::regex_match(name, latinRegex)) {
                throw std::runtime_error("Invalid shop name.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input. Please use only Latin letters and spaces for the shop name.\n";
        }
    }

    // Input for paintings for sale
    int numPaintings;
    std::cout << "Enter the number of paintings to add to the shop: ";
    while (!(std::cin >> numPaintings) || numPaintings < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a positive integer for the number of paintings: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline

    paintingsForSale.clear(); // Clear existing entries in case of re-input

    for (int i = 0; i < numPaintings; ++i) {
        std::string paintingTitle;
        double price;

        // Input and validate painting title
        while (true) {
            std::cout << "Enter the title for painting #" << (i + 1) << " (Latin letters only): ";
            std::getline(std::cin, paintingTitle);
            if (std::regex_match(paintingTitle, latinRegex)) {
                break;
            }
            std::cout << "Invalid input. Please use only Latin letters and spaces for the painting title.\n";
        }

        // Input and validate price
        std::cout << "Enter the price for painting #" << (i + 1) << ": ";
        while (!(std::cin >> price) || price <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive price: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline after the price

        // Add the painting to the paintingsForSale map
        paintingsForSale[paintingTitle] = price;
    }
}

void CommissionShop::buyPainting(const std::string& painting, double price) {
    std::regex latinRegex("^[A-Za-z\\s]+$");
    if (!std::regex_match(painting, latinRegex)) {
        std::cout << "Invalid painting name. Please use only Latin letters and spaces.\n";
        return;
    }
    if (paintingsForSale.find(painting) != paintingsForSale.end()) {
        std::cout << "Painting is already in the shop. Cannot buy duplicate.\n";
        return;
    }
    if (price <= 0) {
        std::cout << "Price must be greater than zero. Please enter a valid price.\n";
        return;
    }
    paintingsForSale[painting] = price * 2;
}

void CommissionShop::sellPainting(const std::string& painting) {
    auto it = paintingsForSale.find(painting);
    if (it == paintingsForSale.end()) {
        std::cout << "Painting not found in the commission shop. Please check the name.\n";
        return;
    }
    paintingsForSale.erase(it);
    std::cout << "Painting sold: " << painting << "\n";
}

void CommissionShop::displayInfo() const {
    std::cout << "Shop Name: " << name << "\n";
    std::cout << "Paintings for sale:\n";
    if (paintingsForSale.empty()) {
        std::cout << "No paintings available for sale.\n";
        return;
    }
    for (const auto& pair : paintingsForSale) {
        std::cout << pair.first << " ($" << pair.second << ")\n";
    }
}

void CommissionShop::buyPaintingInShop(std::vector<CommissionShop>& shops) {
    if (shops.empty()) {
        std::cout << "No commission shops available.\n";
        return;
    }

    std::string shopName;
    std::cout << "Enter the name of the shop to buy a painting: ";
    std::cin.ignore(); // Clear the newline from any previous input
    std::getline(std::cin, shopName);

    // Find the shop by name
    auto it = std::find_if(shops.begin(), shops.end(), [&shopName](const CommissionShop& shop) {
        return shop.getName() == shopName;
    });

    if (it == shops.end()) {
        std::cout << "Shop not found. Please check the name and try again.\n";
        return;
    }

    // Shop found, proceed with buying a painting
    std::string painting;
    double price;
    std::regex latinRegex("^[A-Za-z\\s]+$");

    std::cout << "Enter the title of the painting to buy: ";
    std::getline(std::cin, painting);
    while (painting.empty() || !std::regex_match(painting, latinRegex)) {
        std::cout << "Invalid painting name. Please use only Latin letters and spaces: ";
        std::getline(std::cin, painting);
    }

    std::cout << "Enter the price: ";
    while (!(std::cin >> price) || price <= 0) {
        std::cout << "Invalid input. Please enter a valid positive price: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline after the price

    // Attempt to buy the painting and check if added successfully
    size_t initialSize = it->paintingsForSale.size();
    it->buyPainting(painting, price);
    if (it->paintingsForSale.size() > initialSize) {
        std::cout << "Painting bought by shop: " << it->getName() << "\n";
    } else {
        std::cout << "Failed to buy the painting. It may already be in the shop.\n";
    }
}

void CommissionShop::sellPaintingInShop(std::vector<CommissionShop>& shops) {
    if (shops.empty()) {
        std::cout << "No commission shops available.\n";
        return;
    }

    std::string shopName;
    std::cout << "Enter the name of the shop to sell a painting from: ";
    std::cin.ignore(); // Clear the newline from any previous input
    std::getline(std::cin, shopName);

    // Find the shop by name
    auto it = std::find_if(shops.begin(), shops.end(), [&shopName](const CommissionShop& shop) {
        return shop.getName() == shopName;
    });

    if (it == shops.end()) {
        std::cout << "Shop not found. Please check the name and try again.\n";
        return;
    }

    // Shop found, proceed with selling a painting
    std::string painting;
    std::cout << "Enter the title of the painting to sell: ";
    std::getline(std::cin, painting);

    // Attempt to sell the painting and check if removed successfully
    size_t initialSize = it->paintingsForSale.size();
    it->sellPainting(painting);
    if (it->paintingsForSale.size() < initialSize) {
        std::cout << "Painting sold by shop: " << it->getName() << "\n";
    } else {
        std::cout << "Failed to sell the painting. It may not exist in the shop.\n";
    }
}

void CommissionShop::getDataFromObject(std::ostream& os) const {
    os << name << '\n';
    os << paintingsForSale.size() << '\n';
    for (const auto& pair : paintingsForSale) {
        os << pair.first << '\n' << pair.second << '\n';
    }
}

void CommissionShop::setDataToObject(std::istream& is) {
    std::getline(is, name);
    size_t size;
    is >> size;
    is.ignore();
    for (size_t i = 0; i < size; ++i) {
        std::string paintingName;
        double price;
        std::getline(is, paintingName);
        is >> price;
        is.ignore();
        paintingsForSale[paintingName] = price;
    }
}

void CommissionShop::loadShops(std::vector<CommissionShop>& shops) {
    std::ifstream file(SHOP_FILE);
    if (!file.is_open()) {
        std::cerr << "Error opening collector file.\n";
        return;
    }

    shops.clear();
    while (file.peek() != std::ifstream::traits_type::eof()) {
        CommissionShop shop;
        shop.setDataToObject(file);

        // Check for failed data read to avoid pushing incomplete collectors
        if (!file.fail()) {
            shops.push_back(shop);
        }
    }

    file.close();
}

void CommissionShop::saveShops(const std::vector<CommissionShop>& shops) {
    std::ofstream file(SHOP_FILE);
    for (const auto& shop : shops) {
        shop.getDataFromObject(file);
    }
    file.close();
}
