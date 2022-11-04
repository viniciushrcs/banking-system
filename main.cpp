#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
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
  long getAccNo() { return accountNumber; }
  string getFirstName() { return firstName; }
  string getLastName() { return lastName; }
  float getBalance() { return balance; }

  friend ifstream &operator>>(ifstream &ifs, Account &acc);
  friend ofstream &operator<<(ofstream &ofs, Account &acc);
  friend ostream &operator<<(ostream &os, Account &acc);
  void Deposit(float amount);
  static void setLastAccountNumber(long accountNumber);
  static long getLastAccountNumber();
};
long Account::NextAccountNumber = 0;

class Bank
{
private:
  map<long, Account> accounts;

public:
  Bank()
  {
    Account account;
    ifstream infile;
    infile.open("Bank.data");
    if (!infile)
    {
      cout << "Error while opening file!" << endl;
      return;
    }
    while (!infile.eof())
    {
      infile >> account;
      accounts.insert(pair<long, Account>(account.getAccNo(), account));
    }
    Account::setLastAccountNumber(account.getAccNo());
    infile.close();
  }

  Account OpenAccount(string fname, string lname, float balance);
  Account BalanceEnquiry(long accountNumber);
  void ShowAllAccounts();
  Account Deposit(long accountNumber, float amount);
  ~Bank();
};

int main()
{
  Bank b;
  Account acc;

  int choice;
  string fname, lname;
  long accountNumber;
  float balance;
  float amount;

  cout << "**** Welcome to the Gringotes *****" << endl;
  do
  {
    cout << "\n\tSelect one option below: \n";
    cout << "\n\t1. Open an Account\n";
    cout << "\n\t2. Show account data\n";
    cout << "\n\t3. Show all accounts data\n";
    cout << "\n\t4. Deposit\n";
    cout << "\n\t7. Leave \n";
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
      cout << "**** Congratulations! Your account was created \n";
      cout << acc;
      break;
    case 2:
      cout << "Enter your account number: ";
      cin >> accountNumber;
      acc = b.BalanceEnquiry(accountNumber);
      cout << endl
           << "**** Here are your account Details: " << endl;
      cout << acc;
      break;
    case 3:
      b.ShowAllAccounts();
      break;
    case 4:
      cout << "Enter your account number: ";
      cin >> accountNumber;
      cout << "Enter the amount to deposit: ";
      cin >> amount;
      acc = b.Deposit(accountNumber, amount);
      cout << endl
           << "**** Amount is Deposited ****";
      cout << acc;
      break;
    case 7:
      cout << "**** Bye bye ****" << endl;
      exit(0);
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

Account Bank::OpenAccount(string fname, string lname, float balance)
{
  ofstream outfile;
  Account account(fname, lname, balance);

  accounts.insert(pair<long, Account>(account.getAccNo(), account));
  outfile.open("Bank.data", ios::trunc);

  map<long, Account>::iterator itr;
  for (itr = accounts.begin(); itr != accounts.end(); itr++)
  {
    outfile << itr->second;
  }
  return account;
}

Account Bank::BalanceEnquiry(long accountNumber)
{
  map<long, Account>::iterator itr;
  itr = accounts.find(accountNumber);
  return itr->second;
}

ifstream &operator>>(ifstream &ifs, Account &acc)
{
  ifs >> acc.accountNumber;
  ifs >> acc.firstName;
  ifs >> acc.lastName;
  ifs >> acc.balance;
  return ifs;
}

ostream &operator<<(ostream &os, Account &acc)
{
  os << "First Name: " << acc.getFirstName() << endl;
  os << "Last Name: " << acc.getLastName() << endl;
  os << "Account Number: " << acc.getAccNo() << endl;
  os << "Balance: " << acc.getBalance() << endl;
  return os;
}

ofstream &operator<<(ofstream &ofs, Account &acc)
{
  ofs << acc.accountNumber << endl;
  ofs << acc.firstName << endl;
  ofs << acc.lastName << endl;
  ofs << acc.balance << endl;
  return ofs;
}

void Account::setLastAccountNumber(long accountNumber)
{
  NextAccountNumber = accountNumber;
}

void Bank::ShowAllAccounts()
{
  map<long, Account>::iterator itr;

  for (itr = accounts.begin(); itr != accounts.end(); itr++)
  {
    cout << "Account number: " << itr->first << endl
         << "Account data" << endl
         << itr->second << endl;
  }
}

Account Bank::Deposit(long accountNumber, float amount)
{
  map<long, Account>::iterator itr;
  itr = accounts.find(accountNumber);
  itr->second.Deposit(amount);
  return itr->second;
}

void Account::Deposit(float amount)
{
  balance += amount;
}

long Account::getLastAccountNumber()
{
  return NextAccountNumber;
}

Bank::~Bank()
{
  ofstream outfile;
  outfile.open("Bank.data", ios::trunc);
  map<long, Account>::iterator itr;
  for (itr = accounts.begin(); itr != accounts.end(); itr++)
  {
    outfile << itr->second;
  }
  outfile.close();
}