#include "Collector.h"

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

std::vector<Painting> Collector::getCopiedPaintings() const {
    return copiedPaintings;
}

std::vector<Painting> Collector::getOriginalPaintings() const {
    return originalPaintings;
}

void Collector::input() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Person::input();
    std::regex latinRegex("^[A-Za-z\\s]+$");
    std::regex dateRegex("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");
    int originalCount, copiedCount;
    std::cout << "Enter the number of original paintings: ";
    while (!(std::cin >> originalCount) || originalCount < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive number for original paintings: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    originalPaintings.clear();
    for (int i = 0; i < originalCount; ++i) {
        Painting painting;
        std::string title, creationDate, genre;
        std::shared_ptr<Artist> artist = std::make_shared<Artist>();
        while (true) {
            try {
                std::cout << "Enter title for original painting #" << (i + 1) << " : ";
                std::getline(std::cin, title);
                if (!std::regex_match(title, latinRegex)) {
                    throw std::runtime_error("Title can contain only Latin letters.");
                }
                break;
            } catch (const std::exception &e) {
                std::cout << " Please try again.\n";
            }
        }
        std::string artistName, artistBirthDate, artistStyle;
        std::cout << "Enter artist name: ";
        std::getline(std::cin, artistName);
        artist->setName(artistName);
        while (true) {
            std::cout << "Enter artist birthdate (YYYY-MM-DD): ";
            std::getline(std::cin, artistBirthDate);
            if (std::regex_match(artistBirthDate, dateRegex)) {
                artist->setBirthDate(artistBirthDate);
                break;
            }
            std::cout << "Invalid date format. Please try again.\n";
        }
        std::cout << "Enter artist style: ";
        std::getline(std::cin, artistStyle);
        artist->setStyle(artistStyle);
        while (true) {
            std::cout << "Enter creation date (YYYY-MM-DD): ";
            std::getline(std::cin, creationDate);
            if (std::regex_match(creationDate, dateRegex)) {
                break;
            }
            std::cout << "Invalid date format. Please try again.\n";
        }
        std::cout << "Enter genre: ";
        std::getline(std::cin, genre);
        painting.setTitle(title);
        painting.setArtist(artist);
        painting.setCreationDate(creationDate);
        painting.setGenre(genre);
        painting.setSold(false);
        originalPaintings.push_back(painting);
    }
    std::cout << "Enter the number of copied paintings: ";
    while (!(std::cin >> copiedCount) || copiedCount < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive number for copied paintings: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    copiedPaintings.clear();
    for (int i = 0; i < copiedCount; ++i) {
        Painting painting;
        std::string title, creationDate, genre;
        std::shared_ptr<Artist> artist = std::make_shared<Artist>();
        while (true) {
            try {
                std::cout << "Enter title for copied painting #" << (i + 1) << " : ";
                std::getline(std::cin, title);
                if (!std::regex_match(title, latinRegex)) {
                    throw std::runtime_error("Title can contain only Latin letters.");
                }
                break;
            } catch (const std::exception &e) {
                std::cout << " Please try again.\n";
            }
        }
        std::string artistName, artistBirthDate, artistStyle;
        std::cout << "Enter artist name: ";
        std::getline(std::cin, artistName);
        artist->setName(artistName);
        while (true) {
            std::cout << "Enter artist birthdate (YYYY-MM-DD): ";
            std::getline(std::cin, artistBirthDate);
            if (std::regex_match(artistBirthDate, dateRegex)) {
                artist->setBirthDate(artistBirthDate);
                break;
            }
            std::cout << "Invalid date format. Please try again.\n";
        }
        std::cout << "Enter artist style: ";
        std::getline(std::cin, artistStyle);
        artist->setStyle(artistStyle);
        while (true) {
            std::cout << "Enter creation date (YYYY-MM-DD): ";
            std::getline(std::cin, creationDate);
            if (std::regex_match(creationDate, dateRegex)) {
                break;
            }
            std::cout << "Invalid date format. Please try again.\n";
        }
        std::cout << "Enter genre: ";
        std::getline(std::cin, genre);
        painting.setTitle(title);
        painting.setArtist(artist);
        painting.setCreationDate(creationDate);
        painting.setGenre(genre);
        painting.setSold(false);
        copiedPaintings.push_back(painting);
    }
}

void Collector::displayInfo() const {
    std::cout << "Collector: " << getName() << "\nBirthday: " << getBirthDate() << std::endl;
    std:: cout << "\nOriginal paintings: " << std::endl;
    for (const auto &painting : originalPaintings) painting.displayInfo();
    std::cout << "\nCopied paintings: " << std::endl;
    for (const auto &painting : copiedPaintings) painting.displayInfo();
    std::cout << std::endl << std::endl;
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
        std::cout << "Painting does not exist. Please verify the painting details.\n";
        return;
    }

    originalPaintings.push_back(*painting);
    std::cout << getName() << " purchased " << painting->getTitle() << " for $" << price << ".\n";
}

void Collector::sortCollectorsByName(std::vector<Collector>& collectors) {
    if (collectors.empty()) {
        std::cout << "No collectors available to sort." << std::endl;
        return;
    }
    std::sort(collectors.begin(), collectors.end(), [](const Collector& a, const Collector& b) {
        return a.getName() < b.getName();
    });
    for (const auto& collector : collectors) collector.displayInfo();
}

void Collector::getDataFromObject(std::ostream &os) const {
    os << getName() << std::endl;
    os << getBirthDate() << std::endl;
    os << originalPaintings.size() << std::endl;
    for (const auto& painting : originalPaintings) {
        painting.getDataFromObject(os);
    }
    os << copiedPaintings.size() << std::endl;
    for (const auto& painting : copiedPaintings) {
        painting.getDataFromObject(os);
    }
}

void Collector::setDataToObject(std::istream &is) {
    std::string name, birthDate;
    std::getline(is, name);
    std::getline(is, birthDate);
    if (is.fail()) {
        return;
    }
    setName(name);
    setBirthDate(birthDate);
    size_t originalCount;
    is >> originalCount;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    originalPaintings.clear();
    for (size_t i = 0; i < originalCount; ++i) {
        Painting painting;
        painting.setDataToObject(is);
        originalPaintings.push_back(painting);
    }
    size_t copiedCount;
    is >> copiedCount;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    copiedPaintings.clear();
    for (size_t i = 0; i < copiedCount; ++i) {
        Painting painting;
        painting.setDataToObject(is);
        copiedPaintings.push_back(painting);
    }
}

void Collector::loadCollectors(std::vector<Collector> &collectors) {
    std::ifstream file(COLLECTOR_FILE);
    if (!file.is_open()) {
        return;
    }
    collectors.clear();
    while (file.peek() != std::ifstream::traits_type::eof()) {
        Collector collector;
        collector.setDataToObject(file);
        if (!file.fail()) {
            collectors.push_back(collector);
        }
    }
    file.close();
}

void Collector::saveCollectors(const std::vector<Collector> &collectors) {
    std::ofstream file(COLLECTOR_FILE);
    for (const auto& collector : collectors) {
        collector.getDataFromObject(file);
    }
    file.close();
}