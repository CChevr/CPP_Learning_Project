#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
public:
    AircraftManager() { GL::move_queue.emplace(this); }

    void add(std::unique_ptr<Aircraft> aircraft)
    {
        aircrafts.emplace_back(std::move(aircraft));
        std::cout << "Ajouté!" << std::endl;
    }

    bool move() override
    {
        for (auto it = aircrafts.begin(); it != aircrafts.end();)
        {
            auto item = it;
            if (!(*item).get()->move())
            {
                delete item->release();
                it = aircrafts.erase(it);
            }
            else
            {
                ++it;
            }
        }

        return true;
    }

private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
};