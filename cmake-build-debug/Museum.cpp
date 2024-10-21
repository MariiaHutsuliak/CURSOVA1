#include "Museum.h"
#include <algorithm>
#include <vector>
#include <string>
#include <stdexcept>

Museum::Museum() : title("None"), location("Unknown") {}

Museum::Museum(const std::string &title, const std::string &location)
        : title(title), location(location) {}

Museum::Museum(const Museum &other)
        : title(other.title), location(other.location), collection(other.collection) {}

Museum::Museum(Museum &&other) noexcept
        : title(std::move(other.title)), location(std::move(other.location)), collection(std::move(other.collection)) {}

Museum& Museum::operator=(const Museum& other) {
    if (this == &other) return *this;
    title = other.title;
    location = other.location;
    collection = other.collection;
    return *this;
}

Museum& Museum::operator=(Museum&& other) noexcept {
    if (this == &other) return *this;
    title = std::move(other.title);
    location = std::move(other.location);
    collection = std::move(other.collection);
    return *this;
}

Museum::~Museum() {}

std::string Museum::getLocation() const {
    return location;
}

void Museum::setLocation(const std::string &location) {
    if (location.empty()) {
        throw std::invalid_argument("Location cannot be empty.");
    }
    this->location = location;
}

std::string Museum::getTitle() const {
    return title;
}

void Museum::setTitle(const std::string &title) {
    if (title.empty()) {
        throw std::invalid_argument("Title cannot be empty.");
    }
    this->title = title;
}

void Museum::addPaintingToCollection(const Painting& painting) {
    collection.push_back(painting);
}

void Museum::removePaintingFromCollection(const std::string& paintingTitle) {
    auto it = std::remove_if(collection.begin(), collection.end(),
                             [&paintingTitle](const Painting& painting) {
                                 return painting.getTitle() == paintingTitle;
                             });
    if (it == collection.end()) {
        throw std::runtime_error("Painting not found in the collection.");
    }
    collection.erase(it, collection.end());
}

void Museum::viewCollection() const {
    if (collection.empty()) {
        std::cout << "No paintings in the collection." << std::endl;
        return;
    }
    std::cout << "Museum Collection: \n";
    for (const auto& painting : collection) {
        painting.displayInfo();
    }
}

void Museum::input() {
    std::cout << "Enter name of the museum: ";
    std::getline(std::cin, title);
    if (title.empty()) {
        throw std::invalid_argument("Museum name cannot be empty.");
    }
    std::cout << "Enter location: ";
    std::getline(std::cin, location);
    if (location.empty()) {
        throw std::invalid_argument("Location cannot be empty.");
    };
}

void Museum::displayInfo() const {
    std::cout << "Museum Name: " << title << "\n";
    std::cout << "Location: " << location << "\n";
}

void Museum::save(std::ofstream& out) const {
    if (!out) {
        throw std::ios_base::failure("Error opening file for writing.");
    }
    out << title << "\n";
    out << location << "\n";
    out << collection.size() << "\n";
    for (const auto& painting : collection) {
        painting.save(out);
    }
}


void Museum::load(std::ifstream& in, const std::vector<Artist>& artists) {
    if (!in) {
        throw std::ios_base::failure("Error opening file for reading.");
    }
    std::getline(in, title);
    std::getline(in, location);
    if (title.empty() || location.empty()) {
        throw std::runtime_error("Invalid data in file (empty title or location).");
    }
    size_t size;
    in >> size;
    in.ignore();
    collection.resize(size);
    for (auto& painting : collection) {
        painting.load(in, artists);
    }
}

void Museum::sortMuseumsByName(std::vector<Museum>& museums) {
    if (museums.empty()) {
        throw std::runtime_error("No museums to sort.");
    }
    std::sort(museums.begin(), museums.end(), [](const Museum& a, const Museum& b) {
        return a.getTitle() < b.getTitle();
    });
}

void Museum::addMuseum(vector<Museum> &museums) {
    try {
        Museum newMuseum;
        newMuseum.input();
        museums.push_back(newMuseum);
    } catch (const std::exception& e) {
        std::cerr << "Error while adding museum: " << e.what() << std::endl;
    }
}

void Museum::organizeExhibition() const {
    std::cout << "Exhibition at " << location << "!" << std::endl;
    if (collection.empty()) {
        std::cout << "No paintings available for exhibition." << std::endl;
    } else {
        std::cout << "Paintings on display:" << std::endl;
        for (const auto& painting : collection) {
            painting.displayInfo();
        }
    }
}