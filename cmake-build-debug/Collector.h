#ifndef CURSOVA_COLLECTOR_H
#define CURSOVA_COLLECTOR_H

#include "Person.h"
#include "Painting.h"
#include "DataHandler.h"
#include "Serializable.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <regex>

class Collector : public Person, public DataHandler {
private:
    std::vector<Painting> originalPaintings;
    std::vector<Painting> copiedPaintings;
    constexpr static const char* COLLECTOR_FILE = "collectors.txt";

public:
    Collector();
    Collector(const std::string &name, const std::string &birthDate);
    Collector(const std::string& name, const std::string& birthDate,
              const std::vector<Painting>& originalPaintings, const std::vector<Painting>& copiedPaintings);

    Collector(const Collector &other);
    Collector(Collector &&other) noexcept;
    Collector& operator=(const Collector& other);
    Collector& operator=(Collector&& other) noexcept;
    ~Collector() override;

    [[nodiscard]] std::vector<Painting> getOriginalPaintings() const;
    [[nodiscard]] std::vector<Painting> getCopiedPaintings() const;

    void input() override;

    void displayInfo() const override;

    int placeBid(Painting* painting);

    void purchasePainting(Painting* painting, int price);

    static void sortCollectorsByName(std::vector<Collector>& collectors);

    void getDataFromObject(std::ostream &os) const override;
    void setDataToObject(std::istream &is) override;

    static void loadCollectors(std::vector<Collector>& collectors);
    static void saveCollectors(const std::vector<Collector>& collectors);
};

#endif // CURSOVA_COLLECTOR_H
