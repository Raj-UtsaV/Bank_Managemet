#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

class Bank
{
private:
    friend class B_Management;
    friend class A_Management;
    int pin;
    float balance;
    string id, name, address, f_name, phone, atm_issued;
    string atm_issue_id;
    string atm_card_number;
    string cvv;
    string valid_upto;
    string atm_pin;

public:
    void menu();
    void Bank_Management();
    void ATM_Management();
};

void Bank::menu()
{
    int choice;
    char ch;
    string username;
    string pin;

    do
    {
        system("CLS");

        cout << "\n\n\t\t\t....Welcome to Our Banking System....";
        cout << "\n\t\t-----------------------------------------------------" << endl;
        cout << "\n\t\t\t\t1. Bank Management";
        cout << "\n\t\t\t\t2. ATM Management";
        cout << "\n\t\t\t\t0. Exit";
        cout << "\n\n\t\t\tEnter your choice: ";
        cin >> choice;
        cout << "\n\t\t-----------------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            cout << "\n\n\t\t\tLogin to Bank Services";
            cout << "\n\t\t\t\tEnter your username: ";
            cin >> username;
            cout << "\t\t\t\tPin Code : ";
            pin = ""; // Clear the pin
            for (int i = 0; i < 5; i++)
            { // Ensure the loop runs 5 times for a 5-digit pin
                ch = _getch();
                pin += ch;
                cout << "*";
            }
            if (username == "admin" && pin == "12345")
            {
                Sleep(1000);
                cout << "\n\t\t\t\tAccess granted!";
                Sleep(1000);
                Bank_Management();
            }
            else
            {
                cout << "\n\t\t\t\tInvalid username or pin!";
                Sleep(1000);
            }
            break;
        case 2:
            cout << "\n\n\t\t\tLogin to ATM Services...";
            cout << "\n\t\t\t\tEnter your username: ";
            cin >> username;
            cout << "\t\t\t\tPin Code : ";
            pin = ""; // Clear the pin
            for (int i = 0; i < 5; i++)
            { // Ensure the loop runs 5 times for a 5-digit pin
                ch = _getch();
                pin += ch;
                cout << "*";
            }
            if (username == "admin" && pin == "12345")
            {
                Sleep(1000);
                cout << "\n\t\t\t\tAccess granted!";
                Sleep(1000);
                ATM_Management();
            }
            else
            {
                cout << "\n\t\t\t\tInvalid username or pin!";
                Sleep(1000);
            }
            break;
        case 0:
            exit(0);
        default:
            cout << "\n\t\t\t\tInvalid choice!";
            Sleep(1000);
            break;
        }
    } while (choice != 0);
}

class B_Management
{
    Bank bank;

    bool is_number(const string &s)
    {
        return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
    }

public:
    void NewCustomer()
    {
        system("CLS");
        fstream file;
        vector<string> records;
        int newID;
        cout << "\n\n\t\t\t....Add New Customer....";
        cout << "\n\t\t-----------------------------------------------------" << endl;
        file.open("Bank_Account_Data.txt", ios::in);
        if (file)
        {
            string line, tempID;
            while (getline(file, line))
            {
                records.push_back(line);
            }
            file.close();
            if (!records.empty())
            {
                stringstream ss(records.back());
                getline(ss, tempID, '|');
                if (is_number(tempID))
                {
                    newID = stoi(tempID) + 1;
                }
                else
                {
                    newID = 10000;
                }
            }
            else
            {
                newID = 10000;
            }
        }
        else
        {
            newID = 10000;
        }
        cout << "\n\t\t\tAssigned Customer ID : " << newID;
        bank.id = to_string(newID);
        cin.ignore();
        cout << "\n\t\t\tEnter Customer Name : ";
        getline(cin, bank.name);
        Sleep(500);
        cout << "\t\t\tEnter Customer Father's Name : ";
        getline(cin, bank.f_name);
        Sleep(500);
        cout << "\t\t\tEnter Customer Address : ";
        getline(cin, bank.address);
        Sleep(500);
        cout << "\t\t\tEnter Customer Phone Number : ";
        getline(cin, bank.phone);
        Sleep(500);
        cout << "\t\t\tEnter Customer Pin : ";
        cin >> bank.pin;
        Sleep(500);
        cout << "\t\t\tEnter Customer Initial Balance : ";
        cin >> bank.balance;
        cin.ignore();
        bank.atm_issued = "NO";
        Sleep(500);
        string newRecord = bank.id + "|" + bank.name + "|" + bank.f_name + "|" + bank.address + "|" + bank.phone + "|" + bank.atm_issued + "|" + to_string(bank.pin) + "|" + to_string(bank.balance) + "|";
        records.push_back(newRecord);
        sort(records.begin(), records.end());
        file.open("Bank_Account_Data.txt", ios::out | ios::trunc);
        for (const auto &record : records)
        {
            file << record << endl;
        }
        file.close();
        cout << "\n\n\t\t\tCustomer added successfully!";
        cout << "\n\t\t-----------------------------------------------------" << endl;
        cout << "\n\t\t\tPress any key to Exit...";
        _getch();
        Sleep(1000);
        bank.Bank_Management();
    }

