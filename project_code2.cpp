#include <bits/stdc++.h>
using namespace std;

// ==================== PATIENT NODE (LINKED LIST) ====================
struct PatientNode {
    int id;
    string name;
    int age;
    string disease;
    string contact;
    int priority;
    PatientNode* next;
    
    PatientNode(int i, string n, int a, string d, string c, int p) 
        : id(i), name(n), age(a), disease(d), contact(c), priority(p), next(nullptr) {}
};

// ==================== DOCTOR BST NODE ====================
struct DoctorNode {
    int id;
    string name;
    string specialization;
    string availability;
    DoctorNode* left;
    DoctorNode* right;
    
    DoctorNode(int i, string n, string s, string a) 
        : id(i), name(n), specialization(s), availability(a), left(nullptr), right(nullptr) {}
};

// ==================== APPOINTMENT STRUCTURE ====================
struct Appointment {
    int apptId;
    int patientId;
    int doctorId;
    string date;
    string time;
    
    Appointment(int a, int p, int d, string dt, string t) 
        : apptId(a), patientId(p), doctorId(d), date(dt), time(t) {}
};

// ==================== MEDICAL RECORD (STACK) ====================
struct MedicalRecord {
    int patientId;
    string date;
    string diagnosis;
    string treatment;
    
    MedicalRecord(int p, string d, string diag, string t) 
        : patientId(p), date(d), diagnosis(diag), treatment(t) {}
};

// ==================== DEPARTMENT GRAPH NODE ====================
struct Department {
    string name;
    vector<pair<Department*, int>> connections; // Connected departments with distance
    
    Department(string n) : name(n) {}
};

// ==================== PRIORITY QUEUE COMPARATOR ====================
struct ComparePriority {
    bool operator()(PatientNode* p1, PatientNode* p2) {
        return p1->priority > p2->priority;
    }
};

// ==================== LINKED LIST CLASS ====================
class PatientLinkedList {
private:
    PatientNode* head;
    
public:
    PatientLinkedList() : head(nullptr) {}
    
