#include "Painting.h"

Painting::Painting() : title("None"), artist(nullptr), creationDate("None"), genre("None"), sold(false) {}

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

void Painting::updateSaleStatus() {
    sold = true;
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

bool Painting::getSold() const {
    return sold;
}

void Painting::setSold(bool sold) {
    this->sold = sold;
}

void Painting::input() {
    std::regex latinRegex("^[A-Za-z\\s]+$");
    std::regex yearRegex("^\\d{4}$");
    std::regex dateRegex("^\\d{4}-\\d{2}-\\d{2}$");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        try {
            std::cout << "Enter title: ";
            std::getline(std::cin, title);
            if (title.empty() || !std::regex_match(title, latinRegex)) {
                std::cin.clear();
                throw std::runtime_error("Invalid title.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input for title. Please use only letters, numbers, and spaces.\n";
        }
    }

    artist = std::make_shared<Artist>();
    std::string artistName, artistBirthDate, artistStyle;

    while (true) {
        try {
            std::cout << "Enter artist name: ";
            std::getline(std::cin, artistName);
            if (artistName.empty() || !std::regex_match(artistName, latinRegex)) {
                std::cin.clear();
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
            std::cout << "Enter artist birth date (YYYY-MM-DD): ";
            std::getline(std::cin, artistBirthDate);
            if (artistBirthDate.empty() || !std::regex_match(artistBirthDate, dateRegex)) {
                std::cin.clear();
                throw std::runtime_error("Invalid birth date format.");
            }
            artist->setBirthDate(artistBirthDate);
            break;
        } catch (...) {
            std::cout << "Invalid input for birth date. \nPlease enter in YYYY-MM-DD format.\n";
        }
    }

    while (true) {
        try {
            std::cout << "Enter artist style: ";
            std::getline(std::cin, artistStyle);
            if (artistStyle.empty() || !std::regex_match(artistStyle, latinRegex)) {
                std::cin.clear();
                throw std::runtime_error("Invalid style.");
            }
            artist->setStyle(artistStyle);
            break;
        } catch (...) {
            std::cout << "Invalid input for artist style. Please use only letters, numbers, and spaces.\n";
        }
    }

    while (true) {
        try {
            std::cout << "Enter creation date (e.g., 1875): ";
            std::getline(std::cin, creationDate);
            if (creationDate.empty() || !std::regex_match(creationDate, yearRegex)) {
                std::cin.clear();
                throw std::runtime_error("Invalid creation date.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input for creation date. Please enter a valid year.\n";
        }
    }

    while (true) {
        try {
            std::cout << "Enter genre: ";
            std::getline(std::cin, genre);
            if (genre.empty() || !std::regex_match(genre, latinRegex)) {
                std::cin.clear();
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

void Painting::removePainting(std::vector<Painting>& paintings) {
    if (paintings.empty()) {
        std::cout << "No paintings available to remove.\n";
        return;
    }
    std::string titleToRemove;
    std::cout << "Enter the title of the painting to remove: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, titleToRemove);

    auto it = std::find_if(paintings.begin(), paintings.end(), [&titleToRemove](const Painting& painting) {
        return painting.getTitle() == titleToRemove;
    });
    if (it != paintings.end()) {
        paintings.erase(it);
        std::cout << "Painting \"" << titleToRemove << "\" has been successfully removed.\n";
    } else {
        std::cout << "No painting found with the title \"" << titleToRemove << "\".\n";
    }
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
    setSold(sold);
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Painting::loadPaintings(std::vector<Painting> &paintings) {
    std::ifstream file(PAINTING_FILE);
    if (!file.is_open()) {
        std::cerr << "Error opening collector file.\n";
        return;
    }
    paintings.clear();
    while (file.peek() != std::ifstream::traits_type::eof()) {
        Painting painting;
        painting.setDataToObject(file);

        if (!file.fail()) {
            paintings.push_back(painting);
        }
    }
    file.close();
}

void Painting::savePaintings(const std::vector<Painting> &paintings) {
    std::ofstream file(PAINTING_FILE);
    for (const auto& painting : paintings) {
        painting.getDataFromObject(file);
    }
    file.close();
}