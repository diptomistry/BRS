#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
using namespace std;

class BRS
{
private:
    map<string, string> busName;
    map<string, string> busNumber;
    map<string, int> totalSeats;
    map<string, double> ticketPrice; // Map to store ticket prices
    

public:
    vector<string> availableBuses;
    void addBusData(string tempBusName, string tempBusNumber, int tempTotalSeats, double tempTicketPrice)
    {
        busName[tempBusName] = tempBusName;
        busNumber[tempBusName] = tempBusNumber;
        totalSeats[tempBusName] = tempTotalSeats;
        ticketPrice[tempBusName] = tempTicketPrice; // Store the ticket price for the bus
        availableBuses.push_back(tempBusName);      // Add the bus name to the list of available buses
    }

    void saveAllData()
    {
        ofstream outputFile("bus_data.txt");

        for (auto &entry : busName)
        {
            string tempBusName = entry.first;
            string tempBusNumber = busNumber[tempBusName];
            int tempTotalSeats = totalSeats[tempBusName];
            double tempTicketPrice = ticketPrice[tempBusName];

            outputFile << "Bus Name: " << tempBusName << endl;
            outputFile << "Bus Number: " << tempBusNumber << endl;
            outputFile << "Total Seats: " << tempTotalSeats << endl;
            outputFile << "Ticket Price: Tk" << tempTicketPrice << endl;
            outputFile << "---------------------------------" << endl;
        }

        outputFile.close();
    }

    void displayAvailableBuses()
    {
        cout << "Available Buses:" << endl;
        for (size_t i = 0; i < availableBuses.size(); ++i)
        {
            cout << i + 1 << ". " << availableBuses[i] << endl;
        }
    }

    double calculateTotalPrice(string busName, int numTickets)
    {
        if (ticketPrice.find(busName) != ticketPrice.end())
        {
            double pricePerTicket = ticketPrice[busName];
            return pricePerTicket * numTickets;
        }
        else
        {
            cout << "Bus not found in the system. Cannot calculate total price." << endl;
            return 0.0;
        }
    }

    void getDataFromFile()
    {
        ifstream inputFile("bus_data.txt");
        string line;

        while (getline(inputFile, line))
        {
            cout << line << endl;
        }

        inputFile.close();
    }

    void storeUserData(string userName, string contactNumber, string busName, int numTickets, double totalPrice)
    {
        ofstream outputFile("userdata.txt", ios::app); // Append mode

        if (outputFile.is_open())
        {
            outputFile << "User Name: " << userName << endl;
            outputFile << "Contact Number: " << contactNumber << endl;
            outputFile << "Bus Name: " << busName << endl;
            outputFile << "Number of Tickets: " << numTickets << endl;
            outputFile << "Total Price: Tk" << totalPrice << endl;
            outputFile << "---------------------------------" << endl;
            outputFile.close();
        }
        else
        {
            cout << "Unable to open userdata.txt for writing." << endl;
        }
    }
};

int main()
{
    cout << "Welcome to the Bus Reservation System!" << endl;

    BRS brs;
    brs.addBusData("MM Poribohon", "101", 50, 100.0);
    brs.addBusData("AC Deluxe", "102", 40, 120.0);
    brs.addBusData("Travel Express", "103", 30, 80.0);
    brs.addBusData("Travel Express2", "104", 40, 90.0);
    brs.saveAllData();

    brs.displayAvailableBuses();

    int selectedBusIndex;
    cout << "Enter the number of the bus you want to select: ";
    cin >> selectedBusIndex;

    if (selectedBusIndex >= 1 && selectedBusIndex <= brs.availableBuses.size())
    {
        string selectedBusName = brs.availableBuses[selectedBusIndex - 1];

        cout << "You selected: " << selectedBusName << endl;

        cout << "Enter your name: ";
        string passengerName;
        cin.ignore();
        getline(cin, passengerName);

        cout << "Enter your contact number: ";
        string passengerPhoneNumber;
        cin >> passengerPhoneNumber;

        cout << "Enter the number of tickets to purchase: ";
        int numTickets;
        cin >> numTickets;

        double totalPrice = brs.calculateTotalPrice(selectedBusName, numTickets);

        if (totalPrice > 0)
        {
            cout << "Total Price: Tk" << totalPrice << endl;
            cout << "Thank you for using the Bus Reservation System! Have a great journey!" << endl;

            // Store user data
            brs.storeUserData(passengerName, passengerPhoneNumber, selectedBusName, numTickets, totalPrice);
        }
                else
        {
            cout << "Invalid number of tickets." << endl;
        }
    }
    else
    {
        cout << "Invalid bus selection." << endl;
    }

    return 0;
}
