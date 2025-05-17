#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

class Hospital {
    char address[100];
public:
    static int capacity;

    Hospital() {
        strcpy(address, "4 Park Lane");
    }
};

// Initialize static member
int Hospital::capacity = 500;

class Info {
protected:
    char name[50];
    int age;

public:
    Info() {
        strcpy(name, "N/A");
        age = 0;
    }

    void get() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
    }

    void show() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Patient : public Info {
    int id;
    vector<string> medicalHistory;

public:
    Patient() : id(0) {}

    void get() {
        Info::get();
        cout << "Enter Patient ID: ";
        cin >> id;
        if (Hospital::capacity > 0) {
            cout << "New Patient Capacity: " << --Hospital::capacity << endl;
        } else {
            cout << "Hospital is at full capacity!" << endl;
        }
    }

    void show() const {
        Info::show();
        cout << "Patient ID: " << id << endl;
        cout << "Medical History: ";
        for (const auto& record : medicalHistory) {
            cout << record << "; ";
        }
        cout << endl;
    }

    void addMedicalHistory(const string& record) {
        medicalHistory.push_back(record);
    }

    int retid() const {
        return id;
    }
};

class Employee : public Info {
    int id;
    int type;
    float salary;

public:
    Employee() : id(0), type(0), salary(0) {}

    void get() {
        Info::get();
        cout << "Enter Employee ID: ";
        cin >> id;
        cout << "[1] Doctor\n[2] Admin\n[3] Housekeeping\n[4] Maintenance\n";
        cout << "Enter Employee Type (1/2/3/4): ";
        cin >> type;
    }

    void calculateSalary(int hours) {
        switch (type) {
            case 1: salary = 5000 * hours; break;
            case 2: salary = 2000 * hours; break;
            case 3: salary = 1000 * hours; break;
            case 4: salary = 500 * hours; break;
            default: cout << "Unexpected Type" << endl; salary = 0;
        }
    }

    void show() const {
        Info::show();
        cout << "Employee ID: " << id << ", Type: " << type << ", Salary: " << salary << endl;
    }
};

class Appointment {
    int patientId;
    int doctorId;
    string date;
    string time;

public:
    Appointment(int pId, int dId, const string& d, const string& t) 
        : patientId(pId), doctorId(dId), date(d), time(t) {}

    void show() const {
        cout << "Appointment: Patient ID: " << patientId 
             << ", Doctor ID: " << doctorId 
             << ", Date: " << date 
             << ", Time: " << time << endl;
    }
};

class Bill {
    int fixed;
    int variable;
    int days;

public:
    Bill() : fixed(0), variable(0), days(0) {}

    // Constructor that takes parameters
    Bill(int f, int v, int d) : fixed(f), variable(v), days(d) {}

    void get() {
        cout << "Enter Fixed Charges: ";
        cin >> fixed;
        cout << "Enter Variable Charges: ";
        cin >> variable;
        cout << "Enter Number of Days: ";
        cin >> days;
        fixed *= days;
        variable *= days;
    }

    void show() const {
        cout << "Total Bill: Fixed: Rs. " << fixed << ", Variable: Rs. " << variable << endl;
    }

    Bill operator+(const Bill& b) const {
        return Bill(fixed + b.fixed, variable + b.variable, 0);
    }
};

class Doctor : public Employee {
    bool available;

public:
    Doctor() : available(true) {}

    void setAvailability(bool status) {
        available = status;
    }

    bool isAvailable() const {
        return available;
    }

    void show() const {
        Employee::show();
        cout << "Availability: " << (available ? "Available" : "Unavailable") << endl;
    }
};

void welcomeMessage(const string& message) {
    cout << "********** " << message << " **********" << endl << endl;
}

int main() {
    welcomeMessage("Welcome to XYZ Hospital");

    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    int choice;

    do {
        cout << "[1] Add Patient\n[2] View Patients\n[3] Add Doctor\n[4] View Doctors\n[5] Schedule Appointment\n[0] Exit\nYour Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Patient p;
                p.get();
                patients.push_back(p);
                break;
            }
            case 2: {
                for (const auto& p : patients) {
                    p.show();
                }
                break;
            }
            case 3: {
                Doctor d;
                d.get();
                doctors.push_back(d);
                break;
            }
            case 4: {
                for (const auto& d : doctors) {
                    d.show();
                }
                break;
            }
            case 5: {
                int patientId, doctorId;
                string date, time;
                cout << "Enter Patient ID: ";
                cin >> patientId;
                cout << "Enter Doctor ID: ";
                cin >> doctorId;
                cout << "Enter Appointment Date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter Appointment Time (HH:MM): ";
                cin >> time;

                appointments.emplace_back(patientId, doctorId, date, time);
                break;
            }
            case 0:
                break;
            default:
                cout << "Wrong Choice...\n";
        }
    } while (choice != 0);

    // Display all appointments
    cout << "\nScheduled Appointments:\n";
    for (const auto& appointment : appointments) {
        appointment.show();
    }

    return 0;

}
