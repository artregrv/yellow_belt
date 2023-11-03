#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) 
{
    _busesToStops[bus] = stops;

    for (const auto &stop : stops) {
        _stopsToBuses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string &stop) const 
{
    BusesForStopResponse response;

    if (_stopsToBuses.count(stop) == 0) {
        response.stop = "";
        response.buses = {};
        return response;
    }

    response.stop = stop;
    response.buses = _stopsToBuses.at(stop);

    return response;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string &bus) const 
{
    StopsForBusResponse response;

    if (_busesToStops.count(bus) == 0) {
        response.bus = "";
        response.stopsToBuses = {};
        response.busesToStops = {};
        return response;
    }

    response.bus = bus;
    response.stopsToBuses = _stopsToBuses;
    response.busesToStops = _busesToStops;

    return response;
}

AllBusesResponse BusManager::GetAllBuses() const 
{
    AllBusesResponse response;
    response.busesToStops = _busesToStops;

    return response;
}