#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Person {
protected:
    string name;
    string id;
    int age;

public:
    Person() : name(""), id(""), age(0) {}
    Person(const string& personName, const string& personId, int personAge)
        : name(personName), id(personId), age(personAge) {}

    virtual ~Person() {}
    virtual void display() const = 0;

    string getName() const { return name; }
    string getId() const { return id; }
    int getAge() const { return age; }
};

class Passenger : public Person {
public:
    Passenger() : Person() {}
    Passenger(const string& personName, const string& personId, int personAge)
        : Person(personName, personId, personAge) {}

    void display() const override {
        cout << "Passenger Name: " << name << "\n";
        cout << "CNIC / ID    : " << id << "\n";
        cout << "Age          : " << age << "\n";
    }
};

class Flight {
private:
    int flightID;
    string source;
    string destination;
    string date;
    int totalSeats;
    int availableSeats;
    double ticketPrice;
    static int nextFlightID;

public:
    Flight() : flightID(0), source(""), destination(""), date(""), totalSeats(0), availableSeats(0), ticketPrice(0) {}

    Flight(int id, const string& src, const string& dest, const string& flightDate,
           int total, int available, double price)
        : flightID(id), source(src), destination(dest), date(flightDate), totalSeats(total), availableSeats(available), ticketPrice(price) {}

    Flight(const string& src, const string& dest, const string& flightDate,
           int total, double price)
        : flightID(++nextFlightID), source(src), destination(dest), date(flightDate), totalSeats(total), availableSeats(total), ticketPrice(price) {}

    static void setNextFlightID(int value) { nextFlightID = value; }

    int getFlightID() const { return flightID; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    string getDate() const { return date; }
    int getTotalSeats() const { return totalSeats; }
    int getAvailableSeats() const { return availableSeats; }
    double getTicketPrice() const { return ticketPrice; }

    bool hasSeats() const { return availableSeats > 0; }

    void bookSeat() {
        if (availableSeats <= 0) {
            throw runtime_error("No seats available on flight " + to_string(flightID));
        }
        availableSeats--;
    }

    void cancelSeat() {
        if (availableSeats < totalSeats) {
            availableSeats++;
        }
    }

    void updateFlight(const string& newSource, const string& newDestination,
                      const string& newDate, int newTotalSeats, double newPrice) {
        source = newSource;
        destination = newDestination;
        date = newDate;
        ticketPrice = newPrice;
        if (newTotalSeats < totalSeats) {
            availableSeats = max(0, availableSeats - (totalSeats - newTotalSeats));
        } else {
            availableSeats += newTotalSeats - totalSeats;
        }
        totalSeats = newTotalSeats;
    }

    string toFileString() const {
        stringstream ss;
        ss << flightID << "," << source << "," << destination << "," << date << ","
           << totalSeats << "," << availableSeats << "," << ticketPrice;
        return ss.str();
    }

    friend ostream& operator<<(ostream& os, const Flight& flight) {
        os << left << setw(10) << flight.flightID
           << setw(15) << flight.source
           << setw(15) << flight.destination
           << setw(12) << flight.date
           << setw(13) << flight.totalSeats
           << setw(15) << flight.availableSeats
           << fixed << setprecision(2) << flight.ticketPrice;
        return os;
    }
};

int Flight::nextFlightID = 100;

class Reservation {
private:
    int reservationID;
    int flightID;
    Passenger passenger;
    int seatNumber;
    static int nextReservationID;

public:
    Reservation() : reservationID(0), flightID(0), passenger(), seatNumber(0) {}

    Reservation(int id, int fID, const Passenger& p, int seat)
        : reservationID(id), flightID(fID), passenger(p), seatNumber(seat) {}

    Reservation(int fID, const Passenger& p, int seat)
        : reservationID(++nextReservationID), flightID(fID), passenger(p), seatNumber(seat) {}

    static void setNextReservationID(int value) { nextReservationID = value; }

    int getReservationID() const { return reservationID; }
    int getFlightID() const { return flightID; }
    int getSeatNumber() const { return seatNumber; }

    string toFileString() const {
        stringstream ss;
        ss << reservationID << "," << flightID << "," << passenger.getName() << ","
           << passenger.getId() << "," << passenger.getAge() << "," << seatNumber;
        return ss.str();
    }