    void ExistingCustomer()
    {
        system("CLS");
        fstream file;
        bool found = false;
        string Name, line;
        cout << "\n\n\t\t\t....Existing Customer....";
        cout << "\n\t\t---------------------------------------------------------" << endl;
        cout << "\n\t\t\tName of Customer : ";
        cin.ignore();
        getline(cin, Name);
        Sleep(1000);
        file.open("Bank_Account_Data.txt", ios::in);
        if (!file)
        {
            cout << "\n\n\t\t\tFile Opening Error...";
        }
        else
        {
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, bank.id, '|');
                getline(ss, bank.name, '|');
                getline(ss, bank.f_name, '|');
                getline(ss, bank.address, '|');
                getline(ss, bank.phone, '|');
                getline(ss, bank.atm_issued, '|');
                ss >> bank.pin;
                ss.ignore();
                ss >> bank.balance;

                if (Name == bank.name)
                {
                    system("CLS");
                    cout << "\n\n\t\t\t....Existing Customer....";
                    cout << "\n\t\t----------------------------------------------------" << endl;
                    cout << "\n\t\t\tCustomer ID : " << bank.id;
                    cout << "\n\t\t\tName : " << bank.name;
                    cout << "\n\t\t\tFather's Name : " << bank.f_name;
                    cout << "\n\t\t\tPassword : " << bank.pin;
                    cout << "\n\t\t\tATM Issued : " << bank.atm_issued;
                    found = true;
                    cout << "\n\t\t------------------------------------------------------" << endl;
                    cout << "\n\t\t\tEnter Any key for Next Bank_Account_Data..";
                    getch();
                    Sleep(500);
                }
            }
            file.close();
            if (!found)
            {
                cout << "\n\n\t\t\tCustomer not found!";
            }
            cout << "\n\t\t\tPress any key to Exit...";
            getch();
        }
        Sleep(1000);
        bank.Bank_Management();
    }

    void DepositOptions()
    {
        system("CLS");
        string ID;
        float amount;
        bool found = false;
        fstream file, file1;
        cout << "\n\n\t\t\t....Deposit Options....";
        cout << "\n\t\t---------------------------------------------------------" << endl;
        file.open("Bank_Account_Data.txt", ios::in);
        if (!file)
        {
            cout << "\n\n\t\t\tFile Opening Error...";
            Sleep(1000);
            bank.Bank_Management();
            return;
        }
        else
        {
            cout << "\n\n\t\t\tUser ID : ";
            cin >> ID;
            cin.ignore();
            Sleep(1000);
            file1.open("Bank_Account_Data1.txt", ios::app | ios::out);
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, bank.id, '|');
                getline(ss, bank.name, '|');
                getline(ss, bank.f_name, '|');
                getline(ss, bank.address, '|');
                getline(ss, bank.phone, '|');
                getline(ss, bank.atm_issued, '|');
                ss >> bank.pin;
                ss.ignore();
                ss >> bank.balance;

                if (ID == bank.id)
                {
                    cout << "\n\t\t\tAmount to Deposit : ";
                    cin >> amount;
                    bank.balance += amount;
                    file1 << bank.id << "|" << bank.name << "|" << bank.f_name << "|" << bank.address << "|"
                          << bank.phone << "|" << bank.atm_issued << "|" << bank.pin << "|" << bank.balance << "|" << endl;
                    Sleep(1000);
                    cout << "\n\t\t\tDeposit Successful";
                    cout << "\n\t\t\tCurrent Balance : " << bank.balance;
                    cout << "\n\t\t-----------------------------------------------------" << endl;
                    found = true;
                }
                else
                {
                    file1 << bank.id << "|" << bank.name << "|" << bank.f_name << "|" << bank.address << "|"
                          << bank.phone << "|" << bank.atm_issued << "|" << bank.pin << "|" << bank.balance << "|" << endl;
                }
            }
            file.close();
            file1.close();
            remove("Bank_Account_Data.txt");
            rename("Bank_Account_Data1.txt", "Bank_Account_Data.txt");
            if (!found)
                cout << "\n\n\t\t\tCustomer not found....";
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\n\t\t\tPress any key to Exit...";
            getch();
        }
        Sleep(1000);
        bank.Bank_Management();
    }

    void WithdrawOptions()
    {
        system("CLS");
        string ID;
        int PIN;
        float amount;
        bool found = false;
        fstream file, file1;
        cout << "\n\n\t\t\t....Withdraw Options....";
        cout << "\n\t\t-----------------------------------------------" << endl;
        file.open("Bank_Account_Data.txt", ios::in);
        if (!file)
        {
            cout << "\n\n\t\t\tFile Opening Error...";
            Sleep(1000);
            bank.Bank_Management();
        }
        else
        {
            cout << "\n\n\t\t\tUser ID : ";
            cin >> ID;
            Sleep(1000);
            file1.open("Bank_Account_Data1.txt", ios::app | ios::out);
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, bank.id, '|');
                getline(ss, bank.name, '|');
                getline(ss, bank.f_name, '|');
                getline(ss, bank.address, '|');
                getline(ss, bank.phone, '|');
                getline(ss, bank.atm_issued, '|');
                ss >> bank.pin;
                ss.ignore();
                ss >> bank.balance;

                if (ID == bank.id)
                {
                    cout << "\t\t\tPassword : ";
                    cin >> PIN;
                    Sleep(1000);
                    cout << "\n\t\t\tAmount to Withdraw : ";
                    cin >> amount;
                    Sleep(1000);
                    if (amount <= bank.balance && PIN == bank.pin)
                    {
                        bank.balance -= amount;
                        file1 << bank.id << "|" << bank.name << "|" << bank.f_name << "|" << bank.address << "|"
                              << bank.phone << "|" << bank.atm_issued << "|" << bank.pin << "|" << bank.balance << "|" << endl;
                        cout << "\n\t\t\tWithdraw Successful";
                        cout << "\n\t\t\tCurrent Balance : " << bank.balance;
                        cout << "\n\t\t-----------------------------------------------------" << endl;
                    }
                    else if (PIN != bank.pin)
                    {
                        cout << "\n\t\t\tIncorrect Password";
                    }
                    else if (amount > bank.balance)
                    {
                        cout << "\n\t\t\tInsufficient Balance";
                        cout << "\n\t\t-----------------------------------------------------" << endl;
                    }
                    found = true;
                }
                else
                {
                    file1 << bank.id << "|" << bank.name << "|" << bank.f_name << "|" << bank.address << "|"
                          << bank.phone << "|" << bank.atm_issued << "|" << bank.pin << "|" << bank.balance << "|" << endl;
                }
            }
            file.close();
            file1.close();
            remove("Bank_Account_Data.txt");
            rename("Bank_Account_Data1.txt", "Bank_Account_Data.txt");
            if (!found)
                cout << "\n\n\t\t\tCustomer not found....";
            cout << "\n\t\t------------------------------------------------" << endl;
            cout << "\n\n\t\t\tPress any key to Exit...";
            getch();
        }
        Sleep(1000);
        bank.Bank_Management();
    }

    void Search()
    {
        system("CLS");
        string ID;
        bool found = false;
        fstream file;
        cout << "\n\n\t\t\t....Search Customer Record....";
        cout << "\n\t\t-------------------------------------------------" << endl;
        file.open("Bank_Account_Data.txt", ios::in);
        if (!file)
        {
            cout << "\n\n\t\t\tFile Opening Error...";
            Sleep(1000);
            bank.Bank_Management();
            return;
        }
        else
        {
            cout << "\n\n\t\t\tCustomer ID : ";
            cin >> ID;
            Sleep(2000);
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, bank.id, '|');
                getline(ss, bank.name, '|');
                getline(ss, bank.f_name, '|');
                getline(ss, bank.address, '|');
                getline(ss, bank.phone, '|');
                getline(ss, bank.atm_issued, '|');
                ss >> bank.pin;
                ss.ignore();
                ss >> bank.balance;

                if (ID == bank.id)
                {
                    system("CLS");
                    cout << "\n\n\t\t\t....Search Customer Record....";
                    cout << "\n\t\t--------------------------------------------------" << endl;
                    cout << "\n\t\t\tCustomer ID : " << bank.id;
                    cout << "\n\t\t\tName : " << bank.name;
                    cout << "\n\t\t\tFather's Name : " << bank.f_name;
                    cout << "\n\t\t\tAddress : " << bank.address;
                    cout << "\n\t\t\tPhone : " << bank.phone;
                    cout << "\n\t\t\tPin : " << bank.pin;
                    cout << "\n\t\t\tBalance : " << bank.balance;
                    cout << "\n\t\t\tATM Issued : " << bank.atm_issued;
                    found = true;
                    break;
                }
            }
            file.close();
            if (!found)
                cout << "\n\n\t\t\tCustomer not found.....";
            cout << "\n\t\t-------------------------------------------------" << endl;

            cout << "\n\t\t\tPress any key to Exit...";
            getch();
        }
        Sleep(1000);
        bank.Bank_Management();
    }

    void Edit()
    {
        system("CLS");
        fstream file, tempFile;
        string ID, line;
        bool found = false;
        cout << "\n\n\t\t\t....Edit Customer Record....";
        cout << "\n\t\t-------------------------------------------------" << endl;
        file.open("Bank_Account_Data.txt", ios::in);
        if (!file)
        {
            cout << "\n\n\t\t\tFile Opening Error...";
            Sleep(1000);
            bank.Bank_Management();
            return;
        }
        else
        {
            cout << "\n\t\t\tCustomer ID : ";
            cin >> ID;
            Sleep(2000);
            cin.ignore();
            tempFile.open("Temp.txt", ios::out);

            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, bank.id, '|');
                getline(ss, bank.name, '|');
                getline(ss, bank.f_name, '|');
                getline(ss, bank.address, '|');
                getline(ss, bank.phone, '|');
                getline(ss, bank.atm_issued, '|');
                ss >> bank.pin;
                ss.ignore();
                ss >> bank.balance;

                if (ID == bank.id)
                {
                    system("CLS");
                    cout << "\n\n\t\t\t....Edit Customer Record....";
                    cout << "\n\t\t------------------------------------------------" << endl;
                    cout << "\n\t\t\tCustomer ID : " << bank.id;
                    cout << "\n\t\t\tName : " << bank.name;
                    cout << "\n\t\t\tFather's Name : " << bank.f_name;
                    cout << "\n\t\t\tAddress : " << bank.address;
                    cout << "\n\t\t\tPhone : " << bank.phone;
                    cout << "\n\t\t\tPin : " << bank.pin;
                    cout << "\n\t\t\tATM Issued : " << bank.atm_issued;
                    cout << "\n\t\t-----------------------------------------------------" << endl;
                    cout << "\n\t\t\tEnter New Address : ";
                    getline(cin, bank.address);
                    Sleep(500);
                    cout << "\t\t\tEnter New Phone : ";
                    getline(cin, bank.phone);
                    Sleep(500);
                    cout << "\t\t\tEnter New Pin : ";
                    cin >> bank.pin;
                    cin.ignore();
                    Sleep(1000);

                    line = bank.id + "|" + bank.name + "|" + bank.f_name + "|" + bank.address + "|" + bank.phone + "|" + to_string(bank.pin) + "|" + to_string(bank.balance) + "|" + bank.atm_issued;
                    cout << "\n\t\t\tEdit successful...";
                    found = true;
                }
                tempFile << line << endl;
            }
            file.close();
            tempFile.close();
            remove("Bank_Account_Data.txt");
            rename("Temp.txt", "Bank_Account_Data.txt");

            if (!found)
                cout << "\n\n\t\t\tCustomer not found....";

            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\t\tPress any key to Exit...";
            getch();
        }
        Sleep(1000);
        bank.Bank_Management();
    }

    void Delete()
    {
        system("CLS");
        fstream bank_file, temp_bank_file, atm_file, temp_atm_file;
        string customer_id;
        int pin, retype_pin;
        bool found = false;

        cout << "\n\n\t\t\t....Delete Customer Record....";
        cout << "\n\t\t-----------------------------------------------------" << endl;

        bank_file.open("Bank_Account_Data.txt", ios::in);
        if (!bank_file)
        {
            cout << "Error: Unable to open Bank_Account_Data.txt" << endl;
            Sleep(1000);
            bank.Bank_Management();
            return;
        }

        cout << "\n\t\t\tEnter Customer ID: ";
        cin >> customer_id;
        cin.ignore();
        cout << "\n\t\t\tEnter PIN: ";
        cin >> pin;
        cin.ignore();

        string line;
        Bank bank;

        // Search for the customer record
        while (getline(bank_file, line))
        {
            stringstream ss(line);
            getline(ss, bank.id, '|');
            getline(ss, bank.name, '|');
            getline(ss, bank.f_name, '|');
            getline(ss, bank.address, '|');
            getline(ss, bank.phone, '|');
            getline(ss, bank.atm_issued, '|');
            ss >> bank.pin;
            ss.ignore();
            ss >> bank.balance;

            if (bank.id == customer_id && bank.pin == pin)
            {
                found = true;
                break;
            }
        }
        bank_file.close();

        if (!found)
        {
            cout << "\n\n\t\t\tCustomer not found or invalid PIN...";
            Sleep(1000);
            bank.Bank_Management();
            return;
        }

        // Display customer record
        system("CLS");
        cout << "\n\n\t\t\t....Delete Customer Record....";
        cout << "\n\t\t-----------------------------------------------------" << endl;
        cout << "\n\t\t\tCustomer ID : " << bank.id;
        cout << "\n\t\t\tName : " << bank.name;
        cout << "\n\t\t\tFather's Name : " << bank.f_name;
        cout << "\n\t\t\tAddress : " << bank.address;
        cout << "\n\t\t\tPhone : " << bank.phone;
        cout << "\n\t\t\tPIN : " << bank.pin;
        cout << "\n\t\t\tBalance : " << bank.balance;
        cout << "\n\t\t\tATM Issued : " << bank.atm_issued;

        // Check if ATM card is issued and display details
        if (bank.atm_issued == "YES")
        {
            atm_file.open("ATM_Data.txt", ios::in);
            if (atm_file)
            {
                while (getline(atm_file, line))
                {
                    stringstream ss(line);
                    string atm_customer_id, atm_issue_id, atm_card_number, cvv, valid_upto, atm_pin;
                    getline(ss, atm_customer_id, '|');
                    getline(ss, atm_issue_id, '|');
                    getline(ss, atm_card_number, '|');
                    getline(ss, cvv, '|');
                    getline(ss, valid_upto, '|');
                    getline(ss, atm_pin, '|');

                    if (atm_customer_id == customer_id)
                    {
                        cout << "\n\t\t-----------------------------------------------------" << endl;
                        cout << "\n\t\t\tATM Issue ID : " << atm_issue_id;
                        cout << "\n\t\t\tATM Card Number : " << atm_card_number;
                        cout << "\n\t\t\tCVV : " << cvv;
                        cout << "\n\t\t\tValid Upto : " << valid_upto;
                        cout << "\n\t\t\tATM PIN : " << atm_pin;
                        break;
                    }
                }
                atm_file.close();
            }
        }

        char confirm;
        cout << "\n\n\t\t\tAre you sure you want to delete this customer record? (y/n): ";
        cin >> confirm;
        Sleep(2000);

        if (confirm == 'y' || confirm == 'Y')
        {
            cout << "\n\t\t\tRetype PIN to confirm: ";
            cin >> retype_pin;
            if (retype_pin == pin)
            {
                // Delete customer record
                temp_bank_file.open("Temp_Bank_Account_Data.txt", ios::out);
                bank_file.open("Bank_Account_Data.txt", ios::in);
                while (getline(bank_file, line))
                {
                    stringstream ss(line);
                    getline(ss, bank.id, '|');
                    getline(ss, bank.name, '|');
                    getline(ss, bank.f_name, '|');
                    getline(ss, bank.address, '|');
                    getline(ss, bank.phone, '|');
                    getline(ss, bank.atm_issued, '|');
                    ss >> bank.pin;
                    ss.ignore();
                    ss >> bank.balance;

                    if (!(bank.id == customer_id && bank.pin == pin))
                    {
                        temp_bank_file << bank.id << "|" << bank.name << "|" << bank.f_name << "|" << bank.address << "|"
                                       << bank.phone << "|" << bank.atm_issued << "|" << bank.pin << "|" << bank.balance << "|" << endl;
                    }
                }
                bank_file.close();
                temp_bank_file.close();
                remove("Bank_Account_Data.txt");
                rename("Temp_Bank_Account_Data.txt", "Bank_Account_Data.txt");

                // Delete corresponding ATM record
                temp_atm_file.open("Temp_ATM_Data.txt", ios::out);
                atm_file.open("ATM_Data.txt", ios::in);
                while (getline(atm_file, line))
                {
                    stringstream ss(line);
                    string atm_customer_id;
                    getline(ss, atm_customer_id, '|');

                    if (atm_customer_id != customer_id)
                    {
                        temp_atm_file << line << endl;
                    }
                }
                atm_file.close();
                temp_atm_file.close();
                remove("ATM_Data.txt");
                rename("Temp_ATM_Data.txt", "ATM_Data.txt");

                cout << "\n\n\t\t\tCustomer record deleted successfully....";
            }
            else
            {
                cout << "\n\t\t\tPINs do not match. Deletion aborted.";
            }
        }
        else
        {
            cout << "\n\t\t\tDeletion cancelled....";
        }

        cout << "\n\t\t-----------------------------------------------------" << endl;
        cout << "\n\t\t\tPress any key to Exit...";
        _getch();
        Sleep(1000);
        bank.Bank_Management();
    }

    void ShowAll()
    {
        system("CLS");
        fstream file;
        vector<Bank> records;
        cout << "\n\n\t\t\t....Customer Records....";
        cout << "\n\t\t--------------------------------------------------" << endl;
        file.open("Bank_Account_Data.txt", ios::in);
        if (!file)
        {
            cout << "\n\n\t\t\tFile Opening Error...";
            Sleep(1000);
            bank.Bank_Management();
            return;
        }
        else
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                Bank bank;
                getline(ss, bank.id, '|');
                getline(ss, bank.name, '|');
                getline(ss, bank.f_name, '|');
                getline(ss, bank.address, '|');
                getline(ss, bank.phone, '|');
                getline(ss, bank.atm_issued, '|');
                ss >> bank.pin;
                ss.ignore();
                ss >> bank.balance;
                records.push_back(bank);
            }
            file.close();
            sort(records.begin(), records.end(), [](const Bank &a, const Bank &b)
                 { return a.id < b.id; });
            for (const auto &bank : records)
            {
                cout << "\n\t\t\tCustomer ID : " << bank.id;
                cout << "\n\t\t\tName : " << bank.name;
                cout << "\n\t\t\tFather's Name : " << bank.f_name;
                cout << "\n\t\t\tAddress : " << bank.address;
                cout << "\n\t\t\tPhone : " << bank.phone;
                cout << "\n\t\t\tPIN : " << bank.pin;
                cout << "\n\t\t\tBalance : " << bank.balance;
                cout << "\n\t\t\tATM Issued : " << bank.atm_issued;
                cout << "\n\t\t-----------------------------------------------------" << endl;
                Sleep(1000);
            }
            cout << "\n\n\t\t\tPress any key to Exit...";
            _getch();
            Sleep(1000);
            bank.Bank_Management();
        }
    }
};

