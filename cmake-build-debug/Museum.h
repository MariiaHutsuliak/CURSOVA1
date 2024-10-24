#ifndef CURSOVA_MUSEUM_H
#define CURSOVA_MUSEUM_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Artist.h"
#include "Painting.h"
#include "Serializable.h"

class Museum : public Serializable, DataHandler{
private:
    std::string location;
    std::string title;
    std::vector<Painting> collection;

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
    void viewCollection() const;

    void input();
    void displayInfo() const override;

    void load(std::ifstream& in, const std::vector<Artist>& artists);

    static void sortMuseumsByName(std::vector<Museum>& museums);
    void organizeExhibition() const;

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;


};

#endif //CURSOVA_MUSEUM_H
