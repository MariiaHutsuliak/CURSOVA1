#ifndef CURSOVA_MUSEUM_H
#define CURSOVA_MUSEUM_H
#include "Serializable.h"
#include "DataHandler.h"
#include "Painting.h"
#include "Artist.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

class Museum : public Serializable, public DataHandler{
private:
    std::string location;
    std::string title;
    std::vector<Painting> collection;
    constexpr static const std::string MUSEUM_FILE = "museums.txt";

public:
    Museum();
    Museum(const std::string &name, const std::string &location);
    Museum(const Museum &other);
    Museum(Museum &&other) noexcept;
    Museum& operator=(const Museum& other);
    Museum& operator=(Museum&& other) noexcept;
    ~Museum() override;

    static void addMuseum(std::vector<Museum>& museums);
    [[nodiscard]] std::string getLocation() const;
    void setLocation(const std::string &location);
    [[nodiscard]] std::string getTitle() const;
    void setTitle(const std::string &title);

    void addPaintingToCollection(const Painting& painting);
    void removePaintingFromCollection(const std::string& paintingTitle);

    void input();
    void displayInfo() const override;

    static void sortMuseumsByName(std::vector<Museum>& museums);
    void organizeExhibition() const;

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

    static void loadMuseums(std::vector<Museum>& museums);
    static void saveMuseums(const std::vector<Museum>& museums);

};

#endif //CURSOVA_MUSEUM_H
