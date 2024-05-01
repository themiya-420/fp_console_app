#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime> 
#include <iomanip> 

using namespace std;

// Define structs to represent Room and Booking
struct Room
{
    string id;
    string type;
    double price;
    string available;
};

struct Booking
{
    string guestName;
    vector<Room> roomsBooked;
    float totalBill;
    // Other booking details like check-in date, check-out date can be added here
};

// Function prototypes
void displayMainMenu();
void displayRoomManagementMenu();
void displayBookingManagementMenu();
void displayBookings();
void bookRoom();
void viewRooms();
void searchRoomById();
void addRoom(vector<Room>& rooms);
void saveRoomsToFile(const vector<Room>& rooms);
// Other function prototypes for room and booking management

// Global variables
vector<Room> rooms;
vector<Booking> bookings;


bool login(const std::string& username, const std::string& password) {
    if (username == "admin" && password == "admin") {
        return true;
    } else {
        return false;
    }
}

void handleLogin() {
    std::string username_input, password_input;

    std::cout << "Enter username: ";
    std::cin >> username_input;

    std::cout << "Enter password: ";
    std::cin >> password_input;

    if (login(username_input, password_input)) {
        std::cout << "Login successful!" << std::endl;
        displayMainMenu();
    } else {
        std::cout << "Login failed. Incorrect username or password." << std::endl;
    }
}

int main()
{
    handleLogin();
   
}

