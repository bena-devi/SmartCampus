#include <iostream>
#include <vector>

#include <string>
#include <climits>
using namespace std;


//Class Users
class User {
public:
    string name;
    string email;
    string password;

    User() {}

    User(string n, string e, string p) {
        name = n;
        email = e;
        password = p;
    }
};

//Class Booking
class Booking {
public:
    string userName;
    string userEmail;
    string date;
    int startHour;
    int endHour;

    Booking() {}

    Booking(string uName, string uEmail, string d, int s, int e) {
        userName = uName;
        userEmail = uEmail;
        date = d;
        startHour = s;
        endHour = e;
    }
};


//Class Resource
class Resource {
public:
    int id;
    string name;
    string type;
    vector<Booking> bookings;

    Resource() {}

    Resource(int i, string n, string t) {
        id = i;
        name = n;
        type = t;
    }

    bool isAvailable(string date, int startHour, int endHour) {
        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].date == date) {
                if (!(endHour <= bookings[i].startHour || startHour >= bookings[i].endHour)) {
                    return false;
                }
            }
        }
        return true;
    }


    //Show Conflict
    void showConflictingBookings(string date, int startHour, int endHour) {
        bool found = false;

        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].date == date) {
                if (!(endHour <= bookings[i].startHour || startHour >= bookings[i].endHour)) {
                    if (!found) {
                        cout << "\nThis resource is already booked in this time slot:\n";
                        found = true;
                    }

                    cout << "Booked By: " << bookings[i].userName
                         << " | Email: " << bookings[i].userEmail
                         << " | Date: " << bookings[i].date
                         << " | Time: " << bookings[i].startHour << ":00 - "
                         << bookings[i].endHour << ":00\n";
                }
            }
        }
    }

    void addBooking(string userName, string userEmail, string date, int startHour, int endHour) {
        bookings.push_back(Booking(userName, userEmail, date, startHour, endHour));
    }



    //Show Booking
    void showBookings() {
        cout << "\nBookings for " << name << ":\n";

        if (bookings.size() == 0) {
            cout << "No bookings found.\n";
            return;
        }

        for (int i = 0; i < bookings.size(); i++) {
            cout << "User: " << bookings[i].userName
                 << " | Email: " << bookings[i].userEmail
                 << " | Date: " << bookings[i].date
                 << " | Time: " << bookings[i].startHour << ":00 - "
                 << bookings[i].endHour << ":00\n";
        }
    }


    //Cancel Booking
    void cancelBooking(string userName, string userEmail, string date, int startHour, int endHour) {
        bool found = false;

        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].userName == userName &&
                bookings[i].userEmail == userEmail &&
                bookings[i].date == date &&
                bookings[i].startHour == startHour &&
                bookings[i].endHour == endHour) {

                bookings.erase(bookings.begin() + i);
                cout << "Booking cancelled successfully.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Booking not found.\n";
        }
    }
};


//Class SmartCampus
class SmartCampus {
private:
    vector<User> users;
    vector<Resource> resources;
    vector<vector<int>> cost;
    int loggedInUserIndex;

public:
    SmartCampus() {
        loggedInUserIndex = -1;
    }

    void addResource(int id, string name, string type) {
        resources.push_back(Resource(id, name, type));

        int newSize = resources.size();
        cost.resize(newSize);

        for (int i = 0; i < newSize; i++) {
            cost[i].resize(newSize, INT_MAX);
        }

        for (int i = 0; i < newSize; i++) {
            cost[i][i] = 0;
        }
    }

    void addConnection(int u, int v, int w) {
        if (u >= 0 && v >= 0 && u < resources.size() && v < resources.size()) {
            cost[u][v] = w;
            cost[v][u] = w;
        }
    }


    //Add Register User
    void registerUser() {
        string name, email, password;

        cin.ignore();
        cout << "\nEnter Name: ";
        getline(cin, name);

        cout << "Enter Email: ";
        getline(cin, email);

       
        for (int i = 0; i < users.size(); i++) {
            if (users[i].email == email) {
                cout << "This email is already registered.\n";
                return;
            }
        }

        cout << "Enter Password: ";
        getline(cin, password);

        users.push_back(User(name, email, password));
        cout << "Registration successful.\n";
    }



