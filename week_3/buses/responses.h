#pragma once

#include <string>
#include <vector>
#include <map>

struct BusesForStopResponse 
{
    std::string stop;
    std::vector<std::string> buses;
};

struct StopsForBusResponse 
{
    std::string bus;
    std::map<std::string, std::vector<std::string>> stopsToBuses;
    std::map<std::string, std::vector<std::string>> busesToStops;
};

struct AllBusesResponse 
{
    std::map<std::string, std::vector<std::string>> busesToStops;
};

std::ostream &operator<<(std::ostream& os, const BusesForStopResponse &r);
std::ostream &operator<<(std::ostream& os, const StopsForBusResponse &r);
std::ostream &operator<<(std::ostream& os, const AllBusesResponse &r);