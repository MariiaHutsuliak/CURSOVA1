#ifndef CURSOVA_ARTIST_H
#define CURSOVA_ARTIST_H
#include "Person.h"
#include "DataHandler.h"
#include "Serializable.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <regex>

class Artist: public Person, public DataHandler  {
private:
    std::string style;
    constexpr static const std::string ARTIST_FILE = "artists.txt";

public:
    Artist();
    Artist(const std::string &name, const std::string &birthDate, const std::string &style);
    Artist(const Artist &other);
    Artist(Artist &&other) noexcept;
    Artist& operator=(const Artist& other);
    Artist& operator=(Artist&& other) noexcept;
    ~Artist() override;

    void displayInfo() const override;
    void input() override;

    [[nodiscard]] std::string getStyle() const;
    void setStyle(const std::string &style);

    static void sortArtistsByName(std::vector<Artist>& artists);
    static std::vector<Artist> filterArtistsByStyle(const std::vector<Artist>& artists, const std::string& style);
    static std::vector<Artist> searchArtistsByName(const std::vector<Artist>& artists, const std::string& name);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

    static void loadArtists(std::vector<Artist>& artists);
    static void saveArtists(const std::vector<Artist>& artists);
};


#endif //CURSOVA_ARTIST_H
