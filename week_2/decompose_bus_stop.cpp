#include <iostream>
#include <string>
#include <map>
#include <vector>

enum class QueryType 
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query 
{
    QueryType type;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};

std::istream& operator >> (std::istream &is, Query& q) 
{
    std::string operationCode;
    is >> operationCode;

    if (operationCode == "NEW_BUS") {
        q.type = QueryType::NewBus;

        is >> q.bus;

        int stopCount;
        is >> stopCount;

        q.stops.resize(stopCount);

        for (std::string &stop : q.stops)
            is >> stop;
    } else if (operationCode == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;

        is >> q.stop;
    } else if (operationCode == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;

        is >> q.bus;
    } else if (operationCode == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }


    return is;
}

struct BusesForStopResponse 
{
    std::string stop;
    std::vector<std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) 
{
    if (r.stop == "") {
        std::cout << "No stop";
    } else {
        for (const auto &bus : r.buses) {
            std::cout << bus << " ";
        }
    }

    return os;
}

struct StopsForBusResponse 
{
    std::string bus;
    std::map<std::string, std::vector<std::string>> stopsToBuses;
    std::map<std::string, std::vector<std::string>> busesToStops;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse &r) 
{
    if (r.bus == "") {
        std::cout << "No bus";
    } else {
        bool first = true;

        for (const auto &stop : r.busesToStops.at(r.bus)) {
            if (!first)
                std::cout << '\n';

            first = false;

            std::cout << "Stop " << stop << ": ";

            if (r.stopsToBuses.at(stop).size() == 1) {
                std::cout << "no interchange";
            } else {
                for (const auto &bus : r.stopsToBuses.at(stop)) {
                    if (r.bus != bus) {
                        std::cout << bus << " ";
                    }
                }
            }
        }
    }

    return os;
}

struct AllBusesResponse 
{
    std::map<std::string, std::vector<std::string>> busesToStops;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) 
{
    if (r.busesToStops.empty())
        os << "No buses";

    bool first = true;

    for (const auto& bus : r.busesToStops) {
        if (!first)
            std::cout << '\n';

        first = false;

        std::cout << "Bus " << bus.first << ": ";
        
        for (const std::string &stop : bus.second) {
            std::cout << stop << " ";
        }
    }

  return os;
}

class BusManager 
{
public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops) 
    {
        _busesToStops[bus] = stops;

        for (const auto &stop : stops) {
            _stopsToBuses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const std::string &stop) const 
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

    StopsForBusResponse GetStopsForBus(const std::string &bus) const 
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

    AllBusesResponse GetAllBuses() const 
    {
        AllBusesResponse response;
        response.busesToStops = _busesToStops;

        return response;
    }

private:
    std::map<std::string, std::vector<std::string>> _busesToStops; 
    std::map<std::string, std::vector<std::string>> _stopsToBuses;
};

// #include "unit_test_framework.h"

// void test_allBuses()
// {
//     BusManager bm;
//     Query q;
//     q.type = QueryType::AllBuses;
    
//     AllBusesResponse r;
//     r.busesToStops = {};

//     assertEqual(bm.GetAllBuses(), r, "first test");
// }

int main() {
    int query_count;
    Query q;

    // ==================================================== //

    // TestRunner testRunner;
    // testRunner.runTest(test_allBuses, "test_allBuses");

    // ==================================================== //

    std::cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        std::cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            std::cout << bm.GetBusesForStop(q.stop) << '\n';
            break;
        case QueryType::StopsForBus:
            std::cout << bm.GetStopsForBus(q.bus) << '\n';
            break;
        case QueryType::AllBuses:
            std::cout << bm.GetAllBuses() << '\n';
            break;
        }
    }

    return 0;
}