#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <string>
#include <iomanip>// For setting output precision
#include <fstream>
#include <sstream>
#include <set>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function declarations
void routeOptimisation();
void peakHourManagement();
void stationManagement();
void realTimeUpdates(const string& filename);
void predictiveMaintenance();
void passengerTicketingAndBillingWithFile();
void hygieneManagement();
void safetyManagement();
void yourBookingInfo();

void displayMenu() {
    cout << "===== MENU =====\n";
    cout << "1. Get the distances (Route Optimization)\n";
    cout << "2. Peak Hour Management\n";
    cout << "3. Station Management\n";
    cout << "4. Get the time (Real-Time Updates)\n";
    cout << "5. Predictive Maintenance\n";
    cout << "6. Passenger Ticketing and Billing\n";
    cout << "7. Hygiene Management\n";
    cout << "8. Safety Management(find nearest exit)\n";
    cout << "9. get your booking information\n";
    cout << "10. Exit\n";
    cout << "Enter your choice (1-9): ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                routeOptimisation();
                break;
            case 2:
                peakHourManagement();
                break;
            case 3:
                stationManagement();
                break;
            case 4:
                // Provide the filename for real-time updates
                realTimeUpdates("subway_graph.csv");
                break;
            case 5:
                predictiveMaintenance();
                break;
            case 6:
                passengerTicketingAndBillingWithFile();
                break;
            case 7:
                hygieneManagement();
                break;
            case 8:
                safetyManagement();
                break;
            case 9:
                yourBookingInfo();
                break;
            case 10:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}
// Global variables
unordered_map<int, vector<pair<int, int>>> graph;  // This will store the graph as an adjacency list
int nodes, edges;  // These variables store the number of nodes and edges
void routeOptimisation() {
typedef tuple<int, int, int> Edge; // For storing graph edges

// Function to save the graph to a file
void saveGraphToFile(const vector<Edge>& edges, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    file << "src,dest,weight\n"; // Write header
    for (const auto& edge : edges) {
        file << get<0>(edge) << "," << get<1>(edge) << "," << get<2>(edge) << "\n";
    }
    file.close();
    cout << "Graph saved to " << filename << endl;
}

// Function to load the graph from a file
vector<Edge> loadGraphFromFile(const string& filename) {
    ifstream file(filename);
    vector<Edge> edges;
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for reading." << endl;
        return edges;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        int src, dest, weight;
        char comma;
        ss >> src >> comma >> dest >> comma >> weight;
        edges.emplace_back(src, dest, weight);
    }
    file.close();
    return edges;
}

int main() {
    vector<Edge> edges = {
        {1, 2, 5}, {2, 3, 5}, {3, 4, 8}, {4, 5, 6}, {5, 6, 7}, {6, 7, 6},
        {7, 8, 8}, {8, 9, 8}, {9, 10, 8}, {10, 11, 3}, {11, 12, 4}, {12, 13, 7},
        {13, 14, 8}, {14, 15, 4}, {15, 16, 3}, {16, 17, 5}, {17, 18, 3}, {18, 19, 5},
        {19, 1, 7}, {20, 21, 8}, {21, 22, 8}, {22, 23, 8}, {23, 24, 9}, {24, 25, 4},
        {25, 26, 4}, {26, 27, 5}, {27, 28, 3}, {28, 29, 4}, {29, 30, 3}, {30, 31, 4},
        {31, 32, 5}, {32, 33, 5}, {33, 20, 5}, {34, 35, 8}, {35, 36, 3}, {36, 37, 8},
        {37, 38, 3}, {38, 39, 4}, {39, 40, 3}, {40, 41, 4}, {41, 42, 2}, {42, 34, 4},
        {43, 44, 6}, {44, 45, 6}, {45, 46, 6}, {46, 43, 6}, {43, 47, 4}, {44, 47, 4},
        {45, 47, 5}, {46, 47, 4}, {3, 21, 3}, {5, 22, 3}, {7, 23, 3}, {9, 26, 3},
        {11, 27, 3}, {13, 29, 3}, {15, 31, 5}, {17, 32, 3}, {19, 20, 4}, {20, 34, 2},
        {22, 35, 4}, {24, 37, 5}, {27, 38, 5}, {29, 38, 4}, {30, 39, 2}, {32, 41, 3},
        {34, 43, 4}, {35, 44, 3}, {37, 45, 2}, {39, 45, 2}, {41, 46, 3}
    };

    string filename = "subway_graph.csv";

    // Save the graph to the file
    saveGraphToFile(edges, filename);

    // Load the graph from the file
    vector<Edge> loadedEdges = loadGraphFromFile(filename);
    cout << "Loaded Graph Data:" << endl;
    for (const auto& edge : loadedEdges) {
        cout << get<0>(edge) << " -> " << get<1>(edge) << " (Weight: " << get<2>(edge) << ")" << endl;
    }

    return 0;
}
   

