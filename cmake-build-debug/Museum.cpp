#include "Museum.h"

Museum::Museum() : name("None"), location("Unknown") {}

Museum::Museum(const std::string &name, const std::string &location)
        : name(name), location(location) {}

Museum::Museum(const Museum &other)
        : name(other.name), location(other.location), collection(other.collection) {}

Museum::Museum(Museum &&other) noexcept
        : name(std::move(other.name)), location(std::move(other.location)), collection(std::move(other.collection)) {}

Museum& Museum::operator=(const Museum& other) {
    if (this == &other) return *this;
    name = other.name;
    location = other.location;
    collection = other.collection;
    return *this;
}

Museum& Museum::operator=(Museum&& other) noexcept {
    if (this == &other) return *this;
    name = std::move(other.name);
    location = std::move(other.location);
    collection = std::move(other.collection);
    return *this;
}

Museum::~Museum() {}

std::string Museum::getLocation() const {
    return location;
}

void Museum::setLocation(const std::string &location) {
    this->location = location;
}

std::string Museum::getName() const {
    return name;
}

void Museum::setName(const std::string &name) {
    this->name = name;
}

void Museum::removePaintingFromCollection(const std::string& paintingName) {
    auto it = std::remove_if(collection.begin(), collection.end(),
                             [&paintingName](const Painting& painting) {
                                 return painting.getTitle() == paintingName;
                             });
    if (it == collection.end()) {
        std::cout << "Painting not found in the collection. Please check the title.\n";
    } else {
        collection.erase(it, collection.end());
        std::cout << "Painting " << paintingName << " removed from collection.\n";
    }
}

void Museum::removePaintingFromMuseum(std::vector<Museum>& museums) {
    std::string museumName, paintingName;
    std::cout << "Enter the name of the museum: ";
    std::cin.ignore();
    std::getline(std::cin, museumName);
    auto museumIt = std::find_if(museums.begin(), museums.end(),
                                 [&museumName](const Museum& museum) {
                                     return museum.getName() == museumName;
                                 });

    if (museumIt == museums.end()) {
        std::cout << "Museum not found.\n";
        return;
    }
    std::cout << "Enter the title of the painting to remove: ";
    std::getline(std::cin, paintingName);
    museumIt->removePaintingFromCollection(paintingName);
}

void Museum::input() {
    std::regex latinRegex("^[A-Za-z\\s]+$");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        try {
            std::cout << "Enter name of the museum: ";
            std::getline(std::cin, name);
            if (name.empty() || !std::regex_match(name, latinRegex)) {
                throw std::runtime_error("Invalid name.");
            }
            std::cout << "Enter location: ";
            std::getline(std::cin, location);
            if (location.empty() || !std::regex_match(location, latinRegex)) {
                throw std::runtime_error("Invalid location.");
            }
            break;
        } catch (...) {
            std::cout << "Invalid input. Please use only Latin letters and spaces.\n";
        }
    }
    int numPaintings;
    std::cout << "Enter the number of paintings to add to the collection: ";
    while (!(std::cin >> numPaintings) || numPaintings < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a positive integer for the number of paintings: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    collection.clear();
    for (int i = 0; i < numPaintings; ++i) {
        Painting painting;
        std::string paintingName, artistName, artistBirthDate, artistStyle, creationDate, genre;
        while (true) {
            std::cout << "Enter the title for painting #" << (i + 1) << " : ";
            std::getline(std::cin, paintingName);
            if (std::regex_match(paintingName, latinRegex)) {
                painting.setTitle(paintingName);
                break;
            }
            std::cout << "Invalid input. Please use only Latin letters and spaces for the title.\n";
        }
        while (true) {
            std::cout << "Enter the artist name for painting #" << (i + 1) << " : ";
            std::getline(std::cin, artistName);
            if (std::regex_match(artistName, latinRegex)) {
                break;
            }
            std::cout << "Invalid input. Please use only Latin letters and spaces for the artist name.\n";
        }
        std::regex dateRegex("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");
        while (true) {
            std::cout << "Enter the birth date of the artist (YYYY-MM-DD): ";
            std::getline(std::cin, artistBirthDate);
            if (std::regex_match(artistBirthDate, dateRegex)) {
                break;
            }
            std::cout << "Invalid date format. Please enter the date in YYYY-MM-DD format.\n";
        }
        while (true) {
            std::cout << "Enter the artist's style: ";
            std::getline(std::cin, artistStyle);
            if (std::regex_match(artistStyle, latinRegex)) {
                break;
            }
            std::cout << "Invalid input. Please use only Latin letters and spaces for the style.\n";
        }
        auto artist = std::make_shared<Artist>();
        artist->setName(artistName);
        artist->setBirthDate(artistBirthDate);
        artist->setStyle(artistStyle);
        painting.setArtist(artist);
        std::cout << "Enter the creation date for painting #" << (i + 1) << " (e.g. 1987): ";
        std::getline(std::cin, creationDate);
        painting.setCreationDate(creationDate);
        std::cout << "Enter the genre for painting #" << (i + 1) << ": ";
        std::getline(std::cin, genre);
        painting.setGenre(genre);
        collection.push_back(painting);
    }
}

void Museum::displayInfo() const {
    std::cout << "Museum Name: " << name << "\n";
    std::cout << "Location: " << location << "\n";
    if (collection.empty()) {
        std::cout << "No paintings in the collection." << std::endl;
    } else {
        std::cout << "Paintings in the Collection:" << std::endl;
        for (const auto& painting : collection) {
            painting.displayInfo();
        }
    }
}

void Museum::sortMuseumsByName(std::vector<Museum>& museums) {
    if (museums.empty()) {
        std::cout << "No museums to sort.\n";
        return;
    }
    std::sort(museums.begin(), museums.end(), [](const Museum& a, const Museum& b) {
        return a.getName() < b.getName();
    });
    for (const auto& museum : museums) museum.displayInfo();
}

void Museum::getDataFromObject(std::ostream &os) const {
    os << name << std::endl;
    os << location << std::endl;
    os << collection.size() << std::endl;
    for (const auto& painting : collection) {
        painting.getDataFromObject(os);
    }
}

void Museum::setDataToObject(std::istream &is) {
    std::getline(is, name);
    std::getline(is, location);
    size_t paintingCount;
    is >> paintingCount;
    is.ignore();
    collection.clear();
    for (size_t i = 0; i < paintingCount; ++i) {
        Painting painting;
        painting.setDataToObject(is);
        collection.push_back(painting);
    }
}

void Museum::loadMuseums(std::vector<Museum> &museums) {
    std::ifstream file(MUSEUM_FILE);
    if (!file.is_open()) {
        return;
    }
    museums.clear();
    while (file.peek() != std::ifstream::traits_type::eof()) {
        Museum museum;
        museum.setDataToObject(file);
        if (!file.fail()) {
            museums.push_back(museum);
        }
    }
    file.close();
}

void Museum::saveMuseums(const std::vector<Museum> &museums) {
    std::ofstream file(MUSEUM_FILE);
    for (const auto& museum : museums) {
        museum.getDataFromObject(file);
    }
    file.close();
}