    //Login User
    void loginUser() {
        string email, password;

        cin.ignore();
        cout << "\nEnter Email: ";
        getline(cin, email);

        cout << "Enter Password: ";
        getline(cin, password);

        for (int i = 0; i < users.size(); i++) {
            if (users[i].email == email && users[i].password == password) {
                loggedInUserIndex = i;
                cout << "Login successful. Welcome, " << users[i].name << "!\n";
                return;
            }
        }

        cout << "Invalid email or password.\n";
    }

        

    //Logout User
    void logoutUser() {
        if (loggedInUserIndex == -1) {
            cout << "No user is logged in.\n";
        } else {
            cout << "Logout successful.\n";
            loggedInUserIndex = -1;
        }
    }

    bool isUserLoggedIn() {
        return loggedInUserIndex != -1;
    }

    string getLoggedInUserName() {
        if (loggedInUserIndex != -1) {
            return users[loggedInUserIndex].name;
        }
        return "";
    }

    string getLoggedInUserEmail() {
        if (loggedInUserIndex != -1) {
            return users[loggedInUserIndex].email;
        }
        return "";
    }

    void showResources() {
        cout << "\n--- Available Resources ---\n";

        if (resources.size() == 0) {
            cout << "No resources available.\n";
            return;
        }

        for (int i = 0; i < resources.size(); i++) {
            cout << "ID: " << resources[i].id
                 << " | Name: " << resources[i].name
                 << " | Type: " << resources[i].type << endl;
        }
    }

    //Book Resources
    void bookResource() {
        if (!isUserLoggedIn()) {
            cout << "Please login first.\n";
            return;
        }

        int id, startHour, endHour;
        string date;

        showResources();

        cout << "\nEnter Resource ID: ";
        cin >> id;

        if (id < 0 || id >= resources.size()) {
            cout << "Invalid Resource ID.\n";
            return;
        }

        cin.ignore();
        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Enter Start Hour (0-23): ";
        cin >> startHour;

        cout << "Enter End Hour (1-24): ";
        cin >> endHour;

        if (startHour < 0 || endHour > 24 || startHour >= endHour) {
            cout << "Invalid time slot.\n";
            return;
        }

        if (resources[id].isAvailable(date, startHour, endHour)) {
            resources[id].addBooking(getLoggedInUserName(), getLoggedInUserEmail(), date, startHour, endHour);
            cout << "Booking successful for " << resources[id].name << ".\n";
        } else {
            cout << "Booking failed. Resource already booked.\n";
            resources[id].showConflictingBookings(date, startHour, endHour);
        }
    }


    //Check Availability
    void checkAvailability() {
        int id, startHour, endHour;
        string date;

        showResources();

        cout << "\nEnter Resource ID: ";
        cin >> id;

        if (id < 0 || id >= resources.size()) {
            cout << "Invalid Resource ID.\n";
            return;
        }

        cin.ignore();
        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Enter Start Hour (0-23): ";
        cin >> startHour;

        cout << "Enter End Hour (1-24): ";
        cin >> endHour;

        if (startHour < 0 || endHour > 24 || startHour >= endHour) {
            cout << "Invalid time slot.\n";
            return;
        }

        if (resources[id].isAvailable(date, startHour, endHour)) {
            cout << resources[id].name << " is available.\n";
        } else {
            cout << resources[id].name << " is already booked.\n";
            resources[id].showConflictingBookings(date, startHour, endHour);
        }
    }


    //Cancel Resources 
    void cancelResourceBooking() {
        if (!isUserLoggedIn()) {
            cout << "Please login first.\n";
            return;
        }

        int id, startHour, endHour;
        string date;

        showResources();

        cout << "\nEnter Resource ID: ";
        cin >> id;

        if (id < 0 || id >= resources.size()) {
            cout << "Invalid Resource ID.\n";
            return;
        }

        cin.ignore();
        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Enter Start Hour (0-23): ";
        cin >> startHour;

        cout << "Enter End Hour (1-24): ";
        cin >> endHour;

        resources[id].cancelBooking(getLoggedInUserName(), getLoggedInUserEmail(), date, startHour, endHour);
    }