// Function to manage peak hour information
void peakHourManagement() {
    // Seed for randomization (casting time(0) to unsigned int)
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Vector to store station data as pairs of (zone code, station info)
    std::vector<std::pair<int, Station>> stations = {
        {1, {"Emerald Hills", "Residential + Tourism", {"7AM-9AM", "6PM-8PM"}}},
        {2, {"Heritage Quarters", "Government Offices", {"9AM-11AM", "4PM-6PM"}}},
        {3, {"Greenfield District", "Residential", {"6AM-8AM", "5PM-7PM"}}},
        {4, {"Eco Link Boulevard", "Commercial", {"8AM-10AM", "7PM-9PM"}}},
        {5, {"Serenity States", "Residential", {"7AM-9AM", "6PM-8PM"}}},
        {6, {"Prestige Enclave", "Residential", {"6AM-8AM", "5PM-7PM"}}},
        {7, {"Industrial Park", "Industrial", {"8AM-10AM", "3PM-5PM"}}},
        {8, {"Virtual Valley", "Office", {"9AM-11AM", "5PM-7PM"}}}
    };

    // Display available station options
    std::cout << "Available Zones:\n";
    for (const auto& station : stations) {
        std::cout << station.first << "-" << station.second.name << std::endl;
    }

    // User input
    int stationCode;
    std::cout << "Enter the zone code (1-8): ";
    std::cin >> stationCode;

    // Search for the station code in the vector
    bool found = false;
    for (const auto& station : stations) {
        if (station.first == stationCode) {
            const Station& selectedStation = station.second;

            // Randomize peak hour selection
            int randomIndex = std::rand() % selectedStation.peakHours.size();

            // Display station details and peak hours
            std::cout << "Station: " << selectedStation.name << std::endl;
            std::cout << "Type: " << selectedStation.type << std::endl;
            std::cout << "Peak Hours of subway station in the zone: " << selectedStation.peakHours[randomIndex] << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Invalid station code. Please try again." << std::endl;
    }
}
void stationManagement() {
    struct Station {
        std::string name;
        std::string manager;
        std::string emergencyPhone;
        std::string fireDepartment;
        std::string police;
        std::string sanitaryDepartment;
        std::string tollFreeHelpline;
    };

    srand(static_cast<unsigned>(time(0)));

    std::vector<Station> stations;

    auto generateRandomNames = [](int count) {
        std::vector<std::string> names = {
            "John Doe", "Jane Smith", "Alice Brown", "Bob Johnson", "Charlie Davis",
            "Emily Wilson", "Frank Moore", "Grace Taylor", "Henry Lee", "Isla Walker"};
        std::vector<std::string> randomNames;
        for (int i = 0; i < count; ++i) {
            randomNames.push_back(names[rand() % names.size()]);
        }
        return randomNames;
    };

    auto generatePhoneNumber = []() {
        std::string phone = "+91 ";
        for (int i = 0; i < 10; ++i) {
            phone += std::to_string(rand() % 10);
        }
        return phone;
    };

    std::vector<std::string> stationNames;
    for (int i = 1; i <= 47; ++i) {
        stationNames.push_back("Station " + std::to_string(i));
    }
    std::vector<std::string> managers = generateRandomNames(47);

    for (int i = 0; i < 47; ++i) {
        Station station;
        station.name = stationNames[i];
        station.manager = managers[i];
        station.emergencyPhone = generatePhoneNumber();
        station.fireDepartment = generatePhoneNumber();
        station.police = generatePhoneNumber();
        station.sanitaryDepartment = generatePhoneNumber();
        station.tollFreeHelpline = "1800-" + std::to_string(100000 + rand() % 900000);
        stations.push_back(station);
    }

    while (true) {
        std::string userInput;
        std::cout << "Enter the station number (e.g., 1 for Station 1) to get details or 'exit' to return to the menu: ";
        std::getline(std::cin, userInput);

        if (userInput == "exit") {
            break;
        }

        try {
            int stationNumber = std::stoi(userInput);
            if (stationNumber >= 1 && stationNumber <= 47) {
                const Station& station = stations[stationNumber - 1];
                std::cout << "Station Name: " << station.name << std::endl;
                std::cout << "Manager: " << station.manager << std::endl;
                std::cout << "Emergency Phone: " << station.emergencyPhone << std::endl;
                std::cout << "Fire Department: " << station.fireDepartment << std::endl;
                std::cout << "Police: " << station.police << std::endl;
                std::cout << "Sanitary Department: " << station.sanitaryDepartment << std::endl;
                std::cout << "Toll-Free Helpline: " << station.tollFreeHelpline << std::endl;
                std::cout << "-----------------------------\n";
            } else {
                std::cout << "Station not found. Please try again.\n";
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid station number or 'exit' to return to the menu.\n";
        }
    }
}
void preprocessBoyerMoore(const string& pattern, vector<int>& badCharTable) {
    size_t m = pattern.size();  // Use size_t for pattern size
    for (size_t i = 0; i < 256; ++i) {
        badCharTable[i] = -1;  // Initialize all bad character table values to -1
    }

    for (size_t i = 0; i < m; ++i) {
        badCharTable[static_cast<unsigned char>(pattern[i])] = static_cast<int>(i);  // Cast i to int
    }
}
void boyerMooreSearch(const string& text, const string& pattern) {
    size_t n = text.size();  // Change from int to size_t
    size_t m = pattern.size();  // Change from int to size_t

    vector<int> badCharTable(256, -1);  // Bad character table
    preprocessBoyerMoore(pattern, badCharTable);

    size_t s = 0; // Shift of the pattern with respect to text (size_t instead of int)
    while (s <= (n - m)) {
        size_t j = m - 1;  // Change from int to size_t

        // Keep reducing the index of the pattern from right to left as long as we have a match
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        // If the pattern is found
        if (j < 0) {
            cout << "Pattern found at index " << s << "\n";
            s += (s + m < n) ? m - badCharTable[static_cast<unsigned char>(text[s + m])] : 1;
        } else {
            s += max(size_t(1), j - badCharTable[static_cast<unsigned char>(text[s + j])]);
        }
    }
}
// Function to calculate time (in minutes) from distance and speed
double calculateTime(int distance, double speed) {
    double timeInHours = static_cast<double>(distance) / speed;
    return timeInHours * 60;  // Convert hours to minutes
}

void realTimeUpdates(const string& filename) {
    unordered_map<int, vector<pair<int, int>>> graph;  // Graph to store the stations and distances

    // Read the graph data from the CSV file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << "\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int src, dest, weight;

        // Assuming the CSV file format: src,dest,weight
        char comma;  // To ignore the commas in the CSV
        ss >> src >> comma >> dest >> comma >> weight;

        // Add the edges to the graph
        graph[src].push_back({dest, weight});
        graph[dest].push_back({src, weight});  // Assuming it's an undirected graph
    }

    file.close();

    int start, end;
    cout << "\n=== Real-Time Updates (Train Tracking) ===\n";
    cout << "Enter the current station ID: ";
    cin >> start;
    cout << "Enter the destination station ID: ";
    cin >> end;

    // Average speed of subway train in km/h
    double averageSpeed = 40.0;  // You can adjust this speed as needed

    // Dijkstra's algorithm to find the shortest path
    vector<int> dist(graph.size() + 1, INT_MAX);  // Distance array
    vector<int> parent(graph.size() + 1, -1);     // Parent array for path reconstruction
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDist > dist[currentNode]) continue;

        // Explore neighbors
        for (auto neighbor : graph[currentNode]) {
            int nextNode = neighbor.first;
            int edgeWeight = neighbor.second;

            if (dist[currentNode] + edgeWeight < dist[nextNode]) {
                dist[nextNode] = dist[currentNode] + edgeWeight;
                parent[nextNode] = currentNode;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    // Output the shortest distance
    cout << "Shortest distance from station " << start << " to station " << end << " is: " << dist[end] << " km.\n";

    // Calculate the estimated time based on the shortest path distance
    double timeInMinutes = calculateTime(dist[end], averageSpeed);
    cout << "Estimated time for the train to reach the destination: " << fixed << setprecision(2) << timeInMinutes << " minutes.\n";
}
long long fibonacci(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
// Structure to represent a train
struct Train {
    string name;
    int age;  // Age of the train in years
    bool needsMaintenance;  // Whether the train needs maintenance
    int birthYear;  // The year the train was born (manufactured)
};

// Function to get the current year using the system date
int getCurrentYear() {
    time_t t = time(0);  // Get current system time
    tm* currentTime = localtime(&t);  // Convert to local time
    return 1900 + currentTime->tm_year;  // tm_year gives years since 1900
}

// Function to calculate the next maintenance year
int calculateNextMaintenanceYear(int birthYear, int currentYear) {
    int nextMaintenanceYear = birthYear;

    // Calculate next maintenance year starting from birth year
    while (nextMaintenanceYear <= currentYear) {
        nextMaintenanceYear += 5;
    }

    return nextMaintenanceYear;
}

// Function to predict maintenance based on train age
void predictiveMaintenance() {
    cout << "\n=== Predictive Maintenance for Trains ===\n";

    // Hardcoded train data (train number, age, maintenance requirement, and birth year)
    vector<Train> trains = {
        {"Train 1", 17, false, 2008},
        {"Train 2", 10, false, 2015},
        {"Train 3", 15, false, 2010},
        {"Train 4", 4, false, 2021},
        {"Train 5", 7, false, 2018},  // Set this train to need maintenance
        {"Train 6", 13, false, 2012},
        {"Train 7", 5, false, 2020},
        {"Train 8", 8, false, 2017},
        {"Train 9", 16, false, 2009},
        {"Train 10", 11, false, 2014},
        {"Train 11", 2, false, 2023},
        {"Train 12", 20, false, 2003},
        {"Train 13", 18, false, 2007},
        {"Train 14", 3, false, 2022},
        {"Train 15", 9, false, 2016},
        {"Train 16", 14, false, 2011},
        {"Train 17", 6, false, 2019},
        {"Train 18", 19, false, 2006},
        {"Train 19", 12, false, 2013},
        {"Train 20", 1, false, 2024}
    };

    // Ask user for the train number
    int trainNumber;
    cout << "Enter the train number (1-20): ";
    cin >> trainNumber;

    // Validate the train number
    if (trainNumber < 1 || trainNumber > 20) {
        cout << "Invalid train number. Please enter a number between 1 and 20.\n";
        return;
    }

    // Get the current year
    int currentYear = getCurrentYear();

    // Display the details for the specified train
    Train selectedTrain = trains[trainNumber - 1];  // Adjust index (0-based index)

    // Calculate the next maintenance year (every 5 years from the birth year)
    int nextMaintenanceYear = calculateNextMaintenanceYear(selectedTrain.birthYear, currentYear);

    // For Train 5, set maintenance as needed, since its next maintenance year is before or equal to the current year
    if (trainNumber == 5 && nextMaintenanceYear <= currentYear) {
        selectedTrain.needsMaintenance = true;
    } else {
        selectedTrain.needsMaintenance = (nextMaintenanceYear <= currentYear);
    }

    // Display the train details
    cout << fixed << setprecision(0);  // Set precision for age
    cout << "\nTrain " << trainNumber << " Details:\n";
    cout << "Age: " << selectedTrain.age
         << " years, Present Year: " << currentYear
         << ", Birth Year: " << selectedTrain.birthYear
         << ", Last Maintenance Year: " << (nextMaintenanceYear - 5) // Last maintenance year
         << ", Maintenance Needed: "
         << (selectedTrain.needsMaintenance ? "Yes" : "No") << endl;

    cout << "Next Maintenance Year: " << nextMaintenanceYear << endl;
}
struct Ticket {
    string passengerName;
    int originStation;
    int destinationStation;
    float ticketPrice;
    string bookingTime;
};

vector<Ticket> tickets;  // This will store all the tickets

// Function to get the desktop path based on the operating system
string getDesktopPath() {
#ifdef _WIN32
    return string(getenv("USERPROFILE")) + "\\Desktop\\bookings.txt";
#else
    return string(getenv("HOME")) + "/Desktop/bookings.txt";
#endif
}

// Function to save booking details to a file on the desktop
void saveBookingToFile(const string& name, const string& time, int start, int end, double price) {
    string desktopPath = getDesktopPath();

    ofstream file(desktopPath, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << "Name: " << name << ", Time: " << time
             << ", Start Station: " << start << ", Destination Station: " << end
             << ", Price: " << fixed << setprecision(2) << price << " GBP\n";
        file.close();
        cout << "Booking saved successfully to: " << desktopPath << "\n";
    } else {
        cout << "Error opening the file to save booking.\n";
    }
}

// Function for passenger ticketing and billing
void passengerTicketingAndBillingWithFile() {
    struct Ticket {
    string name;
    int startNode;
    int endNode;
    string time;
    int trainNumber;
    float amount;
};

// Function to save a ticket to a file
void saveTicketToFile(const Ticket& ticket, const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing ticket data." << endl;
        return;
    }
    file << ticket.name << "," << ticket.startNode << "," << ticket.endNode << ","
         << ticket.time << "," << ticket.trainNumber << "," << ticket.amount << "\n";
    file.close();
}

// Function to load all tickets from a file
vector<Ticket> loadTicketsFromFile(const string& filename) {
    ifstream file(filename);
    vector<Ticket> loadedTickets;
    if (!file.is_open()) {
        cerr << "Error: Unable to open bookings file for reading." << endl;
        return loadedTickets;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, time;
        int startNode, endNode, trainNumber;
        float amount;
        char comma;

        getline(ss, name, ',');
        ss >> startNode >> comma >> endNode >> comma;
        getline(ss, time, ',');
        ss >> trainNumber >> comma >> amount;

        loadedTickets.push_back({name, startNode, endNode, time, trainNumber, amount});
    }
    file.close();
    return loadedTickets;
}

// Function to display all tickets
void displayTickets(const vector<Ticket>& tickets) {
    cout << "\n=== Booked Tickets ===\n";
    for (const auto& ticket : tickets) {
        cout << "Name: " << ticket.name
             << "\nStarting Station: " << ticket.startNode
             << "\nDestination Station: " << ticket.endNode
             << "\nTime: " << ticket.time
             << "\nTrain Number: " << ticket.trainNumber
             << "\nAmount: " << ticket.amount << "\n\n";
    }
}

int main() {
    // Define the file name to be used in the current working directory
    string filename = "bookings.txt";

    // Example of saving a ticket
    Ticket ticket1 = {"John Doe", 1, 5, "10:30 AM", 12345, 25.50};
    saveTicketToFile(ticket1, filename);

    // Load tickets from the file and display them
    vector<Ticket> tickets = loadTicketsFromFile(filename);
    displayTickets(tickets);

    cout << "Tickets saved to: " << filename << " in the current directory." << endl;

    return 0;
}
// Function to handle hygiene management complaints
void hygieneManagement() {
    // Get the desktop file path
    std::string filePath;
#ifdef _WIN32
    filePath = getenv("USERPROFILE");
    filePath += "\\Desktop\\HygieneComplaints.txt";
#else
    filePath = getenv("HOME");
    filePath += "/Desktop/HygieneComplaints.txt";
#endif

    // Collect user inputs
    int stationNumber;
    std::cout << "Enter the subway station number: ";
    std::cin >> stationNumber;

    std::vector<std::string> complaintOptions = {
        "Overflowing Trash Cans",
        "Dirty Restrooms",
        "Pest Sightings",
        "Spillage in Train"
    };

    std::cout << "Select a complaint type:" << std::endl;
    for (size_t i = 0; i < complaintOptions.size(); ++i) {
        std::cout << i + 1 << ". " << complaintOptions[i] << std::endl;
    }

    int complaintChoice;
    std::cout << "Enter the number corresponding to your complaint: ";
    std::cin >> complaintChoice;

    // Validate input
    if (complaintChoice < 1 || complaintChoice > static_cast<int>(complaintOptions.size())) {
        std::cerr << "Invalid choice. Exiting." << std::endl;
        return;
    }

    // Save the complaint to the file
    std::ofstream complaintFile(filePath, std::ios::app);
    if (!complaintFile) {
        std::cerr << "Error: Could not open the file for writing." << std::endl;
        return;
    }

    complaintFile << "Station Number: " << stationNumber
                  << ", Complaint: " << complaintOptions[complaintChoice - 1] << std::endl;
    complaintFile.close();

    std::cout << "Complaint logged successfully!" << std::endl;
}

// Function to merge two subarrays
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Function to perform merge sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}
// Edge representation
struct Edge {
    string src;
    string dest;
    int weight;
};

// Graph representation
class Graph {
public:
    unordered_map<string, vector<pair<string, int>>> adjList;

    // Add edge to the graph
    void addEdge(const string& src, const string& dest, int weight) {
        adjList[src].emplace_back(dest, weight);
        adjList[dest].emplace_back(src, weight); // Assuming undirected graph
    }

    // Bellman-Ford algorithm
    unordered_map<string, int> bellmanFord(const string& start) {
        unordered_map<string, int> dist;

        // Initialize distances with infinity
        for (const auto& pair : adjList) {
            dist[pair.first] = numeric_limits<int>::max();
        }
        dist[start] = 0;

        // Relax edges
        for (size_t i = 1; i < adjList.size(); ++i) {
            for (const auto& pair : adjList) {
                string u = pair.first;
                for (const auto& neighbor : adjList[u]) {
                    string v = neighbor.first;
                    int weight = neighbor.second;
                    if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (const auto& pair : adjList) {
            string u = pair.first;
            for (const auto& neighbor : adjList[u]) {
                string v = neighbor.first;
                int weight = neighbor.second;
                if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    cout << "Graph contains a negative weight cycle!" << endl;
                    return {};
                }
            }
        }

        return dist;
    }
};

void safetyManagement() {
struct Edge {
    string src;
    string dest;
    int weight;
};

// Function to get the desktop path dynamically
string getDesktopPath() {
#ifdef _WIN32
    const char* userProfile = getenv("USERPROFILE");
    if (userProfile == nullptr) {
        cerr << "Error: Unable to get the USERPROFILE environment variable." << endl;
        exit(EXIT_FAILURE);
    }
    return string(userProfile) + "\\Desktop\\eme_exit.txt";
#elif _APPLE_
    const char* home = getenv("HOME");
    if (home == nullptr) {
        cerr << "Error: Unable to get the HOME environment variable." << endl;
        exit(EXIT_FAILURE);
    }
    return string(home) + "/Desktop/eme_exit.txt";
#else
    cerr << "Error: Unsupported platform!" << endl;
    exit(EXIT_FAILURE);
#endif
}

int main() {
    // List of edges in the graph
    vector<Edge> edges = {
        {"1", "exit1", 1},
        {"exit1", "2", 3},
        {"2", "3", 2},
        {"3", "4", 3},
        {"4", "5", 2},
        {"1", "6", 3},
        {"6", "7", 2},
        {"7", "8", 2},
        {"2", "8", 3},
        {"8", "9", 3},
        {"9", "exit2", 2},
        {"exit2", "10", 3},
        {"4", "10", 4},
        {"10", "11", 3},
        {"5", "11", 4}
    };

    // Get the desktop path dynamically
    string filePath = getDesktopPath();

    // Open file to write
    ofstream outFile(filePath);

    if (outFile.is_open()) {
        // Write the edges to the file
        for (const auto& edge : edges) {
            outFile << "Src: " << edge.src << ", Dest: " << edge.dest << ", Weight: " << edge.weight << endl;
        }

        cout << "Graph saved to " << filePath << endl;
    } else {
        cout << "Failed to open file." << endl;
    }

    outFile.close();
    return 0;


}
    
void yourBookingInfo()
{
    struct Ticket
    {
        string name;
        int startNode;
        int endNode;
        string time;
        float amount;
    };

    // Function to get the desktop path dynamically
    auto getDesktopPath = []() -> string {
        #ifdef _WIN32
            const char* home = getenv("USERPROFILE");
        #else
            const char* home = getenv("HOME");
        #endif
        if (home == nullptr)
        {
            cerr << "Error: Unable to get the home directory." << endl;
            exit(EXIT_FAILURE);
        }
        return string(home) + "/Desktop/bookings.txt";
    };

    auto kmpPasswordValidation = [](const std::string& text, const std::string& pattern) -> bool {
        int n = static_cast<int>(text.size());
        int m = static_cast<int>(pattern.size());
        std::vector<int> lps(m, 0);

        // Preprocessing pattern for LPS array
        for (int i = 1, len = 0; i < m;)
        {
            if (pattern[i] == pattern[len])
            {
                lps[i++] = ++len;
            }
            else if (len > 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i++] = 0;
            }
        }

        // Searching pattern in the text
        for (int i = 0, j = 0; i < n;)
        {
            if (pattern[j] == text[i])
            {
                i++; j++;
            }
            if (j == m)
            {
                return true;
            }
            else if (i < n && pattern[j] != text[i])
            {
                j ? j = lps[j - 1] : i++;
            }
        }
        return false;
    };

    // Function to load tickets from the file
    auto loadTicketsFromFile = [](const string& filename) -> vector<Ticket> {
        ifstream file(filename);
        vector<Ticket> loadedTickets;

        if (!file.is_open())
        {
            cerr << "Error: Unable to open bookings file for reading." << endl;
            return loadedTickets;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, time;
            int startNode, endNode;
            float amount;

            // Parsing ticket data
            size_t pos;
            pos = line.find("Name: ");
            if (pos == string::npos) continue;
            line = line.substr(pos + 6);
            pos = line.find(", Time: ");
            name = line.substr(0, pos);
            line = line.substr(pos + 8);

            pos = line.find(", Start Station: ");
            time = line.substr(0, pos);
            line = line.substr(pos + 17);

            pos = line.find(", Destination Station: ");
            startNode = stoi(line.substr(0, pos));
            line = line.substr(pos + 23);

            pos = line.find(", Price: ");
            endNode = stoi(line.substr(0, pos));
            line = line.substr(pos + 9);

            amount = stof(line);

            loadedTickets.push_back({name, startNode, endNode, time, amount});
        }
        file.close();
        return loadedTickets;
    };

    string filename = getDesktopPath();
    while (true)
    {
        // Password validation
        string password;
        cout << "Enter the password (or type 'exit' to quit): ";
        cin >> password;

        if (password == "exit")
        {
            cout << "Exiting booking info retrieval.\n";
            return;
        }

        if (!kmpPasswordValidation(password, "password"))
        {
            cout << "Invalid password! Try again.\n";
            continue;
        }

        // Load tickets and search by name
        vector<Ticket> tickets = loadTicketsFromFile(filename);
        string userName;
        cout << "Enter your name: ";
        cin >> userName;

        cout << "\n=== Your Bookings ===\n";
        bool found = false;
        for (const auto& ticket : tickets)
        {
            if (ticket.name == userName)
            {
                found = true;
                cout << "Name: " << ticket.name
                     << "\nTime: " << ticket.time
                     << "\nStarting Station: " << ticket.startNode
                     << "\nDestination Station: " << ticket.endNode
                     << "\nPrice: " << ticket.amount << " rupee\n\n";
            }
        }
        if (!found)
        {
            cout << "No bookings found for the name \"" << userName << "\".\n";
        }

        // Ask if the user wants to continue or return to the menu
        string choice;
        cout << "Do you want to search for another booking? (yes/no): ";
        cin >> choice;

        if (choice != "yes")
        {
            cout << "Returning to the main menu.\n";
            return;
        }
    }
}
