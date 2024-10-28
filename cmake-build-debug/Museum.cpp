#include "Museum.h"

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
    this->location = location;
}

std::string Museum::getTitle() const {
    return title;
}

void Museum::setTitle(const std::string &title) {
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
        std::cout << "Painting not found in the collection. Please check the title.\n";
    } else {
        collection.erase(it, collection.end());
        std::cout << "Painting " << paintingTitle << " removed from collection.\n";
    }
}

void Museum::input() {
    std::regex latinRegex("^[A-Za-z\\s]+$");

    while (true) {
        try {
            std::cout << "Enter name of the museum: ";
            std::getline(std::cin, title);
            if (title.empty() || !std::regex_match(title, latinRegex)) {
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
}

void Museum::displayInfo() const {
    std::cout << "Museum Name: " << title << "\n";
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
        return a.getTitle() < b.getTitle();
    });
    for (const auto& museum : museums) museum.displayInfo();
}

void Museum::addMuseum(std::vector<Museum> &museums) {
    while (true) {
        try {
            Museum newMuseum;
            newMuseum.input();
            museums.push_back(newMuseum);
            break;
        } catch (...) {
            std::cout << "An error occurred while adding the museum. Please try again.\n";
        }
    }
}

void Museum::organizeExhibition() const {
    std::cout << "Exhibition at " << location << "!\n";
    if (collection.empty()) {
        std::cout << "No paintings available for exhibition.\n";
    } else {
        std::cout << "Paintings on display:\n";
        for (const auto& painting : collection) {
            painting.displayInfo();
        }
    }
}

void Museum::getDataFromObject(std::ostream &os) const {
    os << title << std::endl;
    os << location << std::endl;
    os << collection.size() << std::endl;
    for (const auto& painting : collection) {
        painting.getDataFromObject(os);
    }
}

void Museum::setDataToObject(std::istream &is) {
    std::getline(is, title);
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
    if (file.is_open()) {
        if (file.peek() == std::ifstream::traits_type::eof()) {
            return;
        }
        while (!file.eof()) {
            Museum museum;
            museum.setDataToObject(file);
            museums.push_back(museum);
        }
        file.close();
    }
}

void Museum::saveMuseums(const std::vector<Museum> &museums) {
    std::ofstream file(MUSEUM_FILE);
    for (const auto& museum : museums) {
        museum.getDataFromObject(file);
    }
    file.close();
}