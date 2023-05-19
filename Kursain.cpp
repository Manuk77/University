#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "KursainUtil.h"
using namespace std;


// Computer class
class Computer {

public:

    Computer(): procName("HP"), ram(8), hdd(512), video("GTX 1650 SUPER"){}

    Computer(const string& procName, const int& ram, const int& hdd, const string& video) {
        this->procName = procName;
        this->ram = ram;
        this->hdd = hdd;
        this->video = video;
    }

    Computer(const Computer& comps): procName(comps.getProcName()),
            ram(comps.getRam()), hdd(comps.getHdd()), video(comps.getVideo()){};

    ~Computer() = default;


    // setters and getters

    void setProcName(string procName) {this->procName = procName;}
    string getProcName() const { return procName; }

    void setRam(int ram){this->ram = ram;}
    int getRam() const { return ram; }

    void setHdd(int hdd){this->hdd = hdd;}
    int getHdd() const { return hdd; }

    void setVideo(string video){this->video = video;}
    string getVideo() const { return video; }


    bool match(const string& attr, const string& value, const bool& equal) const {
        if (attr == "prodName") {
            return (equal && procName == value) || (!equal && procName != value);
        }
        else if (attr == "ram") {
            return (equal && ram == stoi(value)) || (!equal && ram != stoi(value));
        }
        else if (attr == "hdd") {
            return (equal && hdd == stoi(value)) || (!equal && hdd != stoi(value));
        }
        else if (attr == "video") {
            return (equal && video == value) || (!equal && video != value);
        }
        else {
            return false;
        }
    }

    string toString() const{
        return "{Product Name = " + procName + "} {RAM = " + to_string(ram) +"GB } { HDD = " +
        to_string(hdd) + "GB } { VIDEO = " + video + " }";
    }


private:
    string procName;
    int ram;
    int hdd;
    string video;
};

// Laboratory class
class Laboratory {
public:

    Laboratory() : name("HPCompany"), roomNumber(101) {}

    Laboratory(string& name, int& roomNumber) : name(name), roomNumber(roomNumber) {}

    Laboratory(const Laboratory& labs): name(labs.getName()), roomNumber(labs.getRoomNumber()){}

    ~Laboratory() = default;

    bool match(const string& attr, const string& value, const bool equal) const {
        if (attr == "name")
            return (equal && name == value) || (!equal && name != value);
        if (attr == "roomNumber")
            return (equal && roomNumber == stoi(value)) || (!equal && roomNumber != stoi(value));
    }

    // setters and getters

    void setName(const string& name) { this->name = name; }
    string getName() const { return name; }
    void setRoomNumber(const int& roomNumber){ this->roomNumber = roomNumber;}
    int getRoomNumber() const { return roomNumber; }

    string toString() const {
        return "{ NAME = " + name + "} { ROOM NUMBER = " + to_string(roomNumber) + " }";
    }

private:
    string name;
    int roomNumber;
};

// Database
class Database {

public:


    Database(const Database& other) {
        computers = other.computers;
        labs = other.labs;
    }

    Database(const vector<Computer>& computers, const vector<Laboratory>& labs){
        this->computers = computers;
        this->labs = labs;
    }


    

    vector<Computer> selectComputer(const string& attr, const string& value, const bool& equal)  {
        vector<Computer> result;
        computers = loadComputer();
        for (int i = 0; i < computers.size(); ++i) {
            if (computers[i].match(attr, value, equal)) {
                result.push_back(computers[i]);
            }
        }
        return result;
    }

    vector<Laboratory> selectLaboratory(const string& attr, const string& value, const bool equal) {
        vector<Laboratory> labs;
        this->labs = loadLaboratory();
        for ( int i = 0; i < this->labs.size(); ++i) {
            if (this->labs[i].match(attr, value, equal))
                labs.push_back(this->labs[i]);
        }
        return labs;
    }

    void deleteComputer(const string& attr, const string& value, const bool equal) {
        for (auto it = computers.begin(); it != computers.end(); ) {
            if (it->match(attr, value, equal)) {
                it = computers.erase(it);
            } else {
                ++it;
            }
        }
        saveComputer();
    }

    void deleteLaboratory(const string& attr, const string& value, const bool equal) {
        for(auto it = labs.begin(); it != labs.end();) {
            if (it->match(attr, value, equal))
                it = labs.erase(it);
            else
                ++it;
        }
        saveLaboratory();
    }

    void addComputer(const Computer& comp) {
        computers.push_back(comp);
    }