    void display() const {
        cout << "--- Reservation Details ---\n";
        cout << "Reservation ID: " << reservationID << "\n";
        cout << "Flight ID      : " << flightID << "\n";
        cout << "Seat Number    : " << seatNumber << "\n";
        passenger.display();
        cout << "---------------------------\n";
    }
};

int Reservation::nextReservationID = 1000;

class FlightManager {
private:
    vector<Flight> flights;
    const string fileName = "flights.txt";

    static string lowerText(const string& text) {
        string result = text;
        for (char& c : result) {
            c = static_cast<char>(tolower(c));
        }
        return result;
    }

public:
    FlightManager() { loadFlights(); }

    void loadFlights() {
        flights.clear();
        ifstream file(fileName);
        if (!file.is_open()) {
            ofstream create(fileName);
            return;
        }

        string line;
        int maxID = 100;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string token;
            int id, totalSeats, availableSeats;
            double price;
            string source, destination, date;

            getline(ss, token, ',');
            id = stoi(token);
            getline(ss, source, ',');
            getline(ss, destination, ',');
            getline(ss, date, ',');
            getline(ss, token, ',');
            totalSeats = stoi(token);
            getline(ss, token, ',');
            availableSeats = stoi(token);
            getline(ss, token, ',');
            price = stod(token);

            flights.emplace_back(id, source, destination, date, totalSeats, availableSeats, price);
            if (id > maxID) maxID = id;
        }
        Flight::setNextFlightID(maxID);
    }

    void saveFlights() const {
        ofstream file(fileName, ios::trunc);
        for (const Flight& flight : flights) {
            file << flight.toFileString() << "\n";
        }
    }

    void addFlight(const string& source, const string& destination,
                   const string& date, int totalSeats, double price) {
        Flight flight(source, destination, date, totalSeats, price);
        flights.push_back(flight);
        saveFlights();
    }

    void viewFlights() const {
        if (flights.empty()) {
            cout << "No flights available.\n";
            return;
        }
        cout << left << setw(10) << "FlightID"
                  << setw(15) << "Source"
                  << setw(15) << "Destination"
                  << setw(12) << "Date"
                  << setw(13) << "TotalSeats"
                  << setw(15) << "AvailableSeats"
                  << "Price\n";
        cout << string(80, '-') << "\n";
        for (const Flight& flight : flights) {
            cout << flight << "\n";
        }
    }

    Flight* findFlight(int flightID) {
        for (Flight& flight : flights) {
            if (flight.getFlightID() == flightID) return &flight;
        }
        return nullptr;
    }

    void deleteFlight(int flightID) {
        auto it = remove_if(flights.begin(), flights.end(), [flightID](const Flight& flight) {
            return flight.getFlightID() == flightID;
        });
        if (it == flights.end()) {
            throw runtime_error("Flight ID " + to_string(flightID) + " not found.");
        }
        flights.erase(it, flights.end());
        saveFlights();
    }

    void updateFlight(int flightID, const string& source, const string& destination,
                      const string& date, int totalSeats, double price) {
        Flight* flight = findFlight(flightID);
        if (flight == nullptr) {
            throw runtime_error("Flight ID " + to_string(flightID) + " not found.");
        }
        flight->updateFlight(source, destination, date, totalSeats, price);
        saveFlights();
    }

    vector<Flight> searchFlights(const string& source, const string& destination) const {
        vector<Flight> result;
        string lowerSource = lowerText(source);
        string lowerDestination = lowerText(destination);
        for (const Flight& flight : flights) {
            if (lowerText(flight.getSource()) == lowerSource &&
                lowerText(flight.getDestination()) == lowerDestination) {
                result.push_back(flight);
            }
        }
        return result;
    }
};

class ReservationManager {
private:
    vector<Reservation> reservations;
    const string fileName = "reservations.txt";
    FlightManager& flightManager;

public:
    ReservationManager(FlightManager& manager) : flightManager(manager) { loadReservations(); }