    void showAllBookings() {
        for (int i = 0; i < resources.size(); i++) {
            resources[i].showBookings();
        }
    }


    // Prim's algorithms used for classroom and labs between connection 

    void primMST() {
        int n = resources.size();

        if (n == 0) {
            cout << "No resources available for MST.\n";
            return;
        }

        vector<int> key(n, INT_MAX);
        vector<int> parent(n, -1);
        vector<bool> mstSet(n, false);

        key[0] = 0;

        for (int count = 0; count < n - 1; count++) {
            int minKey = INT_MAX;
            int u = -1;

            for (int v = 0; v < n; v++) {
                if (!mstSet[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            if (u == -1) {
                cout << "Graph is not connected.\n";
                return;
            }

            mstSet[u] = true;

            for (int v = 0; v < n; v++) {
                if (cost[u][v] != INT_MAX && !mstSet[v] && cost[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = cost[u][v];
                }
            }
        }

        cout << "\n--- MST of Resources ---\n";
        int totalCost = 0;

        for (int i = 1; i < n; i++) {
            if (parent[i] != -1) {
                cout << resources[parent[i]].name
                     << " <--> "
                     << resources[i].name
                     << " | Cost: "
                     << cost[parent[i]][i] << endl;

                totalCost += cost[parent[i]][i];
            }
        }

        cout << "Total Minimum Cost: " << totalCost << endl;
    }
};



//Main 
int main() {
    SmartCampus campus;
    int choice;

    campus.addResource(1, "Lab 2", "Lab");
    campus.addResource(2, "Lab 3", "Lab");
    campus.addResource(3, "Lab 4", "Lab");
    campus.addResource(4, "Lab 5", "Lab");
    campus.addResource(5, "Lab 6", "Lab");
    campus.addResource(6, "Lab 7", "Lab");
    campus.addResource(7, "Lab 8", "Lab");
    campus.addResource(8, "Lab 9", "Lab");
    campus.addResource(9, "Classroom 2", "Classroom");
    campus.addResource(11, "Classroom 3", "Classroom");
    campus.addResource(12, "Classroom 4", "Classroom");
    campus.addResource(13, "Classroom 5", "Classroom");
    campus.addResource(14, "Classroom 6", "Classroom");
    campus.addResource(15, "Classroom 7", "Classroom");
    campus.addResource(16, "Classroom 8", "Classroom");

    //Campus Add Connection
    campus.addConnection(0, 1, 4);
    campus.addConnection(0, 2, 6);
    campus.addConnection(0, 3, 3);
    campus.addConnection(1, 2, 5);
    campus.addConnection(1, 3, 7);
    campus.addConnection(2, 3, 2);

    do {
        cout << "\n====== SMART CAMPUS RESOURCE MANAGEMENT SYSTEM ======\n";
        cout << "1. Register User\n";
        cout << "2. Login User\n";
        cout << "3. Show Resources\n";
        cout << "4. Book Resource\n";
        cout << "5. Check Availability\n";
        cout << "6. Cancel Booking\n";
        cout << "7. Show All Bookings\n";
        cout << "8. Show MST\n";
        cout << "9. Logout User\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                campus.registerUser();
                break;

            case 2:
                campus.loginUser();
                break;

            case 3:
                campus.showResources();
                break;

            case 4:
                campus.bookResource();
                break;

            case 5:
                campus.checkAvailability();
                break;

            case 6:
                campus.cancelResourceBooking();
                break;

            case 7:
                campus.showAllBookings();
                break;

            case 8:
                campus.primMST();
                break;

            case 9:
                campus.logoutUser();
                break;

            case 10:
                cout << "Program exited.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 10);

    return 0;
}