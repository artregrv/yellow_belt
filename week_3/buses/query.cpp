#include "query.h"

#include <iostream>

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