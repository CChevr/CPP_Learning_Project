#pragma once

#include "aircraft.hpp"
#include "airport.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

class AircraftFactory
{
public:
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport)
    {
        assert(airport); // make sure the airport is initialized before creating aircraft

        const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
        const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
        const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
        const Point3D direction = (-start).normalize();

        return std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
    }

    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport)
    {
        assert(airport);
        return create_aircraft(*(aircraft_types[rand() % NUM_AIRCRAFT_TYPES]), airport);
    }

    // note: textures have to be initialized after initializing glut, so we'll need
    // our own init here
    void init_aircraft_types()
    {
        // executed once
        assert(aircraft_types[0] == nullptr && aircraft_types[1] == nullptr && aircraft_types[2] == nullptr);

        aircraft_types[0] = new AircraftType { .02f, .05f, .02f, 1, 3000, MediaPath { "l1011_48px.png" } };
        aircraft_types[1] = new AircraftType { .02f, .05f, .02f, 1, 3000, MediaPath { "b707_jat.png" } };
        aircraft_types[2] = new AircraftType { .02f, .07f, .02f, 1, 3000, MediaPath { "concorde_af.png" } };
    }

    const std::string& airlineName(size_t index) const { return airlines[index]; }

private:
    const size_t NUM_AIRCRAFT_TYPES = 3;
    const std::string airlines[8]   = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[3] {};
};