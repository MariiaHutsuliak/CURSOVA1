#include "Auctioneer.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>

Auctioneer::Auctioneer() : Person(), auctionDate("None") {}
Auctioneer::Auctioneer(const std::string& name, const std::string& birthDate, const std::string& auctionDate)
        : Person(name, birthDate), auctionDate(auctionDate) {}

Auctioneer::Auctioneer(const std::string& name, const std::string& birthDate, const std::string& auctionDate,
                       const std::map<std::string, std::pair<std::string, double>>& auctionedPaintings)
        : Person(name, birthDate), auctionDate(auctionDate), auctionedPaintings(auctionedPaintings) {}

Auctioneer::Auctioneer(const Auctioneer &other)
    : Person(other), auctionedPaintings(other.auctionedPaintings), auctionDate(other.auctionDate) {}

Auctioneer::Auctioneer(Auctioneer &&other) noexcept
    : Person(other), auctionedPaintings(other.auctionedPaintings), auctionDate(other.auctionDate) {}

Auctioneer& Auctioneer::operator=(const Auctioneer& other) {
    if (this == &other) return *this;
    Person::operator=(other);
    auctionedPaintings = other.auctionedPaintings;
    auctionDate = other.auctionDate;
    return *this;
}

Auctioneer& Auctioneer::operator=(Auctioneer&& other) noexcept {
    if (this == &other) return *this;
    Person::operator=(std::move(other));
    auctionedPaintings = std::move(other.auctionedPaintings);
    auctionDate = std::move(other.auctionDate);
    return *this;
}

Auctioneer::~Auctioneer() {}

void Auctioneer::addAuctionedPainting(const std::string& painting, const std::string& date, double price) {
    if (price <= 0) {
        throw std::invalid_argument("Price must be greater than zero.");
    }
    auctionedPaintings[painting] = std::make_pair(date, price);
}

std::string Auctioneer::getAuctionDate() const {
    return auctionDate;
}

void Auctioneer::setAuctionDate(const std::string &auctionDate) {
    if (auctionDate.empty()) {
        throw std::invalid_argument("Auction date cannot be empty.");
    }
    this->auctionDate = auctionDate;
}

std::map<std::string, std::pair<std::string,double>> Auctioneer::getAuctionedPaintings() const {
    return auctionedPaintings;
}

void Auctioneer::addAuctioneer(std::vector<Auctioneer>& auctioneers) {
    try {
        Auctioneer auctioneer;
        auctioneer.input();
        auctioneers.push_back(std::move(auctioneer));
    } catch (const std::exception& e) {
        std::cerr << "Error while adding auctioneer: " << e.what() << std::endl;
    }
}

void Auctioneer::input() {
    Person::input();
    std::cout << "Enter auction date: ";
    std::cin.ignore();
    std::getline(std::cin, auctionDate);

    if (auctionDate.empty()) {
        throw std::invalid_argument("Auction date cannot be empty.");
    }
}

void Auctioneer::displayInfo() const {
    std::cout << "Auctioneer: " << getName() << "\nAuction date: " << auctionDate << "\nAuctioned paintings: ";
    if (auctionedPaintings.empty()) {
        std::cout << "No paintings are currently being auctioned.\n";
        return;
    }
    for (const auto& pair : auctionedPaintings) {
        std::cout << pair.first << " (available on " << pair.second.first << ", $" << pair.second.second << ")\n";
    }
}

void Auctioneer::sellPainting(const std::string& painting) {
    auto it = auctionedPaintings.find(painting);
    if (it == auctionedPaintings.end()) {
        throw std::runtime_error("Painting not found in auction.");
    }
    auctionedPaintings.erase(it);
    std::cout << "Painting sold: " << painting << std::endl;
}

void Auctioneer::save(std::ofstream& out) const {
    if (!out) {
        throw std::ios_base::failure("Error opening file for writing.");
    }

    Person::save(out);
    out << auctionDate << "\n" << auctionedPaintings.size() << "\n";
    for (const auto& pair : auctionedPaintings) {
        out << pair.first << "\n" << pair.second.first << "\n" << pair.second.second << "\n";
    }
}

void Auctioneer::load(std::ifstream& in) {
    if (!in) {
        throw std::ios_base::failure("Error opening file for reading.");
    }

    Person::load(in);
    std::getline(in, auctionDate);
    if (auctionDate.empty()) {
        throw std::runtime_error("Auction date is missing in file.");
    }

    size_t size;
    in >> size;
    in.ignore();
    for (size_t i = 0; i < size; ++i) {
        std::string painting, date;
        double price;
        std::getline(in, painting);
        std::getline(in, date);
        in >> price;
        if (price <= 0) {
            throw std::runtime_error("Invalid price found in auction data.");
        }
        in.ignore();
        auctionedPaintings[painting] = std::make_pair(date, price);
    }
}

void Auctioneer::sortAuctioneersByName(std::vector<Auctioneer>& auctioneers) {
    if (auctioneers.empty()) {
        throw std::runtime_error("No auctioneers to sort.");
    }

    std::sort(auctioneers.begin(), auctioneers.end(), [](const Auctioneer& a, const Auctioneer& b) {
        return a.getName() < b.getName();
    });
}

void Auctioneer::holdAuction(Painting* painting, vector<Collector*>& collectors) {
    if (painting == nullptr) {
        throw std::invalid_argument("Painting does not exist.");
    }

    std::cout << "Auction for: " << painting->getTitle() << "\n";
    int highestBid = 0;
    Collector* highestBidder = nullptr;

    for (auto& collector : collectors) {
        try {
            int bid = collector->placeBid(painting);
            if (bid > highestBid) {
                highestBid = bid;
                highestBidder = collector;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error during bidding: " << e.what() << std::endl;
        }
    }

    if (highestBidder) {
        highestBidder->purchasePainting(painting, highestBid);
        std::cout << highestBidder->getName() << " won the auction for $" << highestBid << "!\n";
    } else {
        std::cout << "No bids were placed.\n";
    }
}

void Auctioneer::listAuctionedPaintings() const {
    if (auctionedPaintings.empty()) {
        std::cout << "No paintings are currently being auctioned." << std::endl;
        return;
    }
    std::cout << "Auctioned Paintings:" << std::endl;
    for (const auto& painting : auctionedPaintings) {
        std::cout << "Title: " << painting.first << ", Price: " << painting.second.second << std::endl;
    }
}