    void loadReservations() {
        reservations.clear();
        ifstream file(fileName);
        if (!file.is_open()) {
            ofstream create(fileName);
            return;
        }

        string line;
        int maxID = 1000;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string token;
            int reservationID;
            int flightID;
            string name;
            string cnic;
            int age;
            int seat;

            getline(ss, token, ',');
            reservationID = stoi(token);
            getline(ss, token, ',');
            flightID = stoi(token);
            getline(ss, name, ',');
            getline(ss, cnic, ',');
            getline(ss, token, ',');
            age = stoi(token);
            getline(ss, token, ',');
            seat = stoi(token);

            Passenger passenger(name, cnic, age);
            reservations.emplace_back(reservationID, flightID, passenger, seat);
            if (reservationID > maxID) maxID = reservationID;
        }
        Reservation::setNextReservationID(maxID);
    }

    void saveReservations() const {
        ofstream file(fileName, ios::trunc);
        for (const Reservation& reservation : reservations) {
            file << reservation.toFileString() << "\n";
        }
    }

    void bookTicket(int flightID) {
        Flight* flight = flightManager.findFlight(flightID);
        if (flight == nullptr) {
            throw runtime_error("Flight ID " + to_string(flightID) + " not found.");
        }
        if (!flight->hasSeats()) {
            throw runtime_error("No seats available on this flight.");
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string name;
        string cnic;
        int age;

        cout << "Enter passenger name: ";
        getline(cin, name);
        cout << "Enter CNIC/ID: ";
        getline(cin, cnic);
        cout << "Enter age: ";
        cin >> age;

        if (age <= 0) {
            throw runtime_error("Age must be positive.");
        }

        vector<int> usedSeats;
        for (const Reservation& r : reservations) {
            if (r.getFlightID() == flightID) {
                usedSeats.push_back(r.getSeatNumber());
            }
        }

        int seatNumber = 1;
        while (find(usedSeats.begin(), usedSeats.end(), seatNumber) != usedSeats.end()) {
            seatNumber++;
        }
        if (seatNumber > flight->getTotalSeats()) {
            throw runtime_error("No seat numbers available.");
        }

        Passenger passenger(name, cnic, age);
        Reservation reservation(flightID, passenger, seatNumber);
        reservations.push_back(reservation);
        flight->bookSeat();
        saveReservations();
        flightManager.saveFlights();

        cout << "Ticket booked successfully.\n";
        reservation.display();
    }

    void cancelReservation(int reservationID) {
        auto it = find_if(reservations.begin(), reservations.end(), [reservationID](const Reservation& r) {
            return r.getReservationID() == reservationID;
        });
        if (it == reservations.end()) {
            throw runtime_error("Reservation ID " + to_string(reservationID) + " not found.");
        }

        int flightID = it->getFlightID();
        Flight* flight = flightManager.findFlight(flightID);
        if (flight == nullptr) {
            throw runtime_error("Flight not found for this reservation.");
        }

        reservations.erase(it);
        flight->cancelSeat();
        saveReservations();
        flightManager.saveFlights();

        cout << "Reservation canceled and seat returned.\n";
    }

    void viewReservation(int reservationID) const {
        auto it = find_if(reservations.begin(), reservations.end(), [reservationID](const Reservation& r) {
            return r.getReservationID() == reservationID;
        });
        if (it == reservations.end()) {
            throw runtime_error("Reservation ID " + to_string(reservationID) + " not found.");
        }
        it->display();
    }
};

void showAdminMenu() {
    cout << "\n--- Admin Panel ---\n";
    cout << "1. Add Flight\n";
    cout << "2. View All Flights\n";
    cout << "3. Update Flight\n";
    cout << "4. Delete Flight\n";
    cout << "5. Back to Main Menu\n";
    cout << "Choose an option: ";
}

void showCustomerMenu() {
    cout << "\n--- Customer Panel ---\n";
    cout << "1. Search Flights\n";
    cout << "2. Book Ticket\n";
    cout << "3. Cancel Ticket\n";
    cout << "4. View Reservation\n";
    cout << "5. Back to Main Menu\n";
    cout << "Choose an option: ";
}

