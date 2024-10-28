cmake_minimum_required(VERSION 3.26)
project(cursova)

set(CMAKE_CXX_STANDARD 20)

add_executable(cursova cmake-build-debug/main.cpp
        cmake-build-debug/Person.cpp
        cmake-build-debug/Person.h
        cmake-build-debug/Artist.cpp
        cmake-build-debug/Artist.h
        cmake-build-debug/Painting.cpp
        cmake-build-debug/Painting.h
        cmake-build-debug/Collector.cpp
        cmake-build-debug/Collector.h
        cmake-build-debug/DataHandler.h
        cmake-build-debug/Museum.cpp
        cmake-build-debug/Museum.h
        cmake-build-debug/Auctioneer.cpp
        cmake-build-debug/Auctioneer.h
        cmake-build-debug/CommissionShop.cpp
        cmake-build-debug/CommissionShop.h
        cmake-build-debug/Menu.cpp
        cmake-build-debug/Menu.h
        cmake-build-debug/Serializable.cpp
        cmake-build-debug/Serializable.h
        cmake-build-debug/Admin.cpp
        cmake-build-debug/Admin.h
)
