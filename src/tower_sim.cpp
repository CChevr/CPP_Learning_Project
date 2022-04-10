#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "aircraft_factory.hpp"
#include "aircraft_manager.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <utility>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_random_aircraft()
{
    auto aircraft = TowerSimulation::aircraftFactory.create_random_aircraft(TowerSimulation::airport);
    TowerSimulation::aircraftManager.add(std::move(aircraft));
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_random_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('a', []() { GL::change_tps(-1); });
    GL::keystrokes.emplace('e', []() { GL::change_tps(1); });
    GL::keystrokes.emplace('p', []() { GL::pause(); });
    GL::keystrokes.emplace(
        '1', [this]()
        { TowerSimulation::aircraftManager.infoAirlines(TowerSimulation::aircraftFactory.airlineName(0)); });
    GL::keystrokes.emplace(
        '2', [this]()
        { TowerSimulation::aircraftManager.infoAirlines(TowerSimulation::aircraftFactory.airlineName(1)); });
    GL::keystrokes.emplace(
        '3', [this]()
        { TowerSimulation::aircraftManager.infoAirlines(TowerSimulation::aircraftFactory.airlineName(2)); });
    GL::keystrokes.emplace(
        '4', [this]()
        { TowerSimulation::aircraftManager.infoAirlines(TowerSimulation::aircraftFactory.airlineName(3)); });
    GL::keystrokes.emplace(
        '5', [this]()
        { TowerSimulation::aircraftManager.infoAirlines(TowerSimulation::aircraftFactory.airlineName(4)); });
    GL::keystrokes.emplace(
        '6', [this]()
        { TowerSimulation::aircraftManager.infoAirlines(TowerSimulation::aircraftFactory.airlineName(5)); });
    GL::keystrokes.emplace(
        '7', [this]()
        { TowerSimulation::aircraftManager.infoAirlines(TowerSimulation::aircraftFactory.airlineName(6)); });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, _] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport =
        new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                      new img::Image { one_lane_airport_sprite_path.get_full_path() }, aircraftManager };

    GL::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    aircraftFactory.init_aircraft_types();

    GL::loop();
}
