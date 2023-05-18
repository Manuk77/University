#include<iostream>
using namespace std;

void Menu(){
    cout<<"1. INSERT"<<endl;
    cout<<"2. SELECT"<<endl;
    cout<<"3. DELETE"<<endl;
    cout<<"4. PRINT"<<endl;
    cout<<"5. EXIT"<<endl;
    cout<<"ENTER YOUR CHOICE -> ";
}

void subMenu(){
    cout<<"1. COMPUTER"<<endl;
    cout<<"2. LABORATORY"<<endl;
    cout<<"ENTER YOUR CHOICE -> ";
}



int enterCompProdName(){

    int choice;
    cout<<"ENTER 1 = prodName"<<endl;
    cout<<"ENTER 2 = ram"<<endl;
    cout<<"ENTER 3 = hdd"<<endl;
    cout<<"ENTER 4 = hdd"<<endl;
    cout<<"ENTER YOUR CHOICE -> ";
    cin>>choice;

    return choice;
}

int enterLabProdName() {
    int choice;
    cout << "ENTER 1 = name" << endl;
    cout << "ENTER 2 = roomNumber" << endl;
    cout << "ENTER YOUR CHOICE -> ";
    cin>>choice;
    return choice;
}










