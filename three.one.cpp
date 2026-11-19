#include<iostream>
#include<string>
using namespace std;

class BankAccount {
    private:
        string owner;
        double balance;

        public:
        void open( const string& ownerName, double initial)
        {
            owner = ownerName;
            balance = (initial >0) ? initial : 0;}

            void deposit(double amount)
            {
                if(amount > 0)
                    balance += amount;
            }
            bool withdraw(double amount)
            {
                if(amount > 0 && amount <= balance)
                {
                    balance -= amount;
                    return true;
                }
                return false;
            }
            double getBalance() const
            {
                return balance;
            }
            string getowner()const
            {
                return owner;
            }
        };
        int main()
        {
            BankAccount account;
            account.open("asha", 1000);
            account.deposit(500);
            if(!account.withdraw(2000))
            cout << "Withdrawal denied(infficient)\n";
            account.withdraw(300);
            cout << account.getowner() << " balance=" << account.getBalance() << endl;
            return 0;
        }