#include "CommissionShop.h"
#include <stdexcept>
#include <vector>

CommissionShop::CommissionShop() {}

CommissionShop::CommissionShop(const std::map<std::string, double>& paintingsForSale)
        : paintingsForSale(paintingsForSale) {}

CommissionShop::CommissionShop(const CommissionShop& other)
        : paintingsForSale(other.paintingsForSale) {}

CommissionShop::CommissionShop(CommissionShop&& other) noexcept
        : paintingsForSale(other.paintingsForSale) {}

CommissionShop& CommissionShop::operator=(const CommissionShop& other) {
    if (this == &other) return *this;
    paintingsForSale = other.paintingsForSale;
    return *this;
}

CommissionShop& CommissionShop::operator=(CommissionShop&& other) noexcept {
    if (this == &other) return *this;
    paintingsForSale = std::move(other.paintingsForSale);
    return *this;
}

CommissionShop::~CommissionShop() {}

void CommissionShop::addCommissionShop(std::vector<CommissionShop>& shops) {
    CommissionShop shop;
    shops.push_back(std::move(shop));
}

void CommissionShop::addPainting(const std::string& painting, double price) {
    if (price <= 0) {
        throw std::invalid_argument("Price must be greater than zero.");
    }
    if (paintingsForSale.find(painting) != paintingsForSale.end()) {
        throw std::runtime_error("Painting is already in the commission shop.");
    }
    paintingsForSale[painting] = price;
}

void CommissionShop::buyPainting(const std::string& painting, double price) {
    if (paintingsForSale.find(painting) != paintingsForSale.end()) {
        throw std::runtime_error("Painting is already in the shop.");
    }
    if (price <= 0) {
        throw std::invalid_argument("Price must be greater than zero.");
    }
    paintingsForSale[painting] = price * 2;
}

void CommissionShop::sellPainting(const string& painting) {
    auto it = paintingsForSale.find(painting);
    if (it == paintingsForSale.end()) {
        throw std::runtime_error("Painting not found in the commission shop.");
    }
    paintingsForSale.erase(it);

}

void CommissionShop::displayInfo() const {
    std::cout << "Paintings for sale:\n";
    if (paintingsForSale.empty()) {
        std::cout << "No paintings available for sale.\n";
        return;
    }
    for (const auto& pair : paintingsForSale) {
        std::cout << pair.first << " ($" << pair.second << ")\n";
    }
}

void CommissionShop::save(std::ofstream& out) const {
    if (!out) {
        throw std::ios_base::failure("Error opening file for writing.");
    }
    out << paintingsForSale.size() << "\n";
    for (const auto& pair : paintingsForSale) {
        out << pair.first << "\n" << pair.second << "\n";
    }
}

void CommissionShop::load(std::ifstream& in) {
    if (!in) {
        throw std::ios_base::failure("Error opening file for reading.");
    }
    size_t size;
    in >> size;
    in.ignore();
    for (size_t i = 0; i < size; ++i) {
        std::string painting;
        double price;
        std::getline(in, painting);
        in >> price;
        if (price <= 0) {
            throw std::runtime_error("Invalid price found in file.");
        }
        in.ignore();
        paintingsForSale[painting] = price;
    }
}

void CommissionShop::buyPaintingInShop(std::vector<CommissionShop>& shops) {
    if (shops.empty()) {
        std::cout << "No commission shops available.\n";
        return;
    }

    std::string painting;
    double price;
    std::cout << "Enter name of painting for sale: ";
    std::cin.ignore();
    std::getline(std::cin, painting);
    std::cout << "Enter price: ";
    if (!(std::cin >> price) || price <= 0) {
        throw std::invalid_argument("Invalid price entered.");
    }

    try {
        shops[0].buyPainting(painting, price);
        std::cout << "Painting bought by commission shop: " << painting << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

