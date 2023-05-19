#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stack>
using namespace std;

class accountHolderDetails
{
private:
	int dob;
	int accountNumber;
	char accountType[10];
	char ifscCode[10];
};

class basicInfo
{
private:
	char previousLanguage[10];

public:
	void langChange()
	{
		int a;
		cout << "what is your preferred language?" << endl;
		cout << "1. english" << endl;
		cout << "2. other languages" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "done" << endl;
			break;
		case 2:
			cout << "we do not support any other language than english. sorry! kindly adjust or press exit." << endl;
			break;
		default:
			cout << "invalid" << endl;
			break;
		}
	}
};

class privateinfo
{
private:
	int pin;
	

public:
	long long b;
	int cardNumber;
	stack<long long> passdb;
public:
	void enterPin()
	{
		cout << "enter your pin no. it must be of 4 digits." << endl;
		cin >> b;
		if (b < 1000 || b > 9999)
		{
			cout << "it is not of 4 digits" << endl;
			enterPin();
		}
		passdb.push(b);
	}
	void changePin()
	{
		int c;
		long long d, e;
		if (checkPin())
		{
			cout << "enter new pin" << endl;
			cin >> e;
			if (e < 1000 || e > 9999)
			{
				cout << "it is not of 4 digits" << endl;
				changePin();
			}
			else
			{
				passdb.push(e);
				cout << "done." << endl;
			}
		}
		else
		{
			cout << "wrong pin. going back to home" << endl;
		}
	}
	bool checkPin()
	{
		long long d;
		cout << "enter current pin." << endl;
		cin >> d;
		if (passdb.top() == d)
			return true;
		else
			return false;
	}
public:
	long long g;

public:
	void amountThere()
	{
		cout << "enter amount you have" << endl;
		cin >> g;
		if (g > 9999999999)
		{
			cout << "so much amount in not allowed in your account type." << endl;
			amountThere();
		}
	}
	void amountNeeded()
	{
		long h;
		if (checkPin())
		{
			cout << "enter amount to be debited." << endl;
			cin >> h;
			if (h > 10000 || h > g)
			{
				cout << "amount over limit." << endl;
			}
			else
			{
				cout << "rs." << h << " debited." << endl;
				g = g - h;
			}
		}
		else
			cout << "wrong pin" << endl;
	}
	void miniStatement()
	{
		if (checkPin())
		{
			cout << "\nhello! welcome to assam gramin vikash bank" << endl;
			cout << "here is your mini statement : " << endl;
			cout << "you have rs." << g << " left in your account.\n"
				 << endl;
		}
		else
		{
			cout << "wrong pin." << endl;
		}
	}
	void amountDeposit()
	{
		long o;
		if (checkPin())
		{
			cout << "enter amount to be deposited." << endl;
			cin >> o;
			if ((g + o) > 9999999999)
			{
				cout << "so much amount in not allowed in your account type." << endl;
			}
			else
			{
				cout << "rs." << o << " deposited." << endl;
				g = g + o;
			}
		}
		else
			cout << "wrong pin" << endl;
	}
};

int main()
{
	cout << "enter your name. ";
	string name;
	cin >> name;
	cout << "hi " << name << endl;
	basicInfo j;
	privateinfo l;
	l.enterPin();
	l.amountThere();
	cout << "---------------------------------------" << endl;
	cout << "ATM service starts here!" << endl;
	cout << "---------------------------------------" << endl;
	int m;
	int u = 0;
	while (u == 0)
	{
		cout << "what do you want to do today?" << endl;
		cout << "1. language preference." << endl;
		cout << "2. change pin." << endl;
		cout << "3. debit amount." << endl;
		cout << "4. mini statement." << endl;
		cout << "5. deposit amount." << endl;
		cout << "6. exit." << endl;
		cin >> m;
		{
			switch (m)
			{
			case 1:
				j.langChange();
				break;
			case 2:
				l.changePin();
				break;
			case 3:
				l.amountNeeded();
				break;
			case 4:
				l.miniStatement();
				break;
			case 5:
				l.amountDeposit();
				break;
			case 6:
				u = 1;
				break;
			default:
				cout << "invalid" << endl;
				break;
			}
		}
	}
	cout << "bye! have a nice day." << endl;
}
