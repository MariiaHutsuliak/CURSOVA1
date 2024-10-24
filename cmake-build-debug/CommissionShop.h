#ifndef CURSOVA_COMMISSIONSHOP_H
#define CURSOVA_COMMISSIONSHOP_H
#include "DataHandler.h"
#include "Serializable.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "DataHandler.h"

class CommissionShop : public Serializable, DataHandler {
private:
    std::map<std::string,double> paintingsForSale;
public:
    CommissionShop();
    CommissionShop(const std::map<std::string, double> &paintingsForSale);
    CommissionShop(const CommissionShop &other);
    CommissionShop(CommissionShop &&other) noexcept;
    CommissionShop& operator=(const CommissionShop& other);
    CommissionShop& operator=(CommissionShop&& other) noexcept;
    ~CommissionShop() override;

    static void addCommissionShop(std::vector<CommissionShop>& shops);
    void addPainting(const std::string &painting, double price);
    void buyPainting(const std::string &painting, double price);
    void sellPainting(const std::string &painting);
    void displayInfo() const override;

    static void buyPaintingInShop(std::vector<CommissionShop>& shops);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

};


#endif //CURSOVA_COMMISSIONSHOP_H
