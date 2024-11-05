#ifndef CURSOVA_AUCTIONEER_H
#define CURSOVA_AUCTIONEER_H

#include "Person.h"
#include "Painting.h"
#include "Collector.h"
#include "DataHandler.h"
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <regex>

class Auctioneer : public Person, public DataHandler {
private:
    std::map<std::string, std::pair<std::string, double>> auctionedPaintings;
    std::string auctionDate;
    constexpr static const char* AUCTIONEER_FILE = "auctioneers.txt";

public:
    Auctioneer();
    Auctioneer(const std::string &name, const std::string &birthDate, const std::string &auctionDate);
    Auctioneer(const std::string& name, const std::string& birthDate, const std::string& auctionDate,
               const std::map<std::string, std::pair<std::string, double>>& auctionedPaintings);

    Auctioneer(const Auctioneer &other);
    Auctioneer(Auctioneer &&other) noexcept;
    Auctioneer& operator=(const Auctioneer& other);
    Auctioneer& operator=(Auctioneer&& other) noexcept;
    ~Auctioneer() override;

    [[nodiscard]] std::string getAuctionDate() const;
    void setAuctionDate(const std::string &auctionDate);

    [[nodiscard]] std::map<std::string, std::pair<std::string, double>> getAuctionedPaintings() const;

    void holdAuction(Painting* painting, std::vector<Collector*>& collectors);

    void input() override;

    void displayInfo() const override;

    static void sortAuctioneersByName(std::vector<Auctioneer>& auctioneers);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

    static void loadAuctioneers(std::vector<Auctioneer>& auctioneers);
    static void saveAuctioneers(const std::vector<Auctioneer>& auctioneers);
};

#endif //CURSOVA_AUCTIONEER_H