    void addLaboratory(const Laboratory& labs) {
        this->labs.push_back(labs);
    }



    void saveComputer() const{
        ofstream ofs(computersPath);
       // ofs << "ProdName,RAM,HDD,Video" << endl;
        for(Computer comp: computers) {
            ofs << comp.getProcName() << ",";
            ofs << comp.getRam() << ",";
            ofs << comp.getHdd() << ",";
            ofs << comp.getVideo() << endl;
        }
        ofs.close();
    }

    const vector<Computer>& loadComputer() {
        computers.clear();
        ifstream ifs(computersPath);
        if (!ifs.is_open()) {
            cout << "Error opening file" << endl;
        }

        string line;
        while (getline(ifs, line))
        {
            // Use a stringstream to split the line into fields
            stringstream ss(line);
            string field;
            string procName, video;
            int ram, hdd;


            getline(ss, procName, ',');
            ss >> ram;
            ss.ignore();
            ss >> hdd;
            ss.ignore();
            getline(ss, video, ',');

            // Add the computer object to the vector of computers
            computers.push_back(Computer(procName, ram, hdd, video));


        }
        ifs.close();
        return computers;
    }

    void saveLaboratory() const {
        ofstream ofs(laboratoryPath);
        for(Laboratory laboratory: labs) {
            ofs << laboratory.getName()<< ",";
            ofs << laboratory.getRoomNumber();
        }
        ofs.close();
    }

    const vector<Laboratory>& loadLaboratory()  {
        labs.clear();
        ifstream ifs(laboratoryPath);
        string line;
        vector<Laboratory> laboratory;
        while (getline(ifs, line)) {
            stringstream ss(line);
            string name; int roomNumber;
            getline(ss, name, ',');
            ss >> roomNumber;
            labs.push_back(Laboratory(name, roomNumber));
        }
        ifs.close();
        return labs;
    }


    const vector<Computer>& getComputers() const {
            return computers;
    }

    const vector<Laboratory>& getLaboratory() const {
        return labs;
    }

    void printComputer(const vector<Computer>& computers) const {
        for (const Computer& c: computers) {
            cout<<c.toString()<<endl;
        }
    }
    void printLaboratory(const vector<Laboratory>& labs)const{
        for (const Laboratory& lab: labs) {
            cout<<lab.toString()<<endl;
        }
    }
    void printLaboratory()const{
        for (const Laboratory& lab: labs) {
            cout<<lab.toString()<<endl;
        }
    }



private:
     string computersPath = "/home/manuk/CLionProjects/Kursain/repository/computers";
     string laboratoryPath = "/home/manuk/CLionProjects/Kursain/repository/labaratory";
     vector<Computer> computers;
     vector<Laboratory> labs;
};

class CRUD {
public:


    CRUD(Database &db) : db(db){}

    CRUD(const CRUD& other) : db(other.db) {}
    ~CRUD() = default;


    void insertCompany() {
        string procName;
        int ram;
        int hdd;
        string video;
        cout<<"ENTER PRODUCT NAME -> "; cin>>procName;
        cout<<"ENTER RAM SIZE -> "; cin>>ram;
        cout<<"ENTER HDD SIZE -> "; cin>>hdd;
        cout<<"ENTER VIDEO -> "; cin>>video;
        db.addComputer(*new Computer(procName, ram, hdd, video));
    }

    void insertLaboratory() {
        string name;
        int roomNumber;
        cout<<"ENTER LABORATORY NAME -> "; cin>>name;
        cout<<"ENTER LABORATORY ROOM NUMBER ->"; cin>>roomNumber;
        db.addLaboratory(*new Laboratory(name, roomNumber));
    }

    void deleteComputer(){
        string attribute;
        string value;
        bool equal;
        cout<<"ENTER ATTRIBUTE NAME -> "; cin>>attribute;
        cout<<"ENTER VALUE NAME -> "; cin>>value;
        cout<<"ENTER TRUE OR FALSE -> "; cin>>equal;
        db.deleteComputer(attribute,value, equal);
    }

    void deleteLaboratory(){
        string attribute;
        string value;
        bool equal;
        cout<<"ENTER ATTRIBUTE NAME -> "; cin>>attribute;
        cout<<"ENTER VALUE NAME -> "; cin>>value;
        cout<<"ENTER TRUE OR FALSE -> "; cin>>equal;
        db.deleteLaboratory(attribute, value, equal);
    }

