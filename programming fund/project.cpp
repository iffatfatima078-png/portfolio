#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_FLIGHTS = 100;
const int MAX_RESERVATIONS = 100;

// Structure: Configuration struct for system settings
struct SystemConfig {
    string adminPassword;
    int startFlightID;
    int startReservationID;
    string flightFile;
    string reservationFile;

    SystemConfig() : adminPassword("admin123"), startFlightID(100),
        startReservationID(1000), flightFile("flights.txt"),
        reservationFile("reservations.txt") {
    }
};

// Template Function: Generic comparison
template <typename T>
bool isEqual(T a, T b) {
    return a == b;
}

class Person {
protected:
    string name;
    string id;
    int age;

public:
    Person() : name(""), id(""), age(0) {}
    Person(const string& personName, const string& personId, int personAge)
        : name(personName), id(personId), age(personAge) {
    }

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
        : Person(personName, personId, personAge) {
    }

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
        : flightID(id), source(src), destination(dest), date(flightDate), totalSeats(total), availableSeats(available), ticketPrice(price) {
    }

    Flight(const string& src, const string& dest, const string& flightDate,
        int total, double price)
        : flightID(++nextFlightID), source(src), destination(dest), date(flightDate), totalSeats(total), availableSeats(total), ticketPrice(price) {
    }

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
            int reduction = totalSeats - newTotalSeats;
            availableSeats = (availableSeats - reduction > 0) ? (availableSeats - reduction) : 0;
        }
        else {
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
        : reservationID(id), flightID(fID), passenger(p), seatNumber(seat) {
    }

    Reservation(int fID, const Passenger& p, int seat)
        : reservationID(++nextReservationID), flightID(fID), passenger(p), seatNumber(seat) {
    }

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
    Flight flights[MAX_FLIGHTS];
    int flightCount;
    const string fileName = "flights.txt";

    static string lowerText(const string& text) {
        string result = text;
        for (char& c : result) {
            c = static_cast<char>(tolower(c));
        }
        return result;
    }

public:
    FlightManager() : flightCount(0) { loadFlights(); }

    void loadFlights() {
        flightCount = 0;
        ifstream file(fileName);
        if (!file.is_open()) {
            ofstream create(fileName);
            return;
        }

        string line;
        int maxID = 100;
        while (getline(file, line) && flightCount < MAX_FLIGHTS) {
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

            flights[flightCount] = Flight(id, source, destination, date, totalSeats, availableSeats, price);
            flightCount++;
            if (id > maxID) maxID = id;
        }
        Flight::setNextFlightID(maxID);
        file.close();
    }

    void saveFlights() const {
        ofstream file(fileName, ios::trunc);
        for (int i = 0; i < flightCount; i++) {
            file << flights[i].toFileString() << "\n";
        }
        file.close();
    }

    void addFlight(const string& source, const string& destination,
        const string& date, int totalSeats, double price) {
        if (flightCount >= MAX_FLIGHTS) {
            throw runtime_error("Maximum flights reached.");
        }
        Flight flight(source, destination, date, totalSeats, price);
        flights[flightCount] = flight;
        flightCount++;
        saveFlights();
    }

    void viewFlights() const {
        if (flightCount == 0) {
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
        for (int i = 0; i < flightCount; i++) {
            cout << flights[i] << "\n";
        }
    }

    Flight* findFlight(int flightID) {
        for (int i = 0; i < flightCount; i++) {
            if (flights[i].getFlightID() == flightID) {
                return &flights[i];
            }
        }
        return nullptr;
    }

    void deleteFlight(int flightID) {
        int index = -1;
        for (int i = 0; i < flightCount; i++) {
            if (flights[i].getFlightID() == flightID) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            throw runtime_error("Flight ID " + to_string(flightID) + " not found.");
        }
        for (int i = index; i < flightCount - 1; i++) {
            flights[i] = flights[i + 1];
        }
        flightCount--;
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

    void searchFlights(const string& source, const string& destination, Flight results[], int& resultCount) const {
        resultCount = 0;
        string lowerSource = lowerText(source);
        string lowerDestination = lowerText(destination);
        for (int i = 0; i < flightCount && resultCount < MAX_FLIGHTS; i++) {
            if (lowerText(flights[i].getSource()) == lowerSource &&
                lowerText(flights[i].getDestination()) == lowerDestination) {
                results[resultCount] = flights[i];
                resultCount++;
            }
        }
    }
};

class ReservationManager {
private:
    Reservation reservations[MAX_RESERVATIONS];
    int reservationCount;
    const string fileName = "reservations.txt";
    FlightManager& flightManager;

public:
    ReservationManager(FlightManager& manager) : reservationCount(0), flightManager(manager) { loadReservations(); }

    void loadReservations() {
        reservationCount = 0;
        ifstream file(fileName);
        if (!file.is_open()) {
            ofstream create(fileName);
            return;
        }

        string line;
        int maxID = 1000;
        while (getline(file, line) && reservationCount < MAX_RESERVATIONS) {
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
            reservations[reservationCount] = Reservation(reservationID, flightID, passenger, seat);
            reservationCount++;
            if (reservationID > maxID) maxID = reservationID;
        }
        Reservation::setNextReservationID(maxID);
        file.close();
    }

    void saveReservations() const {
        ofstream file(fileName, ios::trunc);
        for (int i = 0; i < reservationCount; i++) {
            file << reservations[i].toFileString() << "\n";
        }
        file.close();
    }

    void bookTicket(int flightID) {
        if (reservationCount >= MAX_RESERVATIONS) {
            throw runtime_error("Maximum reservations reached.");
        }

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

        int usedSeats[MAX_RESERVATIONS];
        int usedCount = 0;
        for (int i = 0; i < reservationCount; i++) {
            if (reservations[i].getFlightID() == flightID) {
                usedSeats[usedCount] = reservations[i].getSeatNumber();
                usedCount++;
            }
        }

        int seatNumber = 1;
        bool seatFound = false;
        while (seatNumber <= flight->getTotalSeats()) {
            bool used = false;
            for (int i = 0; i < usedCount; i++) {
                if (usedSeats[i] == seatNumber) {
                    used = true;
                    break;
                }
            }
            if (!used) {
                seatFound = true;
                break;
            }
            seatNumber++;
        }

        if (!seatFound) {
            throw runtime_error("No seat numbers available.");
        }

        Passenger passenger(name, cnic, age);
        Reservation reservation(flightID, passenger, seatNumber);
        reservations[reservationCount] = reservation;
        reservationCount++;
        flight->bookSeat();
        saveReservations();
        flightManager.saveFlights();

        cout << "Ticket booked successfully.\n";
        reservation.display();
    }

    void cancelReservation(int reservationID) {
        int index = -1;
        for (int i = 0; i < reservationCount; i++) {
            if (reservations[i].getReservationID() == reservationID) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            throw runtime_error("Reservation ID " + to_string(reservationID) + " not found.");
        }

        int flightID = reservations[index].getFlightID();
        Flight* flight = flightManager.findFlight(flightID);
        if (flight == nullptr) {
            throw runtime_error("Flight not found for this reservation.");
        }

        for (int i = index; i < reservationCount - 1; i++) {
            reservations[i] = reservations[i + 1];
        }
        reservationCount--;
        flight->cancelSeat();
        saveReservations();
        flightManager.saveFlights();

        cout << "Reservation canceled and seat returned.\n";
    }

    void viewReservation(int reservationID) const {
        for (int i = 0; i < reservationCount; i++) {
            if (reservations[i].getReservationID() == reservationID) {
                reservations[i].display();
                return;
            }
        }
        throw runtime_error("Reservation ID " + to_string(reservationID) + " not found.");
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
                    }
                    else if (choice == 2) {
                        flightManager.viewFlights();
                    }
                    else if (choice == 3) {
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
                    }
                    else if (choice == 4) {
                        int flightID;
                        cout << "Enter flight ID to delete: ";
                        cin >> flightID;
                        flightManager.deleteFlight(flightID);
                        cout << "Flight deleted.\n";
                    }
                    else if (choice == 5) {
                        adminMenu = false;
                    }
                    else {
                        cout << "Please choose a valid option.\n";
                    }
                }
                catch (const exception& ex) {
                    cout << "Error: " << ex.what() << "\n";
                }
            }
        }
        else if (choice == 2) {
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
                        Flight results[MAX_FLIGHTS];
                        int resultCount = 0;
                        flightManager.searchFlights(source, destination, results, resultCount);
                        if (resultCount == 0) {
                            cout << "No flights found.\n";
                        }
                        else {
                            cout << "Matching flights:\n";
                            cout << left << setw(10) << "FlightID"
                                << setw(15) << "Source"
                                << setw(15) << "Destination"
                                << setw(12) << "Date"
                                << setw(13) << "TotalSeats"
                                << setw(15) << "AvailableSeats"
                                << "Price\n";
                            cout << string(80, '-') << "\n";
                            for (int i = 0; i < resultCount; i++) {
                                cout << results[i] << "\n";
                            }
                        }
                    }
                    else if (choice == 2) {
                        int flightID;
                        cout << "Enter flight ID to book: ";
                        cin >> flightID;
                        reservationManager.bookTicket(flightID);
                    }
                    else if (choice == 3) {
                        int reservationID;
                        cout << "Enter reservation ID to cancel: ";
                        cin >> reservationID;
                        reservationManager.cancelReservation(reservationID);
                    }
                    else if (choice == 4) {
                        int reservationID;
                        cout << "Enter reservation ID to view: ";
                        cin >> reservationID;
                        reservationManager.viewReservation(reservationID);
                    }
                    else if (choice == 5) {
                        customerMenu = false;
                    }
                    else {
                        cout << "Please choose a valid option.\n";
                    }
                }
                catch (const exception& ex) {
                    cout << "Error: " << ex.what() << "\n";
                }
            }
        }
        else if (choice == 3) {
            running = false;
        }
        else {
            cout << "Please choose 1, 2 or 3.\n";
        }
    }

    cout << "Thank you for using the Airplane Reservation System.\n";
    return 0;
}
