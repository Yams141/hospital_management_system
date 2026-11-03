
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Abstract Base Class
class Person {
protected:
    int id, age;
    string name;

public:
    Person(int i, string n, int a) {
        id = i;
        name = n;
        age = a;
    }

    virtual void display() const = 0;

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    virtual ~Person() {}
};

// Patient Class - Inheritance
class Patient : public Person {
private:
    string disease;

public:
    Patient(int i, string n, int a, string d)
        : Person(i, n, a) {
        disease = d;
    }

    void display() const override {
        cout << left << setw(8) << id
             << setw(20) << name
             << setw(8) << age
             << disease << endl;
    }
};

// Doctor Class - Inheritance
class Doctor : public Person {
private:
    string specialization;
    double fee;

public:
    Doctor(int i, string n, int a,
           string s, double f)
        : Person(i, n, a) {
        specialization = s;
        fee = f;
    }

    void display() const override {
        cout << left << setw(8) << id
             << setw(20) << name
             << setw(8) << age
             << setw(20) << specialization
             << fee << endl;
    }

    double getFee() const {
        return fee;
    }
};

// Appointment Class
class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;

public:
    Appointment(int a, int p, int d, string dt) {
        appointmentId = a;
        patientId = p;
        doctorId = d;
        date = dt;
    }

    void display() const {
        cout << "Appointment ID: " << appointmentId
             << " | Patient ID: " << patientId
             << " | Doctor ID: " << doctorId
             << " | Date: " << date << endl;
    }
};

// Hospital Management Class
class Hospital {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

    int nextPatientId = 1;
    int nextDoctorId = 1;
    int nextAppointmentId = 1;

    Patient* findPatient(int id) {
        for (auto &p : patients) {
            if (p.getId() == id)
                return &p;
        }
        return nullptr;
    }

    Doctor* findDoctor(int id) {
        for (auto &d : doctors) {
            if (d.getId() == id)
                return &d;
        }
        return nullptr;
    }

public:
    void addPatient() {
        string name, disease;
        int age;

        cout << "\nEnter patient name: ";
        getline(cin, name);

        cout << "Enter age: ";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter disease: ";
        getline(cin, disease);

        patients.emplace_back(
            nextPatientId++, name, age, disease
        );

        cout << "\nPatient registered successfully!\n";
    }

    void viewPatients() const {
        if (patients.empty()) {
            cout << "\nNo patients registered.\n";
            return;
        }

        cout << "\n--- PATIENT RECORDS ---\n";
        cout << left << setw(8) << "ID"
             << setw(20) << "Name"
             << setw(8) << "Age"
             << "Disease\n";

        for (const auto &p : patients)
            p.display();
    }

    void addDoctor() {
        string name, specialization;
        int age;
        double fee;

        cout << "\nEnter doctor name: ";
        getline(cin, name);

        cout << "Enter age: ";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter specialization: ";
        getline(cin, specialization);

        cout << "Enter consultation fee: ";
        cin >> fee;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        doctors.emplace_back(
            nextDoctorId++, name, age,
            specialization, fee
        );

        cout << "\nDoctor added successfully!\n";
    }

    void viewDoctors() const {
        if (doctors.empty()) {
            cout << "\nNo doctors available.\n";
            return;
        }

        cout << "\n--- DOCTOR RECORDS ---\n";
        cout << left << setw(8) << "ID"
             << setw(20) << "Name"
             << setw(8) << "Age"
             << setw(20) << "Specialization"
             << "Fee\n";

        for (const auto &d : doctors)
            d.display();
    }

    void bookAppointment() {
        int pId, dId;
        string date;

        if (patients.empty() || doctors.empty()) {
            cout << "\nPlease register a patient "
                 << "and add a doctor first.\n";
            return;
        }

        viewPatients();
        cout << "\nEnter patient ID: ";
        cin >> pId;

        if (findPatient(pId) == nullptr) {
            cout << "Invalid patient ID.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        viewDoctors();
        cout << "\nEnter doctor ID: ";
        cin >> dId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (findDoctor(dId) == nullptr) {
            cout << "Invalid doctor ID.\n";
            return;
        }

        cout << "Enter appointment date (DD-MM-YYYY): ";
        getline(cin, date);

        appointments.emplace_back(
            nextAppointmentId++, pId, dId, date
        );

        cout << "\nAppointment booked successfully!\n";
    }

    void viewAppointments() const {
        if (appointments.empty()) {
            cout << "\nNo appointments found.\n";
            return;
        }

        cout << "\n--- APPOINTMENT DETAILS ---\n";

        for (const auto &a : appointments)
            a.display();
    }

    void generateBill() {
        int pId, dId;

        if (patients.empty() || doctors.empty()) {
            cout << "\nPatient and doctor records are required.\n";
            return;
        }

        viewPatients();
        cout << "\nEnter patient ID: ";
        cin >> pId;

        Patient* p = findPatient(pId);

        if (p == nullptr) {
            cout << "Invalid patient ID.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        viewDoctors();
        cout << "\nEnter doctor ID: ";
        cin >> dId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Doctor* d = findDoctor(dId);

        if (d == nullptr) {
            cout << "Invalid doctor ID.\n";
            return;
        }

        cout << "\n========== HOSPITAL BILL ==========\n";
        cout << "Patient Name : " << p->getName() << endl;
        cout << "Patient ID   : " << p->getId() << endl;
        cout << "Doctor Name  : " << d->getName() << endl;
        cout << "Consultation Fee: Rs. "
             << fixed << setprecision(2)
             << d->getFee() << endl;
        cout << "==================================\n";
        cout << "Total Amount : Rs. "
             << d->getFee() << endl;
        cout << "==================================\n";
    }
};

// Main Function
int main() {
    Hospital hospital;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "      HOSPITAL MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Register New Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Add Doctor\n";
        cout << "4. View All Doctors\n";
        cout << "5. Book Appointment\n";
        cout << "6. View Appointments\n";
        cout << "7. Generate Patient Bill\n";
        cout << "8. Exit\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                hospital.addPatient();
                break;

            case 2:
                hospital.viewPatients();
                break;

            case 3:
                hospital.addDoctor();
                break;

            case 4:
                hospital.viewDoctors();
                break;

            case 5:
                hospital.bookAppointment();
                break;

            case 6:
                hospital.viewAppointments();
                break;

            case 7:
                hospital.generateBill();
                break;

            case 8:
                cout << "\nThank you for using "
                     << "Hospital Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
