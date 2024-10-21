#ifndef CURSOVA_PAINTING_H
#define CURSOVA_PAINTING_H
#include "DataHandler.h"
#include <string>
#include <vector>
#include <fstream>
#include "Artist.h"

class Painting : public DataHandler{
private:
    std::string title;
    Artist* artist;
    std::string creationDate;
    std::string genre;
    bool sold;

public:
    Painting();
    Painting(const std::string& title, Artist* artist, const std::string& creationDate, const std::string& genre);
    Painting(const Painting& other);
    Painting(Painting&& other) noexcept;
    Painting& operator=(const Painting& other);
    Painting& operator=(Painting&& other) noexcept;
    ~Painting() override;

    [[nodiscard]] std::string getTitle() const;
    void setTitle(const std::string& title);

    [[nodiscard]] Artist* getArtist() const;
    void setArtist(Artist* artist);

    [[nodiscard]] std::string getCreationDate() const;
    void setCreationDate(const std::string& creationDate);

    [[nodiscard]] std::string getGenre() const;
    void setGenre(const std::string& genre);

    [[nodiscard]] bool isSold() const;
    void setSold(bool sold);

    void input();
    void displayInfo() const override;

    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    void load(std::ifstream& in, const std::vector<Artist>& artists);

    static void addPainting(std::vector<Painting>& paintings, std::vector<Artist>& artists);
    static void sortPaintingsByTitle(std::vector<Painting>& paintings);
    static std::vector<Painting> filterPaintingsByGenre(const std::vector<Painting>& paintings, const std::string& genre);
    static std::vector<Painting> searchPaintingsByTitle(const std::vector<Painting>& paintings, const std::string& title);
    [[nodiscard]] double estimateValue() const;
    void updateSaleStatus(bool sold);
};

#endif // CURSOVA_PAINTING_H