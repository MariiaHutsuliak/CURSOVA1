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
#include "Menu.h"


int main() {
    std::cout << "Starting main()\n";
    Menu menu;
    menu.mainMenu();
    std::cout << "Program ended.\n";
    return 0;
}
