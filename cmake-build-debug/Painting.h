#ifndef CURSOVA_PAINTING_H
#define CURSOVA_PAINTING_H
#include "DataHandler.h"
#include "Serializable.h"
#include "Artist.h"
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <regex>

class Painting : public Serializable, public DataHandler {
private:
    std::string title;
    std::shared_ptr<Artist> artist;
    std::string creationDate;
    std::string genre;
    bool sold;
    constexpr static const std::string PAINTING_FILE = "painting.txt";

public:
    Painting();
    Painting(const std::string& title, std::shared_ptr<Artist> artist, const std::string& creationDate, const std::string& genre);
    Painting(const Painting& other);
    Painting(Painting&& other) noexcept;
    Painting& operator=(const Painting& other);
    Painting& operator=(Painting&& other) noexcept;
    ~Painting() override;

    [[nodiscard]] std::string getTitle() const;
    void setTitle(const std::string& title);

    [[nodiscard]] Artist* getArtist() const;
    void setArtist(std::shared_ptr<Artist> artist);

    [[nodiscard]] std::string getCreationDate() const;
    void setCreationDate(const std::string& creationDate);

    [[nodiscard]] std::string getGenre() const;
    void setGenre(const std::string& genre);

    [[nodiscard]] bool getSold() const;
    void setSold(bool sold);

    void input();
    void displayInfo() const override;

    static void sortPaintingsByTitle(std::vector<Painting>& paintings);
    static std::vector<Painting> filterPaintingsByGenre(const std::vector<Painting>& paintings, const std::string& genre);
    static std::vector<Painting> searchPaintingsByTitle(const std::vector<Painting>& paintings, const std::string& title);
    [[nodiscard]] double estimateValue() const;
    void updateSaleStatus();

    void getDataFromObject(std::ostream& os) const override;
    void setDataToObject(std::istream& is) override;

    static void loadPaintings(std::vector<Painting>& paintings);
    static void savePaintings(const std::vector<Painting>& paintings);

};

#endif // CURSOVA_PAINTING_H