// Function definitions
void displayMainMenu()
{
	
	#ifdef _WIN32 // Check if running on Windows
    system("cls");
    #else // Assume Unix-based system
        system("clear");
    #endif
	
	
    cout << "===== Main Menu =====\n";
    cout << "1. Room Management\n";
    cout << "2. Booking Management\n";
    cout << "3. Display Bill\n";
    cout << "4. Exit\n";
    
    int choice;
    do
    {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            displayRoomManagementMenu();
            
            break;
        case 2:
            displayBookingManagementMenu();
            
            break;
        case 3:
           displayBookings();
            break;
        case 4:
            // Exit program
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

}

void displayRoomManagementMenu()
{
	int choice;
	vector<Room> rooms;
	
	#ifdef _WIN32 // Check if running on Windows
        system("cls");
    #else // Assume Unix-based system
        system("clear");
    #endif
    cout << "===== Room Management =====\n";
    cout << "1. Add Room\n";
    cout << "2. View Rooms\n";
    cout << "3. Search room by ID\n";
    cout << "4. Go Back To Main Menu\n";
    
     
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addRoom(rooms);
                saveRoomsToFile(rooms);
                break;
            case 2:
                viewRooms();
                break;
            case 3:
                searchRoomById();
                break;
            case 4:
                cout << "Going Back to main menu...\n";
                
                displayMainMenu();
                
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

}

// Function to add rooms.
void addRoom(vector<Room>& rooms) {
    Room newRoom;
    cout << "Enter Room ID: ";
    cin >> newRoom.id;
    cout << "Enter Room Type(Do not Keep Spaces!): ";
    cin >> newRoom.type;
    cout << "Is the room available? (1 for available, 0 for not available): ";
    cin >> newRoom.available;
      cout << "Enter the Room Price in LKR";
    cin >> newRoom.price;
    rooms.push_back(newRoom); // Add the new room to the vector
    cout << "Room added successfully!\n";
}

// function to save rooms to data file (text file in this case)
void saveRoomsToFile(const vector<Room>& rooms) {
    ofstream outFile("rooms.txt");
    if (outFile.is_open()) {
        for (const auto& room : rooms) {
            outFile << room.id << "," << room.type << "," <<  room.available << "," <<room.price << endl;
        }
        outFile.close();
        cout << "Rooms saved to file successfully!\n";
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }
}

// Function to view rooms
void viewRooms() {
    ifstream inFile("rooms.txt");
    if (inFile.is_open()) {
        cout << "===== Rooms =====\n";
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, type, availability, priceStr;
            double price;
            getline(ss, id, ',');
            getline(ss, type, ',');
            getline(ss, availability,',');
             getline(ss, priceStr );
            cout << "Price string: " << priceStr << endl; // Debugging
            price = stod(priceStr); // Convert price string to double
            cout << "Room ID: " << id << ", Type: " << type << ", Price: LKR." << price << ", Availability: " << (availability == "1" ? "Available" : "Not Available") << endl;
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }
}

void searchRoomById() {
    string searchId;
    cout << "Enter Room ID to search: ";
    cin >> searchId;

    ifstream inFile("rooms.txt");
    if (inFile.is_open()) {
        bool found = false;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, type, availability, priceStr;
            double price;
            getline(ss, id, ',');
            getline(ss, type, ',');
            getline(ss, availability,',');
            cout << availability;
            getline(ss, priceStr);
            price = stod(priceStr); // Convert price string to double
            if (id == searchId) {
                found = true;
                cout << "Room found:\n";
                cout << "Room ID: " << id << ", Type: " << type << ", Price: $" << price << ", Availability: " << (availability == "1" ? "Available" : "Not Available") << endl;
                break;
            }
        }
        if (!found) {
            cout << "Room not found.\n";
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }
}


void displayBookingManagementMenu()
{
	
	vector<Room> rooms;
	
    cout << "===== Booking Management =====\n";
    cout << "1. Make a booking\n";
    cout << "2. Back To Main Menu\n";
    
    int choice;
     do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                cout << "Going Back to main menu...\n";
                
                displayMainMenu();
                
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    
    
}

void bookRoom() {
    viewRooms(); // Display available rooms
    string roomId;
    cout << "Enter the Room ID to book: ";
    cin >> roomId;

    // Prompt user to enter customer's name and cashier's name
    string customerName, cashierName;
    cout << "Enter customer's name: ";
    cin.ignore(); // Ignore previous newline character
    getline(cin, customerName);
    cout << "Enter cashier's name: ";
    getline(cin, cashierName);

    ifstream inFile("rooms.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, type, availability, priceStr;
            double price;
            getline(ss, id, ',');
            getline(ss, type, ',');
            getline(ss, availability, ',');
            getline(ss, priceStr);
            if (id == roomId && availability == "1") {
                double pricePerNight = stod(priceStr);
                int numNights;
                cout << "Enter number of nights to stay: ";
                cin >> numNights;
                double totalPrice = pricePerNight * numNights;
                // Get current time
                time_t now = time(0);
                tm *ltm = localtime(&now);
                // Format current time
                stringstream timeStream;
                timeStream << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
                string currentTime = timeStream.str();
                // Display booking details
                cout << "Booking details:\n";
                cout << "Room ID: " << id << ", Type: " << type << ", Price per Night: $" << pricePerNight << ", Number of Nights: " << numNights << endl;
                cout << "Total Price: $" << totalPrice << endl;
                cout << "Customer's Name: " << customerName << endl;
                cout << "Cashier's Name: " << cashierName << endl;
                cout << "Booking Time: " << currentTime << endl;
                // Save booking details to file
                ofstream outFile("bookings.txt", ios::app); // Append mode
                if (outFile.is_open()) {
                    outFile << "Booking details:\n";
                    outFile << "Room ID: " << id << ", Type: " << type << ", Price per Night: $" << pricePerNight << ", Number of Nights: " << numNights << endl;
                    outFile << "Total Price: $" << totalPrice << endl;
                    outFile << "Customer's Name: " << customerName << endl;
                    outFile << "Cashier's Name: " << cashierName << endl;
                    outFile << "Booking Time: " << currentTime << endl;
                    outFile << "----------------------------------------\n"; // Separator
                    outFile.close();
                    cout << "Booking details saved to file.\n";
                } else {
                    cout << "Error: Unable to open file for writing.\n";
                }
                // Update room availability in the file
                // We'll implement this part later
                return;
            }
        }
        cout << "Room not found or not available for booking.\n";
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }
}

// to diplay all the bills
void displayBookings() {
    ifstream inFile("bookings.txt");
    if (inFile.is_open()) {
        cout << "===== Bookings =====\n";
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }
}


