#ifndef CURSOVA_ADMIN_H
#define CURSOVA_ADMIN_H

#include "Serializable.h"
#include "Artist.h"
#include "Auctioneer.h"
#include "Collector.h"
#include "Museum.h"
#include "CommissionShop.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

class Admin : public Serializable {
private:
    std::string userName;
    std::string password;

    constexpr static const char* ADMIN_FILE = "admins.txt";
    constexpr static const char* ARTIST_FILE = "artists.txt";
    constexpr static const char* COLLECTOR_FILE = "collectors.txt";
    constexpr static const char* MUSEUM_FILE = "museums.txt";
    constexpr static const char* SHOP_FILE = "shops.txt";
    constexpr static const char* AUCTIONEER_FILE = "auctioneers.txt";

public:
    Admin();

    Admin(const Admin&) = delete;
    Admin& operator=(const Admin&) = delete;
    Admin(Admin&&) = delete;
    Admin& operator=(Admin&&) = delete;

    static Admin& getInstance();

    [[nodiscard]] const std::string &getUserName() const;
    void setUserName(const std::string &userName);

    [[nodiscard]] const std::string &getPassword() const;
    void setPassword(const std::string &password);

    static bool authenticateAdmin();

     static void manageModerators(std::vector<Artist>& artists, std::vector<Collector>& collectors, std::vector<Auctioneer>& auctioneers,
                                 std::vector<Museum>& museums, std::vector<CommissionShop>& shops);

    template<typename T>
    static void manageSpecificModerator(std::vector<T> &moderators, int actionChoice);

    template<typename T>
    static void addModerator(std::vector<T>& moderators);

    template<typename T>
    static void saveModeratorsToFile(const std::vector<T>& moderators, const char* fileName);

    template<typename T>
    static void removeModerator(std::vector<T>& moderators);

    template<typename T>
    static void viewModerators(const std::vector<T>& moderators);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

    void loadAdmin();
    void saveAdmin() const;
};

#endif // CURSOVA_ADMIN_H
