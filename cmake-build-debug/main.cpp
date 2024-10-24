#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include "DataHandler.h"
#include "Person.h"
#include "Artist.h"
#include "Painting.h"
#include "Collector.h"
#include "Museum.h"
#include "Auctioneer.h"
#include "CommissionShop.h"
#include "Admin.h"
#include "FileManager.h"
#include "Menu.h"

using namespace std;


int main() {

//    Admin admin = {"name", "1234"};
//    FileManager::writeToFile("admin.txt", admin);
//    std::map<std::string, std::pair<std::string, double>> paintings = {
//            {"Mona Lisa", {"Leonardo da Vinci", 850.0}},
//            {"Starry Night", {"Vincent van Gogh", 100.0}}
//    };
//    Auctioneer auctioneer3("John Doe", "1980-05-15", "2024-12-10", paintings);
//    auctioneer3.displayInfo();
//    FileManager::writeToFile("auctioneer.txt", auctioneer3);
//    Auctioneer auctioneer;
//    FileManager::downloadFromFile("auctioneer.txt", auctioneer);
//    auctioneer.displayInfo();
//    Artist artist1 = {"name", "1768-09-09", "immpressionism"};
//    FileManager::writeToFile("artist.txt", artist);
//    Artist artist1;
//    FileManager::downloadFromFile("artist.txt", artist1);
//    artist1.displayInfo();
//    std::vector<std::shared_ptr<Artist>> artists;
//    artists.push_back(std::make_shared<Artist>("Vincent van Gogh", "1853-1890", "Post-Impressionism"));
//    artists.push_back(std::make_shared<Artist>("Claude Monet", "1840-1926", "Impressionism"));
//
//    Painting painting1("Starry Night", artists[0], "1889", "Post-Impressionism");
//    Painting painting2("Water Lilies", artists[1], "1916", "Impressionism");
//    FileManager::writeToFile("painting.txt", painting1);
//     FileManager::writeToFile("painting.txt", painting2);
//     painting.displayInfo();
//     Painting painting3;
//     FileManager::downloadFromFile("painting.txt", painting3);
//     painting3.displayInfo();
//    CommissionShop shop;
//    shop.addPainting("Mona Lisa", 1500.0);
//    shop.addPainting("Starry Night", 2000.0);
//    FileManager::writeToFile("commissionShop.txt", shop);
//    shop.displayInfo();
//    CommissionShop shop1;
//    FileManager::downloadFromFile("commissionShop.txt", shop1);
//    shop1.displayInfo();
//    Collector collector("John Doe", "01/01/1980");
//    collector.addOriginalPainting(painting1);
//    collector.addCopiedPainting(painting2);
//    FileManager::writeToFile("collector.txt", collector);
//    collector.displayInfo();
//    Collector collector1;
//    FileManager::downloadFromFile("collector.txt", collector1);
//    collector1.displayInfo();
//    Museum museum("The Art Gallery", "New York");
//    museum.addPaintingToCollection(painting1);
//    museum.addPaintingToCollection(painting2);
//    FileManager::writeToFile("museum.txt", museum);
//    museum.displayInfo();
//    Museum museum1;
//    FileManager::downloadFromFile("museum.txt", museum1);
//    museum1.displayInfo();
    int choice = 0;
    cin >> choice;


    return 0;
}
