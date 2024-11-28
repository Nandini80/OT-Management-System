#include <bits/stdc++.h>
using namespace std;

class DiskScheduling {
public:
    void CSCAN(vector<int>& requests, int head, int disk_size) 
    {
        sort(requests.begin(), requests.end());
        auto it = find(requests.begin(), requests.end(), head);
        int pos = distance(requests.begin(), it);
        int total_seek_time = 0;

        for (int i = pos + 1; i < requests.size(); i++) {
            total_seek_time += abs(requests[i] - head);
            head = requests[i];
        }

        total_seek_time += abs(disk_size - 1 - head);
        head = 0;
        total_seek_time += abs(requests[0] - head);
        head = requests[0];

        for (int i = 0; i < pos; i++) {
            total_seek_time += abs(requests[i] - head);
            head = requests[i];
        }

        cout << "Total Seek Time: " << total_seek_time << endl;
        cout << "Average Seek Time: " << (double)total_seek_time / requests.size() << endl;
    }
};

class Surgery {
public:
    int id;
    string patientName;
    string doctorName;
    string specialization;
    int priority;
    int duration;
    string status;
    int assignedTime;
};

class Theatre {
public:
    int id;
    string name;
    bool isOccupied;

    Theatre(int id, const string& name) : id(id), name(name), isOccupied(false) {}
};

// Compare function for priority queue
class ComparePriority {
public:
    bool operator()(const Surgery& a, const Surgery& b) {
        if (a.priority == b.priority)
            return a.assignedTime > b.assignedTime;
        return a.priority < b.priority;
    }
};

class OTManagementSystem {
private:
    priority_queue<Surgery, vector<Surgery>, ComparePriority> surgeryQueue;
    vector<Theatre> theatres;
    vector<Surgery> completedSurgeries;
    unordered_map<int, string> userRoles;
    vector<int> surgeryQueueIds;
    int head_position = 0;
    int disk_size = 200;

public:
    OTManagementSystem(int numTheatres) {
        for (int i = 1; i <= numTheatres; ++i) {
            theatres.emplace_back(i, "Theatre " + to_string(i));
        }
    }

    void login() {
        int userId;
        cout << "Enter your User ID: ";
        cin >> userId;
    
        if (userRoles.find(userId) != userRoles.end()) {
            cout << "Welcome back, User ID " << userId << "!\n";
        } else {
            userRoles[userId] = "Employee"; 
            cout << "User ID " << userId << " has been added as Employee.\n";
        }
    }


    void addSurgery() {
        Surgery newSurgery;
        cout << "\nEnter Surgery Details:\n";
        cout << "ID: ";
        cin >> newSurgery.id;
        cin.ignore();
        cout << "Patient Name: ";
        getline(cin, newSurgery.patientName);
        cout << "Doctor Name: ";
        getline(cin, newSurgery.doctorName);
        cout << "Specialization: ";
        getline(cin, newSurgery.specialization);
        cout << "Priority (1-10, 10 = Highest): ";
        cin >> newSurgery.priority;
        cout << "Estimated Duration (hours): ";
        cin >> newSurgery.duration;
        newSurgery.status = "Pending";
        newSurgery.assignedTime = 0;

        surgeryQueue.push(newSurgery);
        surgeryQueueIds.push_back(newSurgery.id);
        cout << "Surgery for " << newSurgery.patientName << " has been added to the queue.\n";
    }

    void assignSurgery() {
        if (surgeryQueue.empty()) {
            cout << "No surgeries in the queue.\n";
            return;
        }

        for (auto& theatre : theatres) {
            if (!theatre.isOccupied) {
                Surgery currentSurgery = surgeryQueue.top();
                surgeryQueue.pop();
                theatre.isOccupied = true;

                cout << "\nAssigning Surgery ID: " << currentSurgery.id << " to " << theatre.name << "\n";
                completeSurgery(theatre, currentSurgery);
                return;
            }
        }

        cout << "All theatres are occupied. Surgery will be rescheduled.\n";
    }

    void completeSurgery(Theatre& theatre, Surgery& surgery) {
        cout << "Surgery in " << theatre.name << " completed successfully!\n";
        theatre.isOccupied = false;
        surgery.status = "Completed";
        completedSurgeries.push_back(surgery);
    }

    void displayQueue() {
        if (surgeryQueue.empty()) {
            cout << "No surgeries in the queue.\n";
            return;
        }

        priority_queue<Surgery, vector<Surgery>, ComparePriority> tempQueue = surgeryQueue;
        cout << "\nCurrent Surgery Queue:\n";
        while (!tempQueue.empty()) {
            Surgery s = tempQueue.top();
            tempQueue.pop();
            cout << "ID: " << s.id
                 << ", Patient: " << s.patientName
                 << ", Doctor: " << s.doctorName
                 << ", Specialization: " << s.specialization
                 << ", Priority: " << s.priority
                 << ", Status: " << s.status
                 << ", Duration: " << s.duration << " hours\n";
        }
    }

    void displayTheatreStatus() {
        cout << "\nTheatre Status:\n";
        for (auto& theatre : theatres) {
            cout << theatre.name << ": " << (theatre.isOccupied ? "Occupied" : "Available") << "\n";
        }
    }

    void viewHistory() {
        if (completedSurgeries.empty()) {
            cout << "No completed surgeries.\n";
            return;
        }

        cout << "\nCompleted Surgery History:\n";
        for (const auto& surgery : completedSurgeries) {
            cout << "ID: " << surgery.id
                 << ", Patient: " << surgery.patientName
                 << ", Doctor: " << surgery.doctorName
                 << ", Specialization: " << surgery.specialization
                 << ", Duration: " << surgery.duration << " mins\n";
        }
    }

    void manageDiskRequests() {
        DiskScheduling ds;
        cout << "\n--- Disk Scheduling Operations ---\n";
        ds.CSCAN(surgeryQueueIds, head_position, disk_size);
    }

    void menu() {
        int choice;
        while (true) {
            cout << "------------------------------\n";
            cout << "---- OT Management System ----\n";
            cout << "------------------------------\n";
            cout << "1. Login\n";
            cout << "2. Add Surgery\n";
            cout << "3. Assign Surgery\n";
            cout << "4. Display Surgery Queue\n";
            cout << "5. Display Theatre Status\n";
            cout << "6. View Completed Surgeries\n";
            cout << "7. Manage Disk Requests (C-SCAN)\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    addSurgery();
                    break;
                case 3:
                    assignSurgery();
                    break;
                case 4:
                    displayQueue();
                    break;
                case 5:
                    displayTheatreStatus();
                    break;
                case 6:
                    viewHistory();
                    break;
                case 7:
                    manageDiskRequests();
                    break;
                case 8:
                    cout << "Exiting system.\nThank You for Visiting Us\n";
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main() {
    OTManagementSystem obj(3);
    obj.menu();
    return 0;
}