void Bank::Bank_Management()
{
    B_Management BM;
    int choice;
    do
    {
        system("CLS");
        cout << "\n\n\t\t\t....Welcome to Banking Management System....";
        cout << "\n\t\t-----------------------------------------------------" << endl;
        cout << "\n\t\t\t\t01. New Customer";
        cout << "\n\t\t\t\t02. Existing Customer";
        cout << "\n\t\t\t\t03. Deposit Options";
        cout << "\n\t\t\t\t04. Withdraw Options";
        cout << "\n\t\t\t\t05. Search Customer Records";
        cout << "\n\t\t\t\t06. Modify Customer Record";
        cout << "\n\t\t\t\t07. Delete Customer Record";
        cout << "\n\t\t\t\t08. Show All Records";
        cout << "\n\t\t\t\t00. Go Back";
        cout << "\n\t\t\tEnter your choice: ";
        cin >> choice;
        cout << "\n\t\t-----------------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            BM.NewCustomer();
            break;
        case 2:
            BM.ExistingCustomer();
            break;
        case 3:
            BM.DepositOptions();
            break;
        case 4:
            BM.WithdrawOptions();
            break;
        case 5:
            BM.Search();
            break;
        case 6:
            BM.Edit();
            break;
        case 7:
            BM.Delete();
            break;
        case 8:
            BM.ShowAll();
            break;
        case 0:
            menu();
            return;
        default:
            cout << "\n\t\t\tInvalid choice! Please try again.";
            Sleep(1000);
        }
    } while (choice != 0);

    cout << "\n\t\t\tThank You for using Our Banking System!";
    Sleep(2000);
    exit(0);
}

