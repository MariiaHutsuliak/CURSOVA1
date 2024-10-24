#include "Painting.h"
#include "Artist.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>

Painting::Painting() : title(""), artist(nullptr), creationDate(""), genre(""), sold(false) {}

Painting::Painting(const std::string& title, std::shared_ptr<Artist> artist, const std::string& creationDate, const std::string& genre)
        : title(title), artist(artist), creationDate(creationDate), genre(genre), sold(false) {}

Painting::Painting(const Painting& other)
        : title(other.title), artist(other.artist), creationDate(other.creationDate), genre(other.genre), sold(other.sold) {}

Painting::Painting(Painting&& other) noexcept
        : title(std::move(other.title)), artist(std::move(other.artist)), creationDate(std::move(other.creationDate)), genre(std::move(other.genre)), sold(other.sold) {}

Painting& Painting::operator=(const Painting& other) {
    if (this != &other) {
        title = other.title;
        artist = other.artist; // Use shared_ptr directly
        creationDate = other.creationDate;
        genre = other.genre;
        sold = other.sold;
    }
    return *this;
}

Painting& Painting::operator=(Painting&& other) noexcept {
    if (this != &other) {
        title = std::move(other.title);
        artist = std::move(other.artist); // Move artist
        creationDate = std::move(other.creationDate);
        genre = std::move(other.genre);
        sold = other.sold;
    }
    return *this;
}

Painting::~Painting() {}

std::string Painting::getTitle() const {
    return title;
}

void Painting::setTitle(const std::string& title) {
    if (title.empty()) {
        throw std::invalid_argument("Title cannot be empty.");
    }
    this->title = title;
}

Artist* Painting::getArtist() const {
    return artist.get(); // Return raw pointer
}

void Painting::setArtist(std::shared_ptr<Artist> artist) { // Change to shared_ptr
    if (!artist) {
        throw std::invalid_argument("Artist cannot be null.");
    }
    this->artist = artist; // Set artist directly
}

std::string Painting::getCreationDate() const {
    return creationDate;
}

void Painting::setCreationDate(const std::string& creationDate) {
    if (creationDate.empty()) {
        throw std::invalid_argument("Creation date cannot be empty.");
    }
    this->creationDate = creationDate;
}

std::string Painting::getGenre() const {
    return genre;
}

void Painting::setGenre(const std::string& genre) {
    if (genre.empty()) {
        throw std::invalid_argument("Genre cannot be empty.");
    }
    this->genre = genre;
}

bool Painting::isSold() const {
    return sold;
}

void Painting::setSold(bool sold) {
    this->sold = sold;
}

void Painting::input() {
    std::cout << "Enter title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    if (title.empty()) {
        throw std::invalid_argument("Title cannot be empty.");
    }

    std::cout << "Enter creation date (e.g., 1875): ";
    std::getline(std::cin, creationDate);
    if (creationDate.empty()) {
        throw std::invalid_argument("Creation date cannot be empty.");
    }

    std::cout << "Enter genre: ";
    std::getline(std::cin, genre);
    if (genre.empty()) {
        throw std::invalid_argument("Genre cannot be empty.");
    }
}

void Painting::displayInfo() const {
    std::cout << "Title: " << title << "\nArtist: " << (artist ? artist->getName() : "Unknown")
              << "\nCreation Date: " << creationDate << "\nGenre: " << genre
              << "\nSold: " << (sold ? "Yes" : "No") << std::endl;
}

void Painting::addPainting(std::vector<Painting>& paintings, std::vector<Artist>& artists) {
    Painting painting;
    std::string artistName;
    std::cout << "Enter artist name: ";
    std::cin.ignore();
    std::getline(std::cin, artistName);

    std::shared_ptr<Artist> artist = nullptr; // Change to shared_ptr
    for (auto& a : artists) {
        if (a.getName() == artistName) {
            artist = std::make_shared<Artist>(a); // Create shared_ptr for artist
            break;
        }
    }

    if (!artist) {
        throw std::runtime_error("Artist not found.");
    }

    painting.setArtist(artist); // Set artist using shared_ptr
    try {
        painting.input();
        paintings.push_back(std::move(painting));
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Painting::sortPaintingsByTitle(std::vector<Painting>& paintings) {
    if (paintings.empty()) {
        throw std::runtime_error("No paintings to sort.");
    }
    std::sort(paintings.begin(), paintings.end(), [](const Painting& a, const Painting& b) {
        return a.getTitle() < b.getTitle();
    });
}

std::vector<Painting> Painting::filterPaintingsByGenre(const std::vector<Painting>& paintings, const std::string& genre) {
    if (genre.empty()) {
        throw std::invalid_argument("Genre cannot be empty for filtering.");
    }
    std::vector<Painting> result;
    std::copy_if(paintings.begin(), paintings.end(), std::back_inserter(result), [&genre](const Painting& painting) {
        return painting.getGenre() == genre;
    });
    return result;
}

std::vector<Painting> Painting::searchPaintingsByTitle(const std::vector<Painting>& paintings, const std::string& title) {
    if (title.empty()) {
        throw std::invalid_argument("Title cannot be empty for searching.");
    }
    std::vector<Painting> result;
    std::copy_if(paintings.begin(), paintings.end(), std::back_inserter(result), [&title](const Painting& painting) {
        return painting.getTitle() == title;
    });
    return result;
}

double Painting::estimateValue() const {
    if (creationDate.size() < 4 || !std::all_of(creationDate.begin(), creationDate.end(), ::isdigit)) {
        throw std::runtime_error("Invalid creation date format.");
    }

    double baseValue = 1000.0;
    if (genre == "Impressionism") {
        baseValue *= 1.5;
    } else if (genre == "Abstract") {
        baseValue *= 1.2;
    }

    int year = std::stoi(creationDate.substr(0, 4));
    if (year < 1900) {
        baseValue *= 2;
    }

    return baseValue;
}

void Painting::updateSaleStatus(bool sold) {
    this->sold = sold;
    std::cout << "The painting has been marked as " << (sold ? "sold" : "available") << "." << std::endl;
}

void Painting::getDataFromObject(std::ostream& os) const {
    os << title << std::endl;
    if (artist) {
        artist->getDataFromObject(os);
    } else {
        os << "Unknown artist" << std::endl;
    }
    os << creationDate << std::endl;
    os << genre << std::endl;
    os << sold << std::endl;
}

void Painting::setDataToObject(std::istream& is) {
    std::string currentLine;
    std::getline(is, title);
    std::getline(is, currentLine);
    if (currentLine == "Unknown artist") {
        artist = nullptr;
    } else {
        artist = std::make_shared<Artist>(); // Create shared_ptr for artist
        artist->setName(currentLine);
        std::getline(is, currentLine);
        artist->setBirthDate(currentLine);
        std::getline(is, currentLine);
        artist->setStyle(currentLine);
    }
    std::getline(is, creationDate);
    std::getline(is, genre);
    is >> sold;
    is.ignore();
}
