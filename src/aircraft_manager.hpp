#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <algorithm>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using AircraftCrash = class std::runtime_error;

class AircraftManager : public GL::DynamicObject
{
public:
    AircraftManager() { GL::move_queue.emplace(this); }

    void add(std::unique_ptr<Aircraft> aircraft)
    {
        auto flyNum = aircraft->get_flight_num();
        if (_flyNums.find(flyNum) == _flyNums.end())
        {
            _aircrafts.emplace_back(std::move(aircraft));
            _flyNums.emplace(flyNum);
        }
        else
        {
            std::cout << flyNum << " existe déjà" << std::endl;
        }
    }

    bool move() override
    {
        std::sort(_aircrafts.begin(), _aircrafts.end(),
                  [](const std::unique_ptr<Aircraft>& a, const std::unique_ptr<Aircraft>& b)
                  { return ((*a.get()) < (*b.get())); });

        _aircrafts.erase(std::remove_if(_aircrafts.begin(), _aircrafts.end(),
                                        [this](std::unique_ptr<Aircraft>& aircraft)
                                        {
                                            try
                                            {
                                                return !aircraft->move();
                                            } catch (const AircraftCrash& err)
                                            {
                                                _crash++;
                                                std::cerr << err.what() << std::endl;
                                                return true;
                                            }
                                        }),
                         _aircrafts.end());

        return true;
    }

    void infoAirlines(const std::string& airline)
    {
        auto count = std::count_if(_aircrafts.begin(), _aircrafts.end(),
                                   [airline](std::unique_ptr<Aircraft>& aircraft) {
                                       return (aircraft->get_flight_num()).find(airline) != std::string::npos;
                                   });

        std::cout << airline << " : " << count << std::endl;
    }

    size_t get_required_fuel() const
    {
        return std::accumulate(_aircrafts.begin(), _aircrafts.end(), (size_t)0,
                               [](size_t sum, const std::unique_ptr<Aircraft>& a) {
                                   return (a->is_low_on_fuel() && !a->has_served()) ? sum + a->get_fuel()
                                                                                    : sum;
                               });
    }

    size_t nb_crash() const { return _crash; }

private:
    std::vector<std::unique_ptr<Aircraft>> _aircrafts;
    std::set<std::string> _flyNums;
    size_t _crash = 0;
};