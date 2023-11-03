#pragma once

#include "responses.h"

class BusManager 
{
public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops);
    BusesForStopResponse GetBusesForStop(const std::string &stop) const;
    StopsForBusResponse GetStopsForBus(const std::string &bus) const;
    AllBusesResponse GetAllBuses() const;

private:
    std::map<std::string, std::vector<std::string>> _busesToStops; 
    std::map<std::string, std::vector<std::string>> _stopsToBuses;
};