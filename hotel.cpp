#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

struct Room {
    int roomNumber;
    string roomType;
    string availability;
    double pricePerNight;
    string amenities;
    string view;
};

vector<Room> rooms;
map<string, string> users; // Username and password map

void loadRoomData(const string& filePath) {
    ifstream file(filePath);
    if (!file) {
        cout << "Room data file not found. Initializing empty data.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Room room;
        string price;
        string roomNumber;
        
        // Parsing CSV file correctly by reading each column
        getline(ss, roomNumber, ',');
        getline(ss, room.roomType, ',');
        getline(ss, room.availability, ',');
        getline(ss, price, ',');
        getline(ss, room.amenities, ',');
        getline(ss, room.view, ',');
        
        room.roomNumber = stoi(roomNumber);
        room.pricePerNight = stod(price);
        rooms.push_back(room);
    }
    file.close();
}

void saveRoomData(const string& filePath) {
    ofstream file(filePath);
    for (const Room& room : rooms) {
        file << room.roomNumber << "," << room.roomType << "," << room.availability << ","
             << room.pricePerNight << "," << room.amenities << "," << room.view << "\n";
    }
    file.close();
}

void addRoom() {
    Room room;
    cout << "Enter Room Number: ";
    cin >> room.roomNumber;
    cout << "Enter Room Type: ";
    cin.ignore();
    getline(cin, room.roomType);
    cout << "Enter Availability: ";
    getline(cin, room.availability);
    cout << "Enter Price Per Night: ";
    cin >> room.pricePerNight;
    cin.ignore();
    cout << "Enter Amenities: ";
    getline(cin, room.amenities);
    cout << "Enter View: ";
    getline(cin, room.view);
    rooms.push_back(room);
    cout << "Room added successfully.\n";
}

void viewRooms() {
    for (const Room& room : rooms) {
        cout << "Room Number: " << room.roomNumber << "\n"
             << "Room Type: " << room.roomType << "\n"
             << "Availability: " << room.availability << "\n"
             << "Price Per Night: " << room.pricePerNight << "\n"
             << "Amenities: " << room.amenities << "\n"
             << "View: " << room.view << "\n\n";
    }
}

void viewSpecificRoom() {
    int roomNumber;
    cout << "Enter Room Number: ";
    cin >> roomNumber;
    for (const Room& room : rooms) {
        if (room.roomNumber == roomNumber) {
            cout << "Room Number: " << room.roomNumber << "\n"
                 << "Room Type: " << room.roomType << "\n"
                 << "Availability: " << room.availability << "\n"
                 << "Price Per Night: " << room.pricePerNight << "\n"
                 << "Amenities: " << room.amenities << "\n"
                 << "View: " << room.view << "\n";
            return;
        }
    }
    cout << "Room not found.\n";
}

void editRoom() {
    int roomNumber;
    cout << "Enter Room Number to edit: ";
    cin >> roomNumber;
    for (Room& room : rooms) {
        if (room.roomNumber == roomNumber) {
            cout << "Enter new Room Type: ";
            cin.ignore();
            getline(cin, room.roomType);
            cout << "Enter new Availability: ";
            getline(cin, room.availability);
            cout << "Enter new Price Per Night: ";
            cin >> room.pricePerNight;
            cin.ignore();
            cout << "Enter new Amenities: ";
            getline(cin, room.amenities);
            cout << "Enter new View: ";
            getline(cin, room.view);
            cout << "Room data updated successfully.\n";
            return;
        }
    }
    cout << "Room not found.\n";
}

void deleteRoom() {
    int roomNumber;
    cout << "Enter Room Number to delete: ";
    cin >> roomNumber;
    rooms.erase(remove_if(rooms.begin(), rooms.end(), [roomNumber](const Room& room) {
        return room.roomNumber == roomNumber;
    }), rooms.end());
    cout << "Room deleted successfully.\n";
}

void login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username] == password) {
        cout << "Login successful!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

int main() {
    users["admin"] = "password"; // Default user
    string filePath = "hotelmanagement.csv";

    loadRoomData(filePath);

    while (true) {
        cout << "\nWelcome to Hotel Lakeview Luxury Hotel!\n"
             << "1. Add Room Data\n"
             << "2. View All Rooms\n"
             << "3. View Specific Room(s)\n"
             << "4. Edit Room Data\n"
             << "5. Delete Room Data\n"
             << "6. Exit\n"
             << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addRoom();
                saveRoomData(filePath);
                break;
            case 2:
                viewRooms();
                break;
            case 3:
                viewSpecificRoom();
                break;
            case 4:
                editRoom();
                saveRoomData(filePath);
                break;
            case 5:
                deleteRoom();
                saveRoomData(filePath);
                break;
            case 6:
                cout << "Thanks for visiting!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}


