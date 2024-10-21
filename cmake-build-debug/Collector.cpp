#include "Collector.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <stdexcept>

Collector::Collector() : Person() {}
Collector::Collector(const std::string &name, const std::string &birthDate)
        : Person(name, birthDate) {}

Collector::Collector(const std::string& name, const std::string& birthDate, const std::vector<Painting>& originalPaintings, const std::vector<Painting>& copiedPaintings)
        : Person(name, birthDate), originalPaintings(originalPaintings), copiedPaintings(copiedPaintings) {}

Collector::Collector(const Collector& other)
        : Person(other), originalPaintings(other.originalPaintings), copiedPaintings(other.copiedPaintings) {}

Collector::Collector(Collector&& other) noexcept
        : Person(other), originalPaintings(other.originalPaintings), copiedPaintings(other.copiedPaintings) {}

Collector& Collector::operator=(const Collector& other) {
    if (this == &other) return *this;
    Person::operator=(other);
    originalPaintings = other.originalPaintings;
    copiedPaintings = other.copiedPaintings;
    return *this;
}

Collector& Collector::operator=(Collector&& other) noexcept {
    if (this == &other) return *this;
    Person::operator=(std::move(other));
    originalPaintings = std::move(other.originalPaintings);
    copiedPaintings = std::move(other.copiedPaintings);
    return *this;
}

Collector::~Collector() {}

void Collector::addOriginalPainting(const Painting& painting) {
    originalPaintings.push_back(painting);
}

void Collector::addCopiedPainting(const Painting& painting) {
    copiedPaintings.push_back(painting);
}

std::vector<Painting> Collector::getCopiedPaintings() const {
    return copiedPaintings;
}

std::vector<Painting> Collector::getOriginalPaintings() const {
    return originalPaintings;
}

void Collector::addCollector(std::vector<Collector>& collectors) {
    try {
        Collector collector;
        collector.input();
        collectors.push_back(std::move(collector));
    } catch (const std::exception& e) {
        std::cerr << "Error while adding collector: " << e.what() << std::endl;
    }
}

void Collector::input() {
    Person::input();
}
void Collector::displayInfo() const {
    std::cout << "Collector: " << getName() << "\nOriginal paintings: ";
    for (const auto &painting : originalPaintings) painting.displayInfo();
    std::cout << "\nCopied paintings: ";
    for (const auto &painting : copiedPaintings) painting.displayInfo();
    std::cout << endl;
}

int Collector::placeBid(Painting* painting) {
    int bid;
    std::cout << "Enter your bid for " << painting->getTitle() << ": ";


    while (!(std::cin >> bid) || bid <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive bid: ";
    }

    return bid;
}

void Collector::purchasePainting(Painting* painting, int price) {
    if (painting == nullptr) {
        throw std::invalid_argument("Painting does not exist.");
    }

    originalPaintings.push_back(*painting);
    std::cout << getName() << " purchased " << painting->getTitle() << " for $" << price << ".\n";
}

void Collector::save(std::ofstream& out) const {
    if (!out) {
        throw std::ios_base::failure("Error opening file for writing.");
    }

    Person::save(out);
    out << originalPaintings.size() << "\n";
    for (const auto& painting : originalPaintings) {
        painting.save(out);
    }
    out << copiedPaintings.size() << "\n";
    for (const auto& painting : copiedPaintings) {
        painting.save(out);
    }
}

void Collector::load(std::ifstream& in, const std::vector<Artist>& artists) {
    if (!in) {
        throw std::ios_base::failure("Error opening file for reading.");
    }

    Person::load(in);
    size_t size;
    in >> size;
    in.ignore();
    originalPaintings.resize(size);
    for (auto& painting : originalPaintings) {
        painting.load(in, artists);
    }
    in >> size;
    in.ignore();
    copiedPaintings.resize(size);
    for (auto& painting : copiedPaintings) {
        painting.load(in, artists);
    }
}

void Collector::sortCollectorsByName(std::vector<Collector>& collectors) {
    if (collectors.empty()) {
        throw std::runtime_error("No collectors to sort.");
    }

    std::sort(collectors.begin(), collectors.end(), [](const Collector& a, const Collector& b) {
        return a.getName() < b.getName();
    });
}