    void insert(int id, string name, int age, string disease, string contact, int priority) {
        PatientNode* newNode = new PatientNode(id, name, age, disease, contact, priority);
        if(!head) {
            head = newNode;
        } else {
            PatientNode* temp = head;
            while(temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }
    
    void display() {
        if(!head) {
            cout << "No patients in the list.\n";
            return;
        }
        PatientNode* temp = head;
        while(temp) {
            cout << "\nID: " << temp->id << " | Name: " << temp->name 
                 << " | Age: " << temp->age << " | Disease: " << temp->disease
                 << "\nContact: " << temp->contact << " | Priority: " << temp->priority << endl;
            temp = temp->next;
        }
    }
    
    PatientNode* search(int id) {
        PatientNode* temp = head;
        while(temp) {
            if(temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }
    
    void deletePatient(int id) {
        if(!head) return;
        
        if(head->id == id) {
            PatientNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Patient deleted successfully!\n";
            return;
        }
        
        PatientNode* temp = head;
        while(temp->next && temp->next->id != id) {
            temp = temp->next;
        }
        
        if(temp->next) {
            PatientNode* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Patient deleted successfully!\n";
        } else {
            cout << "Patient not found!\n";
        }
    }
    
    ~PatientLinkedList() {
        while(head) {
            PatientNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ==================== BINARY SEARCH TREE (DOCTORS) ====================
class DoctorBST {
private:
    DoctorNode* root;
    
    DoctorNode* insertHelper(DoctorNode* node, int id, string name, string spec, string avail) {
        if(!node) return new DoctorNode(id, name, spec, avail);
        
        if(id < node->id)
            node->left = insertHelper(node->left, id, name, spec, avail);
        else
            node->right = insertHelper(node->right, id, name, spec, avail);
        
        return node;
    }
    
    void inorderHelper(DoctorNode* node) {
        if(!node) return;
        inorderHelper(node->left);
        cout << "\nID: " << node->id << " | Name: " << node->name 
             << "\nSpecialization: " << node->specialization 
             << " | Availability: " << node->availability << endl;
        inorderHelper(node->right);
    }
    
    DoctorNode* searchHelper(DoctorNode* node, int id) {
        if(!node || node->id == id) return node;
        if(id < node->id) return searchHelper(node->left, id);
        return searchHelper(node->right, id);
    }
    
    void destroyTree(DoctorNode* node) {
        if(node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
public:
    DoctorBST() : root(nullptr) {}
    
    void insert(int id, string name, string spec, string avail) {
        root = insertHelper(root, id, name, spec, avail);
    }
    
    void display() {
        cout << "\n========== DOCTORS (BST In-order Traversal) ==========\n";
        if(!root) {
            cout << "No doctors available.\n";
            return;
        }
        inorderHelper(root);
    }
    
    DoctorNode* search(int id) {
        return searchHelper(root, id);
    }
    
    ~DoctorBST() {
        destroyTree(root);
    }
};

// ==================== HOSPITAL GRAPH (DEPARTMENTS) ====================
class HospitalGraph {
private:
    vector<Department*> departments;
    
public:
    void addDepartment(string name) {
        departments.push_back(new Department(name));
    }
    
    void addConnection(int dept1, int dept2, int distance) {
        if(dept1 < departments.size() && dept2 < departments.size()) {
            departments[dept1]->connections.push_back({departments[dept2], distance});
            departments[dept2]->connections.push_back({departments[dept1], distance});
        }
    }
    
    void displayGraph() {
        cout << "\n========== HOSPITAL DEPARTMENT LAYOUT ==========\n";
        for(int i = 0; i < departments.size(); i++) {
            cout << "\n" << departments[i]->name << " connected to:\n";
            for(auto conn : departments[i]->connections) {
                cout << "  -> " << conn.first->name << " (Distance: " << conn.second << "m)\n";
            }
        }
    }
    
    ~HospitalGraph() {
        for(auto dept : departments) delete dept;
    }
};

// ==================== MAIN HOSPITAL MANAGEMENT SYSTEM ====================
class HospitalManagementSystem {
private:
    PatientLinkedList patientList;                             // Linked List
    DoctorBST doctorTree;                                      // Binary Search Tree
    priority_queue<PatientNode*, vector<PatientNode*>, ComparePriority> emergencyQueue; // Priority Queue
    queue<int> opdQueue;                                       // Queue
    stack<MedicalRecord*> medicalHistory;                      // Stack
    unordered_map<int, vector<Appointment*>> appointmentHash;  // Hash Table
    HospitalGraph hospitalLayout;                              // Graph
    
    int patientCounter;
    int doctorCounter;
    int appointmentCounter;

public:
    HospitalManagementSystem() : patientCounter(1), doctorCounter(1), appointmentCounter(1) {
        initializeDoctors();
        initializeHospitalLayout();
    }
    
    ~HospitalManagementSystem() {
        for(auto& pair : appointmentHash) {
            for(auto a : pair.second) delete a;
        }
        while(!medicalHistory.empty()) {
            delete medicalHistory.top();
            medicalHistory.pop();
        }
    }
    
    void initializeDoctors() {
        doctorTree.insert(doctorCounter++, "Dr. Smith", "Cardiologist", "Mon-Fri 9AM-5PM");
        doctorTree.insert(doctorCounter++, "Dr. Johnson", "Neurologist", "Mon-Wed 10AM-4PM");
        doctorTree.insert(doctorCounter++, "Dr. Williams", "Orthopedic", "Tue-Sat 8AM-3PM");
        doctorTree.insert(doctorCounter++, "Dr. Brown", "General Physician", "Mon-Sat 9AM-6PM");
        doctorTree.insert(doctorCounter++, "Dr. Davis", "Pediatrician", "Mon-Fri 9AM-4PM");
    }
    
    void initializeHospitalLayout() {
        hospitalLayout.addDepartment("Emergency");
        hospitalLayout.addDepartment("OPD");
        hospitalLayout.addDepartment("ICU");
        hospitalLayout.addDepartment("Surgery");
        hospitalLayout.addDepartment("Pharmacy");
        hospitalLayout.addDepartment("Lab");
        
        hospitalLayout.addConnection(0, 1, 50);  // Emergency - OPD
        hospitalLayout.addConnection(0, 2, 30);  // Emergency - ICU
        hospitalLayout.addConnection(1, 3, 70);  // OPD - Surgery
        hospitalLayout.addConnection(2, 3, 40);  // ICU - Surgery
        hospitalLayout.addConnection(1, 4, 60);  // OPD - Pharmacy
        hospitalLayout.addConnection(1, 5, 45);  // OPD - Lab
    }
    
    // ========== LINKED LIST OPERATIONS ==========
    void addPatient() {
        string name, disease, contact;
        int age, priority;
        
        cout << "\n--- Add New Patient (Linked List) ---\n";
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Disease: ";
        getline(cin, disease);
        cout << "Enter Contact: ";
        getline(cin, contact);
        cout << "Enter Priority (1=Critical, 2=Serious, 3=Normal): ";
        cin >> priority;
        
        patientList.insert(patientCounter, name, age, disease, contact, priority);
        
        PatientNode* p = patientList.search(patientCounter);
        if(priority == 1) {
            emergencyQueue.push(p);
            cout << "\n** EMERGENCY PATIENT ADDED TO PRIORITY QUEUE **\n";
        } else {
            opdQueue.push(patientCounter);
        }
        
        cout << "\nPatient Added Successfully! Patient ID: " << patientCounter << endl;
        patientCounter++;
    }
    
    void displayAllPatients() {
        cout << "\n========== ALL PATIENTS (Linked List) ==========\n";
        patientList.display();
    }
    
    void searchPatient() {
        int id;
        cout << "\nEnter Patient ID to search: ";
        cin >> id;
        
        PatientNode* p = patientList.search(id);
        if(p) {
            cout << "\n--- Patient Found (Linked List) ---\n";
            cout << "ID: " << p->id << " | Name: " << p->name 
                 << " | Age: " << p->age << " | Disease: " << p->disease
                 << "\nContact: " << p->contact << " | Priority: " << p->priority << endl;
        } else {
            cout << "Patient not found!\n";
        }
    }
    
    void deletePatient() {
        int id;
        cout << "\nEnter Patient ID to delete: ";
        cin >> id;
        patientList.deletePatient(id);
    }
    
    // ========== BST OPERATIONS ==========
    void displayDoctors() {
        doctorTree.display();
    }
    
    void searchDoctor() {
        int id;
        cout << "\nEnter Doctor ID to search: ";
        cin >> id;
        
        DoctorNode* d = doctorTree.search(id);
        if(d) {
            cout << "\n--- Doctor Found (BST) ---\n";
            cout << "ID: " << d->id << " | Name: " << d->name 
                 << "\nSpecialization: " << d->specialization 
                 << " | Availability: " << d->availability << endl;
        } else {
            cout << "Doctor not found!\n";
        }
    }
    
    // ========== HASH TABLE OPERATIONS ==========
    void bookAppointment() {
        doctorTree.display();
        
        int patId, docId;
        string date, time;
        
        cout << "\n--- Book Appointment (Hash Table) ---\n";
        cout << "Enter Patient ID: ";
        cin >> patId;
        cout << "Enter Doctor ID: ";
        cin >> docId;
        cin.ignore();
        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin, date);
        cout << "Enter Time (HH:MM): ";
        getline(cin, time);
        
        Appointment* appt = new Appointment(appointmentCounter++, patId, docId, date, time);
        appointmentHash[docId].push_back(appt);
        
        cout << "\nAppointment Booked! Appointment ID: " << appt->apptId << endl;
    }
    
    void displayAppointmentsByDoctor() {
        int docId;
        cout << "\nEnter Doctor ID to view appointments: ";
        cin >> docId;
        
        if(appointmentHash.find(docId) == appointmentHash.end() || appointmentHash[docId].empty()) {
            cout << "No appointments for this doctor.\n";
            return;
        }
        
        cout << "\n========== APPOINTMENTS (Hash Table) ==========\n";
        for(auto appt : appointmentHash[docId]) {
            cout << "\nAppointment ID: " << appt->apptId 
                 << " | Patient ID: " << appt->patientId
                 << " | Date: " << appt->date << " | Time: " << appt->time << endl;
        }
    }
    
    // ========== PRIORITY QUEUE OPERATIONS ==========
    void processEmergency() {
        cout << "\n--- Emergency Queue (Priority Queue) ---\n";
        if(emergencyQueue.empty()) {
            cout << "No emergency patients!\n";
            return;
        }
        
        PatientNode* p = emergencyQueue.top();
        emergencyQueue.pop();
        
        cout << "\nProcessing EMERGENCY Patient:\n";
        cout << "ID: " << p->id << " | Name: " << p->name 
             << " | Age: " << p->age << " | Disease: " << p->disease << endl;
        cout << "\n** Patient being treated immediately! **\n";
    }
    
    // ========== QUEUE OPERATIONS ==========
    void processOPD() {
        cout << "\n--- OPD Queue (Queue) ---\n";
        if(opdQueue.empty()) {
            cout << "No patients in OPD queue!\n";
            return;
        }
        
        int patId = opdQueue.front();
        opdQueue.pop();
        
        PatientNode* p = patientList.search(patId);
        if(p) {
            cout << "\nProcessing OPD Patient:\n";
            cout << "ID: " << p->id << " | Name: " << p->name 
                 << " | Disease: " << p->disease << endl;
        }
    }
    
    // ========== STACK OPERATIONS ==========
    void addMedicalRecord() {
        int patId;
        string date, diagnosis, treatment;
        
        cout << "\n--- Add Medical Record (Stack) ---\n";
        cout << "Enter Patient ID: ";
        cin >> patId;
        cin.ignore();
        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin, date);
        cout << "Enter Diagnosis: ";
        getline(cin, diagnosis);
        cout << "Enter Treatment: ";
        getline(cin, treatment);
        
        MedicalRecord* record = new MedicalRecord(patId, date, diagnosis, treatment);
        medicalHistory.push(record);
        
        cout << "\nMedical Record Added Successfully!\n";
    }
    
    void displayRecentRecords() {
        cout << "\n========== RECENT MEDICAL RECORDS (Stack - LIFO) ==========\n";
        if(medicalHistory.empty()) {
            cout << "No medical records available.\n";
            return;
        }
        
        stack<MedicalRecord*> temp;
        int count = 0;
        
        while(!medicalHistory.empty() && count < 5) {
            MedicalRecord* record = medicalHistory.top();
            medicalHistory.pop();
            temp.push(record);
            
            cout << "\nPatient ID: " << record->patientId 
                 << " | Date: " << record->date
                 << "\nDiagnosis: " << record->diagnosis 
                 << "\nTreatment: " << record->treatment << endl;
            count++;
        }
        
        while(!temp.empty()) {
            medicalHistory.push(temp.top());
            temp.pop();
        }
    }
    
    // ========== GRAPH OPERATIONS ==========
    void displayHospitalLayout() {
        hospitalLayout.displayGraph();
    }
};

// ==================== MAIN FUNCTION ====================
int main() {
    HospitalManagementSystem hms;
    int choice;
    
    while(true) {
        cout << "\n\n=============================================\n";
        cout << "      HOSPITAL MANAGEMENT SYSTEM\n";
        cout << "=============================================\n";
        cout << "1.  Add Patient (Linked List)\n";
        cout << "2.  Display All Patients (Linked List)\n";
        cout << "3.  Search Patient (Linked List)\n";
        cout << "4.  Delete Patient (Linked List)\n";
        cout << "5.  Display Doctors (BST)\n";
        cout << "6.  Search Doctor (BST)\n";
        cout << "7.  Book Appointment (Hash Table)\n";
        cout << "8.  Display Appointments by Doctor (Hash)\n";
        cout << "9.  Process Emergency Patient (Priority Queue)\n";
        cout << "10. Process OPD Patient (Queue)\n";
        cout << "11. Add Medical Record (Stack)\n";
        cout << "12. Display Recent Medical Records (Stack)\n";
        cout << "13. Display Hospital Layout (Graph)\n";
        cout << "14. Exit\n";
        cout << "=============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: hms.addPatient(); break;
            case 2: hms.displayAllPatients(); break;
            case 3: hms.searchPatient(); break;
            case 4: hms.deletePatient(); break;
            case 5: hms.displayDoctors(); break;
            case 6: hms.searchDoctor(); break;
            case 7: hms.bookAppointment(); break;
            case 8: hms.displayAppointmentsByDoctor(); break;
            case 9: hms.processEmergency(); break;
            case 10: hms.processOPD(); break;
            case 11: hms.addMedicalRecord(); break;
            case 12: hms.displayRecentRecords(); break;
            case 13: hms.displayHospitalLayout(); break;
            case 14: 
                cout << "\nThank you for using Hospital Management System!\n";
                return 0;
            default: 
                cout << "\nInvalid choice! Please try again.\n";
        }
    }
    
    return 0;
}