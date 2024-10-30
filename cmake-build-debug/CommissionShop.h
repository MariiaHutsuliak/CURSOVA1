#ifndef CURSOVA_COMMISSIONSHOP_H
#define CURSOVA_COMMISSIONSHOP_H
#include "DataHandler.h"
#include "Serializable.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <regex>

class CommissionShop : public Serializable, public DataHandler {
private:
    std::string name;
    std::map<std::string, double> paintingsForSale;
    constexpr static const char* SHOP_FILE = "shops.txt";

public:
    CommissionShop();
    CommissionShop(const std::string& name, const std::map<std::string, double>& paintingsForSale);
    CommissionShop(const CommissionShop &other);
    CommissionShop(CommissionShop &&other) noexcept;
    CommissionShop& operator=(const CommissionShop& other);
    CommissionShop& operator=(CommissionShop&& other) noexcept;
    ~CommissionShop() override;

    void setName(const std::string& name);
    [[nodiscard]] std::string getName() const;

    void input();
    void buyPainting(const std::string& painting, double price);
    void sellPainting(const std::string& painting);
    void displayInfo() const override;

    static void buyPaintingInShop(std::vector<CommissionShop>& shops);
    static void sellPaintingInShop(std::vector<CommissionShop> &shops);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

    static void loadShops(std::vector<CommissionShop>& shops);
    static void saveShops(const std::vector<CommissionShop>& shops);

};
#endif // CURSOVA_COMMISSIONSHOP_H
