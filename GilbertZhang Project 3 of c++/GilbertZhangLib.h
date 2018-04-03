///Solution project3 of C++ class in LasalleCollege Montreal December 10 2017
/// Practice using C++ Read and write with flat txt file, to Create a console ATM application
/// Gilbert Zhang xixi2010@gamil.com
#pragma once
#include "String"
#include "iostream"
#include "fstream"
#include <sstream>
#include <conio.h>//to use _getch()

using namespace::std;

struct BankAccount
{
	string accountNumber;
	string userName;
	string userPassword;
	double accountBalance;
};

void DisplayMainTitle();
void DisplayTitle(string, string, bool);
string ReadUserAccountNumber();
BankAccount* ReadFromText(int*);
bool IsAccountNumberExisted(BankAccount*, int, string, string*, string*, double*);
bool VerifyPassword(string, string);
string ShowChoiceMenuAndGetChoice();
void Deposer(string, string, string, double*);
void Retirer(string, string, string, double*);
void Consulter(string, string, string, double*);
void WriteToText(BankAccount* BankAccounts, int accountCount);
void UpdateBankAccountBalance(BankAccount*, int, string, double);
void DoTheFunctionByChoice(string, string, string, string, double*);

string GetPassword()
{
	char password[100];
	int index = 0;
	while (true)
	{
		char ch;
		ch = _getch();
		if (ch == 8)//backspace
		{
			if (index != 0)
			{
				cout << char(8) << " " << char(8);
				index--;
			}
		}
		else if (ch == '\r' || index == 99)//return
		{
			password[index] = '\0';
			cout << endl;
			break;
		}
		else
		{
			cout << "*";
			password[index++] = ch;
		}
	}
	return password;
}