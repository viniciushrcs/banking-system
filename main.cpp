#include <map>
#include <cstdlib>
#include <iostream>
using namespace std;

class Account
{
private:
  long accountNumber;
  string firstName;
  string lastName;
  float balance;
  static long NextAccountNumber;

public:
  Account() {}
  Account(string fname, string lname, float balance);
};
long Account::NextAccountNumber = 0;

class Bank
{
private:
  map<long, Account> accounts;

public:
  Bank();
  Account OpenAccount(string fname, string lname, float balance);
};

int main()
{
  Bank b;
  Account acc;
  int choice;
  string fname, lname;
  long accountNumber;
  float balance;

  cout << "****Welcome to the Gringotes" << endl;
  do
  {
    cout << "\n\tSelect one option below ";
    cout << "\n\t1 Open an Account";
    cin >> choice;
    switch (choice)
    {
    case 1:
      cout << "Enter your first name: ";
      cin >> fname;
      cout << "Enter your last name: ";
      cin >> lname;
      cout << "Enter your initial balance: ";
      cin >> balance;
      acc = b.OpenAccount(fname, lname, balance);
      break;
    case7:
      break;
    default:
      cout << "\n Enter a correct choice";
      exit(0);
      break;
    }
  } while (choice != 7);

  return 0;
}

Account::Account(string fname, string lname, float balance)
{
  NextAccountNumber++;
  accountNumber = NextAccountNumber;
  firstName = fname;
  lastName = lname;
  this->balance = balance;
}
