#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	std::string typeString;
	is >> typeString;

	if (typeString == "NEW_BUS") {
		q.type = QueryType::NewBus;
		int stopsCount;
		is >> stopsCount;
		q.stops.resize(stopsCount);
		for (auto &stop : q.stops) {
			is >> stop;
		}
	} else if (typeString == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	} else if (typeString == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	} else if (typeString == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	
	return is;
}

struct BusesForStopResponse {
	std::map<std::string, std::vector<std::string>> stopsToBuses;
};

ostream& operator << (ostream& os, const BusesForStopResponse &r) 
{
	if (r.stopsToBuses.count(stop) == 0) {
    	os << "No stop" << endl;
    } else {
        for (const string& bus : r.stopsToBuses[stop]) {
          	os << bus << " ";
        }
       	os << endl;
	}

  	return os;
}

struct StopsForBusResponse {
	std::map<std::string, std::vector<std::string>> stopsForBus;
};

ostream& operator << (ostream& os, const StopsForBusResponse &r) 
{

}

struct AllBusesResponse {
	std::map<std::string, std::vector<std::string>> busesToStops;
};

ostream& operator << (ostream &os, const AllBusesResponse &r) {
	if (r.busesToStops.empty()) {
        os << "No buses" << endl;
    } else {
        for (const auto& busItem : r.busesToStops) {
          	os << "Bus " << busItem.first << ": ";
          	for (const string &stop : busItem.second) {
            	os << stop << " ";
          	}
          os << endl;
        }
    }
	return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
  }

  	BusesForStopResponse GetBusesForStop(const string& stop) const 
	{

  	}

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
  }

  	AllBusesResponse GetAllBuses() const 
	{
		AllBusesResponse response;
		response.busesToStops = _busesToStops;
		return response;
  	}

private:
	map<string, vector<string>> _busesToStops, _stopsToBuses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

/*int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}*/

int main() {
  int q;
  cin >> q;

  map<string, vector<string>> buses_to_stops, stops_to_buses;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "NEW_BUS") {

      string bus;
      cin >> bus;
      int stop_count;
      cin >> stop_count;
      vector<string>& stops = buses_to_stops[bus];
      stops.resize(stop_count);
      for (string& stop : stops) {
        cin >> stop;
        stops_to_buses[stop].push_back(bus);
      }

    } else if (operation_code == "BUSES_FOR_STOP") {

      string stop;
      cin >> stop;
      if (stops_to_buses.count(stop) == 0) {
        cout << "No stop" << endl;
      } else {
        for (const string& bus : stops_to_buses[stop]) {
          cout << bus << " ";
        }
        cout << endl;
      }

    } else if (operation_code == "STOPS_FOR_BUS") {

      string bus;
      cin >> bus;
      if (buses_to_stops.count(bus) == 0) {
        cout << "No bus" << endl;
      } else {
        for (const string& stop : buses_to_stops[bus]) {
          cout << "Stop " << stop << ": ";
          if (stops_to_buses[stop].size() == 1) {
            cout << "no interchange";
          } else {
            for (const string& other_bus : stops_to_buses[stop]) {
              if (bus != other_bus) {
                cout << other_bus << " ";
              }
            }
          }
          cout << endl;
        }
      }

    } else if (operation_code == "ALL_BUSES") {

      if (buses_to_stops.empty()) {
        cout << "No buses" << endl;
      } else {
        for (const auto& bus_item : buses_to_stops) {
          cout << "Bus " << bus_item.first << ": ";
          for (const string& stop : bus_item.second) {
            cout << stop << " ";
          }
          cout << endl;
        }
      }

    }
  }

  return 0;
}
