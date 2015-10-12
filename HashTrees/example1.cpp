// lab10-example1.cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include "HashTable.cpp"

using namespace std;

struct Account
{
    string loginName;         // (Key) Account name
    string password;          // Account password

    int getKey () const { return acctNum; }
    static unsigned int hash(const int& key) { return abs( key ); }
};

int main()
{
    HashTable<Account,int> accounts(11);    // List of accounts
    Account acct;                         // A single account
    int searchKey;                        // An account key
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

    // Checks for accounts and prints records if found

    cout << endl;
    cout << "Enter account number (<EOF> to end): ";
    while ( cin >> searchKey )
    {
       if ( accounts.retrieve(searchKey,acct) )
           cout << acct.acctNum << " " << acct.balance << endl;
       else
           cout << "Account " << searchKey << " not found." << endl;
    }

    return 0;
}
