#pragma once

#include <vector>
#include <memory>

#include "aircraft.hpp"

class AircraftManager {
    public:
    void add(std::unique_ptr<Aircraft> aircraft) {
        aircrafts.emplace_back(std::move(aircraft));
        std::cout << "Ajouté!" << std::endl;
    }

    private:
        std::vector<std::unique_ptr<Aircraft>> aircrafts;

};