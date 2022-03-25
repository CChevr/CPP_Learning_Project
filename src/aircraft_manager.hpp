#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>
#include <set>
#include <string>

class AircraftManager : public GL::DynamicObject
{
public:
    AircraftManager() { GL::move_queue.emplace(this); }

    void add(std::unique_ptr<Aircraft> aircraft)
    {   
        auto flyNum = aircraft.get()->get_flight_num();
        if(_flyNums.find(flyNum) == _flyNums.end()) {
            _aircrafts.emplace_back(std::move(aircraft));
            _flyNums.emplace(flyNum);
        } else {
            std::cout << flyNum << " existe déjà" << std::endl;
        }
    }

    bool move() override
    {
        for (auto it = _aircrafts.begin(); it != _aircrafts.end();)
        {
            auto item = it;
            if (!(*item).get()->move())
            {   
                _flyNums.erase((*item).get()->get_flight_num());
                delete item->release();
                it = _aircrafts.erase(it);
            }
            else
            {
                ++it;
            }
        }

        return true;
    }

private:
    std::vector<std::unique_ptr<Aircraft>> _aircrafts;
    std::set<std::string> _flyNums;
};