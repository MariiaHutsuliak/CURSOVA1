#include "Artist.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>

Artist::Artist() : Person{}, style{"None"} {}
Artist::Artist(const std::string &name, const std::string &birthDate, const std::string &style)
    : Person(name, birthDate), style(style) {}

Artist::Artist(const Artist &other)
    : Person(other), style(other.style) {}

Artist::Artist(Artist &&other) noexcept
    : Person(other), style(other.style) {}

Artist& Artist::operator=(const Artist& other) {
    if (this == &other) return *this;
    Person::operator=(other);
    style = other.style;
    return *this;
}

Artist& Artist::operator=(Artist&& other) noexcept {
    if (this == &other) return *this;
    Person::operator=(std::move(other));
    style = std::move(other.style);
    return *this;
}

Artist::~Artist() {}

void Artist::input() {
    Person::input();
    std::cout << "Enter style: ";
    std::getline(std::cin, style);

    if (style.empty()) {
        throw std::invalid_argument("Style cannot be empty.");
    }
}

void Artist::addArtist(std::vector<Artist>& artists) {
    try {
        Artist artist;
        artist.input();
        artists.push_back(std::move(artist));
    } catch (const std::exception& e) {
        std::cerr << "Error while adding artist: " << e.what() << std::endl;
    }
}

void Artist::displayInfo() const {
    std::cout << "Name: " << getName() << "\nBirth date: " << getBirthDate() << "\nStyle: " << getStyle() << endl;
}

std::string Artist::getStyle() const {
    return style;
}

void Artist::setStyle(const std::string &style) {
    if (style.empty()) {
        throw std::invalid_argument("Style cannot be empty.");
    }
    this->style = style;
}

void Artist::save(std::ofstream& out) const {
    if (!out) {
        throw std::ios_base::failure("Error opening file for writing.");
    }
    Person::save(out);
    out << style << "\n";
}

void Artist::load(std::ifstream& in) {
    if (!in) {
        throw std::ios_base::failure("Error opening file for reading.");
    }
    Person::load(in);
    std::getline(in, style);
    if (style.empty()) {
        throw std::runtime_error("Error loading artist: style is empty.");
    }
}

void Artist::sortArtistsByName(std::vector<Artist>& artists) {
    if (artists.empty()) {
        throw std::runtime_error("No artists available to sort.");
    }

    std::sort(artists.begin(), artists.end(), [](const Artist& a, const Artist& b) {
        return a.getName() < b.getName();
    });
}

std::vector<Artist> Artist::filterArtistsByStyle(const std::vector<Artist>& artists, const std::string& style) {
    if (style.empty()) {
        throw std::invalid_argument("Style cannot be empty for filtering.");
    }

    std::vector<Artist> result;
    std::copy_if(artists.begin(), artists.end(), std::back_inserter(result), [&style](const Artist& artist) {
        return artist.getStyle() == style;
    });

    if (result.empty()) {
        throw std::runtime_error("No artists found with the specified style.");
    }

    return result;
}

std::vector<Artist> Artist::searchArtistsByName(const std::vector<Artist>& artists, const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty for searching.");
    }

    std::vector<Artist> result;
    std::copy_if(artists.begin(), artists.end(), std::back_inserter(result), [&name](const Artist& artist) {
        return artist.getName() == name;
    });

    if (result.empty()) {
        throw std::runtime_error("No artists found with the specified name.");
    }

    return result;
}