    void selectComputer(){
        string prodName = "prodName";
        string ram = "ram";
        string hdd = "hdd";
        string video = "video";
        string value;
        bool equal = true;
        switch (enterCompProdName()) {
            case 1:
                cout<<"SELECT COMPANY * WHERE " + prodName + " = "; cin>>value;
                printComp(db.selectComputer(prodName, value, equal));
                break;
            case 2:
                cout<<"SELECT COMPANY * WHERE " + ram + " = "; cin>>value;
                printComp(db.selectComputer(ram, value, equal));
                break;
            case 3:
                cout<<"SELECT COMPANY * WHERE " + hdd + " = "; cin>>value;
                printComp(db.selectComputer(hdd, value, equal));
                break;
            case 4:
                cout<<"SELECT COMPANY * WHERE " + video + " = "; cin>>value;
                printComp(db.selectComputer(video, value, equal));
                break;
            default:
                cout<<"ENTERED CHOICE DOSE NOT EXIST"<<endl;
        }


    }

    void selectLaboratory() {
        string name = "name";
        string roomNumber = "roomNumber";
        string value;
        bool equal = true;
        switch (enterLabProdName()) {
            case 1:
                cout << "SELECT LABORATORY * WHERE " + name + "= "; cin >> value;
                printLab(db.selectLaboratory(name, value, equal));
                break;
            case 2:
                cout << "SELECT LABORATORY * WHERE " + roomNumber + "= "; cin >> value;
                printLab(db.selectLaboratory(roomNumber, value, equal));
                break;
            default:
                cout<<"ENTERED CHOICE DOSE NOT EXIST"<<endl;
        }
    }

    void printComp(const vector<Computer>& comp) const {
        if (comp.size() < 1) {
            cout<<"VECTOR IS EMPTY, INSERT SOME ELEMENTS"<<endl;
            return;
        }
        for(Computer c: comp){
            cout<<c.toString()<<endl;
        }
    }

    void printLab(const vector<Laboratory>& labs) const {
        if (labs.empty()) {
            cout<<"VECTOR IS EMPTY, INSERT SOME ELEMENTS"<<endl;
            return;
        }
        for (Laboratory l: labs) {
            cout << l.toString() << endl;
        }

    }

    void setDb(Database& db) {
        this->db = db;
    }
    const Database& getDb() {
        return this->db;
    }

private:
    Database db;
};

//int main() {
//    int i = 0;
//    vector<Computer> comp;
//    vector<Laboratory> lib;
//    Database db = Database(comp, lib);
//    CRUD crud = CRUD(db);
//    do{
//        Menu();
//        // choice for crud
//        cin>>i;
//        switch (i) {
//            case 1:
//                subMenu();
//                cin>>i;
//                switch (i) {
//                    case 1:
//                        crud.insertCompany();
//                        break;
//                    case 2:
//                        crud.insertLaboratory();
//                        break;
//                    default:
//                        cout<<"ENTERED CHOICE DOSE NOT EXIST"<<endl;
//                }
//                crud.getDb().saveLaboratory();
//                crud.getDb().saveComputer();
//                break;
//
//            case 2:
//                subMenu();
//                cin >> i;
//                switch (i) {
//                    case 1:
//                        crud.selectComputer();
//                        break;
//                    case 2:
//                        crud.selectLaboratory();
//                        break;
//                    default:
//                        cout<<"ENTERED CHOICE DOSE NOT EXIST"<<endl;
//                }
//
//
//                break;
//            case 3:
//                if(crud.getDb().getComputers().size() < 1)
//                    break;
//                int choice;
//                subMenu();
//                cin>>choice;
//                if (choice == 1) {
//                    crud.getDb().printComputer(crud.getDb().getComputers());
//                    crud.deleteComputer();
//                }else {
//                    crud.getDb().printLaboratory(crud.getDb().getLaboratory());
//                    crud.deleteLaboratory();
//                }
//                break;
//            case 4:
//                subMenu();
//                int x;
//                cin >> x;
//                switch (x) {
//                    case 1:
//                        crud.getDb().printComputer(crud.getDb().getComputers());
//                        break;
//                    case 2:
//                        crud.getDb().printLaboratory(crud.getDb().getLaboratory());
//                        break;
//                    default:
//                        cout<<"ENTERED CHOICE DOSE NOT EXIST"<<endl;
//                }
//                break;
//
//            case 5:
//                break;
//
//            default:
//                cout<<"ENTERED CHOICE DOSE NOT EXIST"<<endl;
//        }
//
//    } while (i != 5);
//
//    return 0;
//}

