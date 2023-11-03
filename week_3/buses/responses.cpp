#include "responses.h"

#include <iostream>

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) 
{
    if (r.stop == "") {
        os << "No stop";
    } else {
        for (const auto &bus : r.buses) {
            os << bus << " ";
        }
    }

    return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse &r) 
{
    if (r.bus == "") {
        os << "No bus";
    } else {
        bool first = true;

        for (const auto &stop : r.busesToStops.at(r.bus)) {
            if (!first)
                os << '\n';

            first = false;

            os << "Stop " << stop << ": ";

            if (r.stopsToBuses.at(stop).size() == 1) {
                os << "no interchange";
            } else {
                for (const auto &bus : r.stopsToBuses.at(stop)) {
                    if (r.bus != bus) {
                        os << bus << " ";
                    }
                }
            }
        }
    }

    return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) 
{
    if (r.busesToStops.empty())
        os << "No buses";

    bool first = true;

    for (const auto& bus : r.busesToStops) {
        if (!first)
            os << '\n';

        first = false;

        os << "Bus " << bus.first << ": ";
        
        for (const std::string &stop : bus.second) {
            os << stop << " ";
        }
    }

  return os;
}