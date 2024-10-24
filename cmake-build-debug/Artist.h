#ifndef CURSOVA_ARTIST_H
#define CURSOVA_ARTIST_H
#include "Person.h"
#include <string>
#include <vector>
#include "DataHandler.h"
#include "Serializable.h"

class Artist: public Person, DataHandler {
private:
    std::string style;
public:
    Artist();
    Artist(const std::string &name, const std::string &birthDate, const std::string &style);
    Artist(const Artist &other);
    Artist(Artist &&other) noexcept;
    Artist& operator=(const Artist& other);
    Artist& operator=(Artist&& other) noexcept;
    ~Artist() override;

    static void addArtist(std::vector<Artist>& artists);
    void displayInfo() const override;
    void input() override;

    [[nodiscard]] std::string getStyle() const;
    void setStyle(const std::string &style);

    static void sortArtistsByName(std::vector<Artist>& artists);
    static vector<Artist> filterArtistsByStyle(const std::vector<Artist>& artists, const std::string& style);
    static vector<Artist> searchArtistsByName(const std::vector<Artist>& artists, const std::string& name);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;


};


#endif //CURSOVA_ARTIST_H