int main() {
    FlightManager flightManager;
    ReservationManager reservationManager(flightManager);
    const string adminPassword = "admin123";
    bool running = true;

    while (running) {
        cout << "\n=== Airplane Reservation System ===\n";
        cout << "1. Admin Panel\n";
        cout << "2. Customer Panel\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string password;
            cout << "Enter admin password: ";
            getline(cin, password);
            if (password != adminPassword) {
                cout << "Password is wrong.\n";
                continue;
            }

            bool adminMenu = true;
            while (adminMenu) {
                showAdminMenu();
                cin >> choice;
                try {
                    if (choice == 1) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        string source;
                        string destination;
                        string date;
                        int totalSeats;
                        double price;

                        cout << "Enter source city: ";
                        getline(cin, source);
                        cout << "Enter destination city: ";
                        getline(cin, destination);
                        cout << "Enter flight date (YYYY-MM-DD): ";
                        getline(cin, date);
                        cout << "Enter total seats: ";
                        cin >> totalSeats;
                        cout << "Enter ticket price: ";
                        cin >> price;
                        flightManager.addFlight(source, destination, date, totalSeats, price);
                        cout << "Flight added.\n";
                    } else if (choice == 2) {
                        flightManager.viewFlights();
                    } else if (choice == 3) {
                        int flightID;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter flight ID to update: ";
                        cin >> flightID;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        string source;
                        string destination;
                        string date;
                        int totalSeats;
                        double price;
                        cout << "Enter new source city: ";
                        getline(cin, source);
                        cout << "Enter new destination city: ";
                        getline(cin, destination);
                        cout << "Enter new flight date (YYYY-MM-DD): ";
                        getline(cin, date);
                        cout << "Enter new total seats: ";
                        cin >> totalSeats;
                        cout << "Enter new ticket price: ";
                        cin >> price;
                        flightManager.updateFlight(flightID, source, destination, date, totalSeats, price);
                        cout << "Flight updated.\n";
                    } else if (choice == 4) {
                        int flightID;
                        cout << "Enter flight ID to delete: ";
                        cin >> flightID;
                        flightManager.deleteFlight(flightID);
                        cout << "Flight deleted.\n";
                    } else if (choice == 5) {
                        adminMenu = false;
                    } else {
                        cout << "Please choose a valid option.\n";
                    }
                } catch (const exception& ex) {
                    cout << "Error: " << ex.what() << "\n";
                }
            }
        } else if (choice == 2) {
            bool customerMenu = true;
            while (customerMenu) {
                showCustomerMenu();
                cin >> choice;
                try {
                    if (choice == 1) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        string source;
                        string destination;
                        cout << "Enter source city: ";
                        getline(cin, source);
                        cout << "Enter destination city: ";
                        getline(cin, destination);
                        vector<Flight> results = flightManager.searchFlights(source, destination);
                        if (results.empty()) {
                            cout << "No flights found.\n";
                        } else {
                            cout << "Matching flights:\n";
                            cout << left << setw(10) << "FlightID"
                                      << setw(15) << "Source"
                                      << setw(15) << "Destination"
                                      << setw(12) << "Date"
                                      << setw(13) << "TotalSeats"
                                      << setw(15) << "AvailableSeats"
                                      << "Price\n";
                            cout << string(80, '-') << "\n";
                            for (const Flight& flight : results) {
                                cout << flight << "\n";
                            }
                        }
                    } else if (choice == 2) {
                        int flightID;
                        cout << "Enter flight ID to book: ";
                        cin >> flightID;
                        reservationManager.bookTicket(flightID);
                    } else if (choice == 3) {
                        int reservationID;
                        cout << "Enter reservation ID to cancel: ";
                        cin >> reservationID;
                        reservationManager.cancelReservation(reservationID);
                    } else if (choice == 4) {
                        int reservationID;
                        cout << "Enter reservation ID to view: ";
                        cin >> reservationID;
                        reservationManager.viewReservation(reservationID);
                    } else if (choice == 5) {
                        customerMenu = false;
                    } else {
                        cout << "Please choose a valid option.\n";
                    }
                } catch (const exception& ex) {
                    cout << "Error: " << ex.what() << "\n";
                }
            }
        } else if (choice == 3) {
            running = false;
        } else {
            cout << "Please choose 1, 2 or 3.\n";
        }
    }

    cout << "Thank you for using the Airplane Reservation System.\n";
    return 0;
}
