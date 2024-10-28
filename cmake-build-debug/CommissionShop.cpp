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

void CommissionShop::addCommissionShop(std::vector<CommissionShop>& shops) {
    CommissionShop shop;
    std::regex latinRegex("^[A-Za-z\\s]+$");

    std::cout << "Enter the name for the new shop: ";
    std::cin.ignore();
    std::getline(std::cin, shop.name);
    while (shop.name.empty() || !std::regex_match(shop.name, latinRegex)) {
        std::cout << "Invalid name. Please use only Latin letters and spaces: ";
        std::getline(std::cin, shop.name);
    }
    shops.push_back(std::move(shop));
}

void CommissionShop::addPainting(const std::string& painting, double price) {
    std::regex latinRegex("^[A-Za-z\\s]+$");
    if (price <= 0) {
        std::cout << "Price must be greater than zero. Please enter a valid price.\n";
        return;
    }
    if (!std::regex_match(painting, latinRegex)) {
        std::cout << "Invalid painting name. Please use only Latin letters and spaces.\n";
        return;
    }
    if (paintingsForSale.find(painting) != paintingsForSale.end()) {
        std::cout << "Painting is already in the commission shop. Cannot add duplicate.\n";
        return;
    }
    paintingsForSale[painting] = price;
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

    std::string painting;
    double price;
    std::regex latinRegex("^[A-Za-z\\s]+$");

    std::cout << "Enter name of painting for sale: ";
    std::cin.ignore();
    std::getline(std::cin, painting);
    while (painting.empty() || !std::regex_match(painting, latinRegex)) {
        std::cout << "Invalid painting name. Please use only Latin letters and spaces: ";
        std::getline(std::cin, painting);
    }

    std::cout << "Enter price: ";
    while (!(std::cin >> price) || price <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive price: ";
    }

    shops[0].buyPainting(painting, price);
    std::cout << "Painting bought by commission shop: " << painting << "\n";
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
    if (file.is_open()) {
        if (file.peek() == std::ifstream::traits_type::eof()) {
            return;
        }
        while (!file.eof()) {
            CommissionShop shop;
            shop.setDataToObject(file);
            shops.push_back(shop);
        }
        file.close();
    }
}

void CommissionShop::saveShops(const std::vector<CommissionShop>& shops) {
    std::ofstream file(SHOP_FILE);
    for (const auto& shop : shops) {
        shop.getDataFromObject(file);
    }
    file.close();
}
