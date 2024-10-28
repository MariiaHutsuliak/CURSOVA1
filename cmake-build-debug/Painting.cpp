#include "Painting.h"

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
        artist = other.artist;
        creationDate = other.creationDate;
        genre = other.genre;
        sold = other.sold;
    }
    return *this;
}

Painting& Painting::operator=(Painting&& other) noexcept {
    if (this != &other) {
        title = std::move(other.title);
        artist = std::move(other.artist);
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
    this->title = title;
}

Artist* Painting::getArtist() const {
    return artist.get();
}

void Painting::setArtist(std::shared_ptr<Artist> artist) {
    if (!artist) {
        std::cout << "Artist cannot be null. Please provide a valid artist.\n";
        return;
    }
    this->artist = artist;
}

std::string Painting::getCreationDate() const {
    return creationDate;
}

void Painting::setCreationDate(const std::string& creationDate) {
    this->creationDate = creationDate;
}

std::string Painting::getGenre() const {
    return genre;
}

void Painting::setGenre(const std::string& genre) {
    this->genre = genre;
}

bool Painting::isSold() const {
    return sold;
}

void Painting::setSold(bool sold) {
    this->sold = sold;
}

void Painting::input() {
    std::regex latinRegex("^[A-Za-z0-9\\s]+$");
    std::regex yearRegex("^\\d{4}$");
    std::regex dateRegex("^\\d{4}-\\d{2}-\\d{2}$");  // Example format for birthDate as YYYY-MM-DD

    // Input and validate title
    while (true) {
        try {
            std::cout << "Enter title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            if (title.empty() || !std::regex_match(title, latinRegex)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid title.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input for title. Please use only letters, numbers, and spaces.\n";
        }
    }

    // Input and validate artist details
    artist = std::make_shared<Artist>();
    std::string artistName, artistBirthDate, artistStyle;

    while (true) {
        try {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter artist name: ";
            std::getline(std::cin, artistName);
            if (artistName.empty() || !std::regex_match(artistName, latinRegex)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid artist name.");
            }
            artist->setName(artistName);
            break;
        } catch (...) {
            std::cout << "Invalid input for artist name. Please use only letters, numbers, and spaces.\n";
        }
    }

    while (true) {
        try {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter artist birth date (YYYY-MM-DD): ";
            std::getline(std::cin, artistBirthDate);
            if (artistBirthDate.empty() || !std::regex_match(artistBirthDate, dateRegex)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid birth date format.");
            }
            artist->setBirthDate(artistBirthDate);
            break;
        } catch (...) {
            std::cout << "Invalid input for birth date. Please enter in YYYY-MM-DD format.\n";
        }
    }

    while (true) {
        try {
            std::cout << "Enter artist style: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, artistStyle);
            if (artistStyle.empty() || !std::regex_match(artistStyle, latinRegex)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid style.");
            }
            artist->setStyle(artistStyle);
            break;
        } catch (...) {
            std::cout << "Invalid input for artist style. Please use only letters, numbers, and spaces.\n";
        }
    }

    // Input and validate creation date
    while (true) {
        try {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter creation date (e.g., 1875): ";
            std::getline(std::cin, creationDate);
            if (creationDate.empty() || !std::regex_match(creationDate, yearRegex)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid creation date.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input for creation date. Please enter a valid year.\n";
        }
    }

    // Input and validate genre
    while (true) {
        try {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter genre: ";
            std::getline(std::cin, genre);
            if (genre.empty() || !std::regex_match(genre, latinRegex)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid genre.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input for genre. Please use only letters, numbers, and spaces.\n";
        }
    }
}

void Painting::displayInfo() const {
    std::cout << "Title: " << title << "\nArtist: " << (artist ? artist->getName() : "Unknown")
              << "\nBirthday: " << artist->getBirthDate() << "\nStyle: " << artist->getStyle()
              << "\nCreation Date: " << creationDate << "\nGenre: " << genre
              << "\nSold: " << (sold ? "Yes" : "No") << std::endl << std::endl;
}

void Painting::addPainting(std::vector<Painting>& paintings, std::vector<Artist>& artists) {
    while (true) {
        try {
            Painting painting;
            std::string artistName;
            std::regex latinRegex("^[A-Za-z\\s]+$");

            std::cout << "Enter artist name: ";
            std::cin.ignore();
            std::getline(std::cin, artistName);
            if (artistName.empty() || !std::regex_match(artistName, latinRegex)) {
                throw std::runtime_error("Invalid artist name.");
            }

            std::shared_ptr<Artist> artist = nullptr;
            for (auto& a : artists) {
                if (a.getName() == artistName) {
                    artist = std::make_shared<Artist>(a);
                    break;
                }
            }

            if (!artist) {
                std::cout << "Artist not found. Please try again with a valid artist.\n";
                continue;
            }

            painting.setArtist(artist);
            painting.input();
            paintings.push_back(std::move(painting));
            break;
        } catch (...) {
            std::cout << "An error occurred while adding the painting. Please try again.\n";
        }
    }
}

void Painting::sortPaintingsByTitle(std::vector<Painting>& paintings) {
    if (paintings.empty()) {
        std::cout << "No paintings to sort.\n";
        return;
    }
    std::sort(paintings.begin(), paintings.end(), [](const Painting& a, const Painting& b) {
        return a.getTitle() < b.getTitle();
    });
    for (const auto& painting : paintings) painting.displayInfo();
}

std::vector<Painting> Painting::filterPaintingsByGenre(const std::vector<Painting>& paintings, const std::string& genre) {
    std::vector<Painting> result;
    if (genre.empty()) {
        std::cout << "Genre cannot be empty for filtering.\n";
        return {};
    }
    std::copy_if(paintings.begin(), paintings.end(), std::back_inserter(result), [&genre](const Painting& painting) {
        return painting.getGenre() == genre;
    });
    if (result.empty()) {
        std::cout << "No paintings found with the specified genre.\n";
    }
    return result;
}

std::vector<Painting> Painting::searchPaintingsByTitle(const std::vector<Painting>& paintings, const std::string& title) {
    std::vector<Painting> result;
    if (title.empty()) {
        std::cout << "Title cannot be empty for searching.\n";
        return {};
    }
    std::copy_if(paintings.begin(), paintings.end(), std::back_inserter(result), [&title](const Painting& painting) {
        return painting.getTitle() == title;
    });
    if (result.empty()) {
        std::cout << "No paintings found with the specified title.\n";
    }
    return result;
}

double Painting::estimateValue() const {
    if (creationDate.size() < 4 || !std::all_of(creationDate.begin(), creationDate.end(), ::isdigit)) {
        std::cout << "Invalid creation date format. Unable to estimate value.\n";
        return 0.0;
    }

    double baseValue = 1000.0;
    if (genre == "impressionism") {
        baseValue *= 1.5;
    } else if (genre == "abstract") {
        baseValue *= 1.2;
    }

    int year = std::stoi(creationDate);
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
        artist = std::make_shared<Artist>();
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

void Painting::loadPaintings(std::vector<Painting> &paintings) {
    std::ifstream file(PAINTING_FILE);
    if (file.is_open()) {
        if (file.peek() == std::ifstream::traits_type::eof()) {
            return;
        }
        while (!file.eof()) {
            Painting painting;
            painting.setDataToObject(file);
            paintings.push_back(painting);
        }
        file.close();
    }
}

void Painting::savePaintings(const std::vector<Painting> &paintings) {
    std::ofstream file(PAINTING_FILE);
    for (const auto& painting : paintings) {
        painting.getDataFromObject(file);
    }
    file.close();
}