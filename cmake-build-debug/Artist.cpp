#include "Artist.h"

Artist::Artist() : Person{}, style{"None"} {}

Artist::Artist(const std::string &name, const std::string &birthDate, const std::string &style)
        : Person(name, birthDate), style(style) {}

Artist::Artist(const Artist &other)
        : Person(other), style(other.style) {}

Artist::Artist(Artist &&other) noexcept
        : Person(std::move(other)), style(std::move(other.style)) {}

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
    while (true) {
        try {
            Person::input();
            std::regex latinRegex("^[A-Za-z\\s]+$");
            std::cin.clear();//cin clear for being sure
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//cin inore now here
            std::cout << "Enter style (latin letters only): ";
            std::getline(std::cin, style);

            if (style.empty()) {
                std::cin.clear();//cin clear for being sure
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//cin inore now here
                throw std::runtime_error("Style cannot be empty.");
            } else if (!std::regex_match(style, latinRegex)) {
                std::cin.clear();//cin clear for being sure
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//cin inore now here
                throw std::runtime_error("Style can contain only Latin letters.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
}

void Artist::displayInfo() const {
    std::cout << "Name: " << getName() << "\nBirth date: " << getBirthDate() << "\nStyle: " << getStyle() << std::endl << std::endl;
}

std::string Artist::getStyle() const {
    return style;
}

void Artist::setStyle(const std::string &style) {
    this->style = style;
}

void Artist::sortArtistsByName(std::vector<Artist>& artists) {
    if (artists.empty()) {
        std::cout << "No artists available to sort." << std::endl;
        return;
    }

    std::sort(artists.begin(), artists.end(), [](const Artist& a, const Artist& b) {
        return a.getName() < b.getName();
    });
    for (const auto& artist : artists) artist.displayInfo();
}

std::vector<Artist> Artist::filterArtistsByStyle(const std::vector<Artist>& artists, const std::string& style) {
    std::vector<Artist> result;
    if (style.empty()) {
        std::cout << "Style cannot be empty for filtering." << std::endl;
        return result;
    }

    std::copy_if(artists.begin(), artists.end(), std::back_inserter(result), [&style](const Artist& artist) {
        return artist.getStyle() == style;
    });

    if (result.empty()) {
        std::cout << "No artists found with the specified style." << std::endl;
    }

    return result;
}

std::vector<Artist> Artist::searchArtistsByName(const std::vector<Artist>& artists, const std::string& name) {
    std::vector<Artist> result;
    if (name.empty()) {
        std::cout << "Name cannot be empty for searching." << std::endl;
        return result;
    }
    std::copy_if(artists.begin(), artists.end(), std::back_inserter(result), [&name](const Artist& artist) {
        return artist.getName() == name;
    });
    if (result.empty()) {
        std::cout << "No artists found with the specified name." << std::endl;
    }
    return result;
}

void Artist::getDataFromObject(std::ostream &os) const {
    Person::getDataFromObject(os);
    os << style << std::endl;
}

void Artist::setDataToObject(std::istream &is) {
    Person::setDataToObject(is);
    std::string currentLine;
    std::getline(is, currentLine);
    style = currentLine;
}

void Artist::loadArtists(std::vector<Artist>& artists) {
    std::ifstream file(ARTIST_FILE);
    if (!file.is_open()) {
        std::cerr << "Error opening collector file.\n";
        return;
    }

    artists.clear();
    while (file.peek() != std::ifstream::traits_type::eof()) {
        Artist artist;
        artist.setDataToObject(file);

        // Check for failed data read to avoid pushing incomplete collectors
        if (!file.fail()) {
            artists.push_back(artist);
        }
    }

    file.close();
}

void Artist::saveArtists(const std::vector<Artist>& artists) {
    std::ofstream file(ARTIST_FILE);
    for (const auto& artist : artists) {
        artist.getDataFromObject(file);
    }
    file.close();
}