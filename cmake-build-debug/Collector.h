#ifndef CURSOVA_COLLECTOR_H
#define CURSOVA_COLLECTOR_H
#include "Person.h"
#include "Painting.h"
#include <string>
#include <vector>
#include <fstream>

class Collector: public Person {
private:
    std::vector<Painting> originalPaintings;
    std::vector<Painting> copiedPaintings;
public:
    Collector();
    Collector(const std::string &name, const std::string &birthDate);
    Collector(const std::string& name, const std::string& birthDate,
              const std::vector<Painting>& originalPaintings, const std::vector<Painting>& copiedPaintings);
    Collector(const Collector &other);
    Collector(Collector &&other) noexcept;
    Collector& operator=(const Collector& other);
    Collector& operator=(Collector&& other) noexcept;
    ~Collector();

    static void addCollector(std::vector<Collector>& collectors);
    void addOriginalPainting(const Painting& painting);
    void addCopiedPainting(const Painting& painting);

    [[nodiscard]] std::vector<Painting> getOriginalPaintings() const;
    [[nodiscard]] std::vector<Painting> getCopiedPaintings() const;

    void input() override;
    void displayInfo() const override;
    static int placeBid(Painting* painting);
    void purchasePainting(Painting* painting, int price);

    void save(std::ofstream& out) const override;
    void load(std::ifstream& out) override;
    void load(std::ifstream& in, const std::vector<Artist>& artists);
    static void sortCollectorsByName(std::vector<Collector>& collectors);
};

#endif // CURSOVA_COLLECTOR_H