class A_Management
{
private:
    Bank bank;

    string generate_random_number(int length)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 9);
        string number;
        for (int i = 0; i < length; ++i)
        {
            number += to_string(dis(gen));
        }
        return number;
    }

public:
    void Issue()
    {
        system("CLS");
        fstream bank_file, atm_file;
        vector<Bank> atm_records;
        string customer_id;
        int pin;

        cout << "\n\n\t\t\t....Issue ATM Card....";
        cout << "\n\t\t-----------------------------------------------------" << endl;

        bank_file.open("Bank_Account_Data.txt", ios::in);
        if (!bank_file)
        {
            cout << "Error: Unable to open Bank_Account_Data.txt" << endl;
            return;
        }

        cout << "\n\t\t\tEnter Customer ID: ";
        cin >> customer_id;
        cin.ignore();
        bool valid_customer = false;
        bool atm_already_issued = false;
        string line;
        while (getline(bank_file, line))
        {
            stringstream ss(line);
            getline(ss, bank.id, '|');
            getline(ss, bank.name, '|');
            getline(ss, bank.f_name, '|');
            getline(ss, bank.address, '|');
            getline(ss, bank.phone, '|');
            getline(ss, bank.atm_issued, '|');
            ss >> bank.pin;
            ss.ignore();
            ss >> bank.balance;

            if (bank.id == customer_id)
            {
                valid_customer = true;
                atm_already_issued = (bank.atm_issued == "YES");
                break;
            }
        }
        bank_file.close();

        if (!valid_customer)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid customer ID" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        cout << "\t\t\tEnter Pin: ";
        cin >> pin;
        if (bank.pin != pin)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid Pin" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        if (atm_already_issued)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tATM card already issued!" << endl;
            cout << "\n\t\tCard Number: " << bank.atm_card_number;
            cout << "\n\t\tCVV: " << bank.cvv;
            cout << "\n\t\tValid Upto: " << bank.valid_upto;
            cout << "\n\t\tPIN: " << bank.atm_pin;
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\t\tPress any key to Exit...";
            _getch();
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        // Generate the next sequential atm_issue_id
        atm_file.open("ATM_Data.txt", ios::in);
        int last_issue_id = 0;
        if (atm_file)
        {
            while (getline(atm_file, line))
            {
                stringstream ss(line);
                Bank record;
                getline(ss, record.id, '|');
                getline(ss, record.atm_issue_id, '|');
                getline(ss, record.atm_card_number, '|');
                getline(ss, record.cvv, '|');
                getline(ss, record.valid_upto, '|');
                getline(ss, record.atm_pin, '|');
                atm_records.push_back(record);

                int issue_id = stoi(record.atm_issue_id);
                if (issue_id > last_issue_id)
                {
                    last_issue_id = issue_id;
                }
            }
            atm_file.close();
        }
        int new_issue_id = last_issue_id + 1;

        bank.atm_issue_id = to_string(new_issue_id);
        bank.atm_card_number = generate_random_number(16);
        bank.cvv = generate_random_number(3);
        bank.atm_pin = generate_random_number(4);
        time_t t = time(0);
        tm *now = localtime(&t);
        bank.valid_upto = to_string((now->tm_year + 1900) + 5) + "/" + to_string(now->tm_mon + 1);
        bank.atm_issued = "YES";

        atm_records.push_back(bank);

        // Sort the records by atm_issue_id
        sort(atm_records.begin(), atm_records.end(), [](const Bank &a, const Bank &b)
             { return stoi(a.atm_issue_id) < stoi(b.atm_issue_id); });

        // Store ATM data in the file in ascending order of atm_issue_id
        atm_file.open("ATM_Data.txt", ios::out | ios::trunc);
        for (const auto &record : atm_records)
        {
            atm_file << record.id << "|" << record.atm_issue_id << "|" << record.atm_card_number << "|"
                     << record.cvv << "|" << record.valid_upto << "|" << record.atm_pin << endl;
        }
        atm_file.close();

        // Update the Bank_Account_Data.txt file to mark ATM as issued
        vector<string> bank_records;
        bank_file.open("Bank_Account_Data.txt", ios::in);
        while (getline(bank_file, line))
        {
            stringstream ss(line);
            Bank temp;
            getline(ss, temp.id, '|');
            if (temp.id == customer_id)
            {
                line = bank.id + "|" + bank.name + "|" + bank.f_name + "|" + bank.address + "|" + bank.phone + "|YES|" + to_string(bank.pin) + "|" + to_string(bank.balance) + "|";
            }
            bank_records.push_back(line);
        }
        bank_file.close();

        bank_file.open("Bank_Account_Data.txt", ios::out | ios::trunc);
        for (const auto &record : bank_records)
        {
            bank_file << record << endl;
        }
        bank_file.close();

        cout << "\n\t\t\tATM card issued successfully!";
        Sleep(1000);
        cout << endl;
        cout << "\n\t\t\tCard Number: " << bank.atm_card_number;
        cout << "\n\t\t\tCVV: " << bank.cvv;
        cout << "\n\t\t\tValid Upto: " << bank.valid_upto;
        cout << "\n\t\t\tPIN: " << bank.atm_pin;
        cout << "\n\t\t-----------------------------------------------------" << endl;
        cout << "\n\t\t\tPress any key to Exit...";
        _getch();
        Sleep(1000);
        bank.ATM_Management();
    }

    void DeactivateATM()
    {
        system("CLS");
        fstream bank_file, atm_file, tempAtmFile, tempBankFile;
        string customer_id;
        int pin, retypePIN;
        bool found = false;

        cout << "\n\n\t\t\t....Deactivate ATM Card....";
        cout << "\n\t\t-----------------------------------------------------" << endl;

        cout << "\n\t\t\tEnter Customer ID: ";
        cin >> customer_id;
        cin.ignore();

        bank_file.open("Bank_Account_Data.txt", ios::in);
        if (!bank_file)
        {
            cout << "Error: Unable to open Bank_Account_Data.txt" << endl;
            return;
        }

        // Verify customer ID and PIN
        string line;
        Bank bank;
        while (getline(bank_file, line))
        {
            stringstream ss(line);
            getline(ss, bank.id, '|');
            getline(ss, bank.name, '|');
            getline(ss, bank.f_name, '|');
            getline(ss, bank.address, '|');
            getline(ss, bank.phone, '|');
            getline(ss, bank.atm_issued, '|');
            ss >> bank.pin;
            ss.ignore();
            ss >> bank.balance;

            if (bank.id == customer_id)
            {
                found = true;
                break;
            }
        }
        bank_file.close();

        if (!found)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid customer ID" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }
        Sleep(1000);
        cout << "\t\t\tEnter Pin: ";
        cin >> pin;
        if (bank.pin != pin)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid Pin" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }
        Sleep(1000);
        // If the ATM card is issued, show ATM details
        if (bank.atm_issued == "YES")
        {
            atm_file.open("ATM_Data.txt", ios::in);
            found = false;
            Bank atm;
            while (getline(atm_file, line))
            {
                stringstream ss(line);
                getline(ss, atm.id, '|');
                getline(ss, atm.atm_issue_id, '|');
                getline(ss, atm.atm_card_number, '|');
                getline(ss, atm.cvv, '|');
                getline(ss, atm.valid_upto, '|');
                getline(ss, atm.atm_pin, '|');

                if (atm.id == customer_id)
                {
                    cout << "\n\t\t-----------------------------------------------------" << endl;
                    cout << "\n\t\tCustomer ID: " << atm.id;
                    cout << "\n\t\tATM Issue ID: " << atm.atm_issue_id;
                    cout << "\n\t\tATM Card Number: " << atm.atm_card_number;
                    cout << "\n\t\tCVV: " << atm.cvv;
                    cout << "\n\t\tValid Upto: " << atm.valid_upto;
                    cout << "\n\t\tATM Pin: " << atm.atm_pin;
                    cout << "\n\t\t-----------------------------------------------------" << endl;
                    found = true;
                    break;
                }
            }
            atm_file.close();

            if (!found)
            {
                cout << "\n\t\tATM record not found" << endl;
                Sleep(1000);
                bank.ATM_Management();
                return;
            }
            Sleep(1000);
            // Ask for confirmation to deactivate ATM card
            char confirm;
            cout << "\n\n\t\tAre you sure you want to deactivate this ATM card? (y/n): ";
            cin >> confirm;
            Sleep(2000);

            if (confirm == 'y' || confirm == 'Y')
            {
                cout << "\n\t\tRetype Pin to confirm: ";
                cin >> retypePIN;

                if (retypePIN == pin)
                {
                    // Delete the ATM record
                    tempAtmFile.open("TempATM.txt", ios::out);
                    atm_file.open("ATM_Data.txt", ios::in);
                    while (getline(atm_file, line))
                    {
                        stringstream ss(line);
                        Bank tempAtm;
                        getline(ss, tempAtm.id, '|');
                        if (tempAtm.id != customer_id)
                        {
                            tempAtmFile << line << endl;
                        }
                    }
                    atm_file.close();
                    tempAtmFile.close();
                    remove("ATM_Data.txt");
                    rename("TempATM.txt", "ATM_Data.txt");

                    // Update the bank account record to set atm_issued to "NO"
                    tempBankFile.open("TempBank.txt", ios::out);
                    bank_file.open("Bank_Account_Data.txt", ios::in);
                    while (getline(bank_file, line))
                    {
                        stringstream ss(line);
                        Bank tempBank;
                        getline(ss, tempBank.id, '|');
                        getline(ss, tempBank.name, '|');
                        getline(ss, tempBank.f_name, '|');
                        getline(ss, tempBank.address, '|');
                        getline(ss, tempBank.phone, '|');
                        getline(ss, tempBank.atm_issued, '|');
                        ss >> tempBank.pin;
                        ss.ignore();
                        ss >> tempBank.balance;

                        if (tempBank.id == customer_id)
                        {
                            tempBank.atm_issued = "NO";
                            line = tempBank.id + "|" + tempBank.name + "|" + tempBank.f_name + "|" + tempBank.address + "|" + tempBank.phone + "|" + tempBank.atm_issued + "|" + to_string(tempBank.pin) + "|" + to_string(tempBank.balance) + "|";
                        }
                        tempBankFile << line << endl;
                    }
                    bank_file.close();
                    tempBankFile.close();
                    remove("Bank_Account_Data.txt");
                    rename("TempBank.txt", "Bank_Account_Data.txt");
                    Sleep(1000);
                    cout << "\n\n\t\tATM card deactivated successfully....";
                }
                else
                {
                    Sleep(1000);
                    cout << "\n\t\tPINs do not match. Deactivation aborted.";
                }
            }
            else
            {
                Sleep(1000);
                cout << "\n\t\tDeactivation cancelled....";
            }
        }
        else
        {
            Sleep(1000);
            cout << "\n\t\tNo ATM card issued for this customer.";
        }

        cout << "\n\t\t-----------------------------------------------------" << endl;
        cout << "\n\t\tPress any key to Exit...";
        _getch();
        Sleep(1000);
        bank.ATM_Management();
    }

    void ATMInformation()
    {
        system("CLS");
        fstream bank_file, atm_file;
        string customer_id;
        int pin;
        bool valid_customer = false;
        bool atm_issued = false;
        Bank bank, atm;

        cout << "\n\n\t\t\t....Retrieve ATM Information....";
        cout << "\n\t\t-----------------------------------------------------" << endl;

        cout << "\n\t\t\tEnter Customer ID: ";
        cin >> customer_id;
        cin.ignore();
        Sleep(1000);

        bank_file.open("Bank_Account_Data.txt", ios::in);
        if (!bank_file)
        {
            cout << "Error: Unable to open Bank_Account_Data.txt" << endl;
            Sleep(1000);
            return;
        }

        string line;
        while (getline(bank_file, line))
        {
            stringstream ss(line);
            getline(ss, bank.id, '|');
            getline(ss, bank.name, '|');
            getline(ss, bank.f_name, '|');
            getline(ss, bank.address, '|');
            getline(ss, bank.phone, '|');
            getline(ss, bank.atm_issued, '|');
            ss >> bank.pin;
            ss.ignore();
            ss >> bank.balance;

            if (bank.id == customer_id)
            {
                valid_customer = true;
                atm_issued = (bank.atm_issued == "YES");
                break;
            }
        }
        bank_file.close();

        if (!valid_customer)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid customer ID" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        cout << "\t\t\tEnter Pin: ";
        cin >> pin;
        Sleep(1000);
        if (bank.pin != pin)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid Pin" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        if (!atm_issued)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tNo ATM card issued for this customer" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        atm_file.open("ATM_Data.txt", ios::in);
        if (!atm_file)
        {
            cout << "Error: Unable to open ATM_Data.txt" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }
        Sleep(1000);
        while (getline(atm_file, line))
        {
            stringstream ss(line);
            getline(ss, atm.id, '|');
            getline(ss, atm.atm_issue_id, '|');
            getline(ss, atm.atm_card_number, '|');
            getline(ss, atm.cvv, '|');
            getline(ss, atm.valid_upto, '|');
            getline(ss, atm.atm_pin, '|');

            if (atm.id == customer_id)
            {
                cout << "\n\t\t-----------------------------------------------------" << endl;
                cout << "\n\t\tCustomer ID: " << atm.id;
                cout << "\n\t\tATM Issue ID: " << atm.atm_issue_id;
                cout << "\n\t\tATM Card Number: " << atm.atm_card_number;
                cout << "\n\t\tCVV: " << atm.cvv;
                cout << "\n\t\tValid Upto: " << atm.valid_upto;
                cout << "\n\t\tATM Pin: " << atm.atm_pin;
                cout << "\n\t\t-----------------------------------------------------" << endl;
                break;
            }
        }
        atm_file.close();
        cout << "\n\t\t\tPress any key to Exit...";
        _getch();
        Sleep(1000);
        bank.ATM_Management();
    }

    void CheckBalance()
    {
        system("CLS");
        fstream atm_file, bank_file;
        string atm_card_number;
        int atm_pin;
        bool valid_card = false;
        Bank atm;

        cout << "\n\n\t\t\t....Check Balance....";
        cout << "\n\t\t-----------------------------------------------------" << endl;

        cout << "\n\t\t\tEnter ATM Card Number: ";
        cin >> atm_card_number;
        Sleep(1000);

        atm_file.open("ATM_Data.txt", ios::in);
        if (!atm_file)
        {
            cout << "Error: Unable to open ATM_Data.txt" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        string line;
        while (getline(atm_file, line))
        {
            stringstream ss(line);
            getline(ss, atm.id, '|');
            getline(ss, atm.atm_issue_id, '|');
            getline(ss, atm.atm_card_number, '|');
            getline(ss, atm.cvv, '|');
            getline(ss, atm.valid_upto, '|');
            getline(ss, atm.atm_pin, '|');

            if (atm.atm_card_number == atm_card_number)
            {
                valid_card = true;
                break;
            }
        }
        atm_file.close();

        if (!valid_card)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid ATM Card Number" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        // Check if ATM card is expired
        time_t t = time(0);
        tm *now = localtime(&t);
        int current_year = now->tm_year + 1900;
        int current_month = now->tm_mon + 1;
        int exp_year = stoi(atm.valid_upto.substr(0, 4));
        int exp_month = stoi(atm.valid_upto.substr(5, 2));

        if (current_year > exp_year || (current_year == exp_year && current_month > exp_month))
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tATM Card is expired" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        cout << "\t\t\tEnter ATM Pin: ";
        cin >> atm_pin;
        Sleep(1000);
        if (atm_pin != stoi(atm.atm_pin))
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid ATM Pin" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        bank_file.open("Bank_Account_Data.txt", ios::in);
        if (!bank_file)
        {
            cout << "Error: Unable to open Bank_Account_Data.txt" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        while (getline(bank_file, line))
        {
            stringstream ss(line);
            getline(ss, bank.id, '|');
            getline(ss, bank.name, '|');
            getline(ss, bank.f_name, '|');
            getline(ss, bank.address, '|');
            getline(ss, bank.phone, '|');
            getline(ss, bank.atm_issued, '|');
            ss >> bank.pin;
            ss.ignore();
            ss >> bank.balance;

            if (bank.id == atm.id)
            {
                cout << "\n\t\t-----------------------------------------------------" << endl;
                cout << "\n\t\tCustomer ID: " << bank.id;
                Sleep(1000);
                cout << "\n\t\tBalance: " << bank.balance;
                cout << "\n\t\t-----------------------------------------------------" << endl;
                break;
            }
        }
        bank_file.close();

        cout << "\n\t\t\tPress any key to Exit...";
        _getch();
        Sleep(1000);
        bank.ATM_Management();
    }

    void WithdrawMoney()
    {
        system("CLS");
        fstream atm_file, bank_file, tempBankFile;
        string atm_card_number;
        int atm_pin, withdraw_amount;
        bool valid_card = false;
        Bank atm, bank;

        cout << "\n\n\t\t\t....Withdraw Money....";
        cout << "\n\t\t-----------------------------------------------------" << endl;

        cout << "\n\t\t\tEnter ATM Card Number: ";
        cin >> atm_card_number;
        Sleep(1000);

        atm_file.open("ATM_Data.txt", ios::in);
        if (!atm_file)
        {
            cout << "Error: Unable to open ATM_Data.txt" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        string line;
        while (getline(atm_file, line))
        {
            stringstream ss(line);
            getline(ss, atm.id, '|');
            getline(ss, atm.atm_issue_id, '|');
            getline(ss, atm.atm_card_number, '|');
            getline(ss, atm.cvv, '|');
            getline(ss, atm.valid_upto, '|');
            getline(ss, atm.atm_pin, '|');

            if (atm.atm_card_number == atm_card_number)
            {
                valid_card = true;
                break;
            }
        }
        atm_file.close();

        if (!valid_card)
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid ATM Card Number" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        // Check if ATM card is expired
        time_t t = time(0);
        tm *now = localtime(&t);
        int current_year = now->tm_year + 1900;
        int current_month = now->tm_mon + 1;
        int exp_year = stoi(atm.valid_upto.substr(0, 4));
        int exp_month = stoi(atm.valid_upto.substr(5, 2));

        if (current_year > exp_year || (current_year == exp_year && current_month > exp_month))
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tATM Card is expired" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        cout << "\t\t\tEnter ATM Pin: ";
        cin >> atm_pin;
        Sleep(1000);
        if (atm_pin != stoi(atm.atm_pin))
        {
            cout << "\n\t\t-----------------------------------------------------" << endl;
            cout << "\n\t\tInvalid ATM Pin" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        bank_file.open("Bank_Account_Data.txt", ios::in);
        if (!bank_file)
        {
            cout << "Error: Unable to open Bank_Account_Data.txt" << endl;
            Sleep(1000);
            bank.ATM_Management();
            return;
        }

        while (getline(bank_file, line))
        {
            stringstream ss(line);
            getline(ss, bank.id, '|');
            getline(ss, bank.name, '|');
            getline(ss, bank.f_name, '|');
            getline(ss, bank.address, '|');
            getline(ss, bank.phone, '|');
            getline(ss, bank.atm_issued, '|');
            ss >> bank.pin;
            ss.ignore();
            ss >> bank.balance;

            if (bank.id == atm.id)
            {
                cout << "\n\t\t-----------------------------------------------------" << endl;
                cout << "\n\t\tCustomer ID: " << bank.id;
                Sleep(1000);
                cout << "\n\t\tCurrent Balance: " << bank.balance;
                cout << "\n\t\t-----------------------------------------------------" << endl;
                Sleep(1000);

                cout << "\n\t\t\tEnter Amount to Withdraw: ";
                cin >> withdraw_amount;
                Sleep(1000);

                if (withdraw_amount > bank.balance)
                {
                    cout << "\n\t\t-----------------------------------------------------" << endl;
                    cout << "\n\t\tInsufficient Funds" << endl;
                    Sleep(1000);
                    bank.ATM_Management();
                    return;
                }
                else
                {
                    bank.balance -= withdraw_amount;
                    cout << "\n\t\t-----------------------------------------------------" << endl;
                    cout << "\n\t\tWithdrawal Successful" << endl;
                    cout << "\n\t\tNew Balance: " << bank.balance;
                    cout << "\n\t\t-----------------------------------------------------" << endl;
                    Sleep(1000);
                }
                break;
            }
        }
        bank_file.close();

        // Update bank account data with new balance
        tempBankFile.open("TempBank.txt", ios::out);
        bank_file.open("Bank_Account_Data.txt", ios::in);
        while (getline(bank_file, line))
        {
            stringstream ss(line);
            Bank tempBank;
            getline(ss, tempBank.id, '|');
            getline(ss, tempBank.name, '|');
            getline(ss, tempBank.f_name, '|');
            getline(ss, tempBank.address, '|');
            getline(ss, tempBank.phone, '|');
            getline(ss, tempBank.atm_issued, '|');
            ss >> tempBank.pin;
            ss.ignore();
            ss >> tempBank.balance;

            if (tempBank.id == atm.id)
            {
                tempBank.balance = bank.balance;
                line = tempBank.id + "|" + tempBank.name + "|" + tempBank.f_name + "|" + tempBank.address + "|" + tempBank.phone + "|" + tempBank.atm_issued + "|" + to_string(tempBank.pin) + "|" + to_string(tempBank.balance) + "|";
            }
            tempBankFile << line << endl;
        }
        bank_file.close();
        tempBankFile.close();
        remove("Bank_Account_Data.txt");
        rename("TempBank.txt", "Bank_Account_Data.txt");

        cout << "\n\t\t\tPress any key to Exit...";
        _getch();
        Sleep(1000);
        bank.ATM_Management();
    }
};

void Bank::ATM_Management()
{
    A_Management AM;
    system("CLS");
    int choice;
    cout << "\n\n\t\t\t....Welcome to Our ATM....";
    cout << "\n\t\t-----------------------------------------------" << endl;
    cout << "\n\t\t\t\t1. Issue New ATM";
    cout << "\n\t\t\t\t2. Deactivate ATM";
    cout << "\n\t\t\t\t3. ATM Information";
    cout << "\n\t\t\t\t4. Check Balance";
    cout << "\n\t\t\t\t5. Withdraw Money";
    cout << "\n\t\t\t\t0. Go Back";
    cout << "\n\n\t\t\tEnter your choice: ";
    cin >> choice;
    cout << "\n\t\t-----------------------------------------------" << endl;

    switch (choice)
    {
    case 1:
        AM.Issue();
        break;
    case 2:
        AM.DeactivateATM();
        break;
    case 3:
        AM.ATMInformation();
        break;
    case 4:
        AM.CheckBalance();
        break;
    case 5:
        AM.WithdrawMoney();
        break;
    case 0:
        menu();
        break;
    default:
        cout << "\n\t\t\tInvalid choice!";
        Sleep(1000);
        ATM_Management();
        break;
    }
}

int main()
{
    Bank obj;
    obj.menu();
    return 0;
}