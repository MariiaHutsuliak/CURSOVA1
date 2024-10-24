#ifndef CURSOVA_AUCTIONEER_H
#define CURSOVA_AUCTIONEER_H
#include "Person.h"
#include "Painting.h"
#include "Collector.h"
#include "DataHandler.h"
#include <map>
#include <string>

class Auctioneer : public Person, DataHandler {
private:
    std::map<std::string,std::pair<std::string,double>> auctionedPaintings;
    std::string auctionDate;

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

    static void addAuctioneer(std::vector<Auctioneer>& auctioneers);
    void addAuctionedPainting(const std::string &painting, const std::string &date, double price);

    [[nodiscard]] std::string getAuctionDate() const;
    void setAuctionDate(const std::string &auctionDate);

    [[nodiscard]] std::map<std::string, std::pair<std::string,double>> getAuctionedPaintings() const;

    static void holdAuction(Painting* painting, vector<Collector*>& collectors);

    void input() override;
    void displayInfo() const override;
    void sellPainting(const std::string &painting);

    static void sortAuctioneersByName(std::vector<Auctioneer>& auctioneers);
    void listAuctionedPaintings() const;

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

};


#endif //CURSOVA_AUCTIONEER_H
