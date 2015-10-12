// lab10-example1.cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include "HashTable.cpp"

using namespace std;

struct Account
{
    string loginName;         // (Key) Account name
    string password;          // Account password

    string getKey () const { return loginName; }
};

int main()
{
    HashTable<Account,string> accounts(8);    // List of accounts
    Account acct;                           // A single account
    string pass, name;
    ifstream fin; 
    fin.open("password.dat"); 
    // Read in information on a set of accounts.
    fin >> acct.loginName; 
    fin >> acct.password; 
    accounts.insert(acct);
    while(fin.good())
     {
        fin >> acct.loginName; 
        fin >> acct.password; 
        accounts.insert(acct);
     }
   accounts.showStructure();
   cout << "Login: "; 
   cin >> name;
   while(cin.good())
     {  
        cout <<"Password: ";  
        cin >> pass; 
        if(accounts.retrieve(name,acct) && acct.password == pass)
          cout <<"Authentication successful" <<endl; 
        else
          cout <<"Authentication failure" <<endl;
        cout << "Login: "; 
        cin >> name;
     }
    return 0;
}
