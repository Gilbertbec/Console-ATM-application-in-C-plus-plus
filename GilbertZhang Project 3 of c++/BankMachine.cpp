/// Solution project3 of C++ class in LasalleCollege Montreal December 10 2017
/// Practice using C++ Read and write with flat txt file, to Create a console ATM application
/// Gilbert Zhang xixi2010@gamil.com
#include "BoZhangLib.h"

void main()
{
	setlocale(LC_ALL, "");//to let cout print french well
	//main() will be recalled after customer put a wrong AccountNumber or a wrong password 3 times, clear screen to do the next try
	//clear the screen for the new customer
	system("cls");
	DisplayMainTitle();

	int accountsCount;//In order to record the number of accounts
	BankAccount* bankAccountArray = ReadFromText(&accountsCount);

	string accountNumber = ReadUserAccountNumber();
	string userName, userPassword;
	double accountBalance;

	bool isAccountNumberExited = IsAccountNumberExisted(bankAccountArray, accountsCount, accountNumber, &userName, &userPassword, &accountBalance);

	if (isAccountNumberExited)
	{
		if (VerifyPassword(userName, userPassword))
		{
			string choice = ShowChoiceMenuAndGetChoice();
			DoTheFunctionByChoice(choice, accountNumber, userName, userPassword, &accountBalance);

			UpdateBankAccountBalance(bankAccountArray, accountsCount, accountNumber, accountBalance);
			WriteToText(bankAccountArray, accountsCount);

			cout << endl << endl << "Merci d'avoir utiliser nos services" << endl;
			cout << "Appuyez sur une touche pour continuer..." << endl;
		}
		else
		{
			cout << "Votre nip est incorrect, merci d'avoir utiliser nos services, au revoir!" << endl;
		}
	}
	else
	{
		cout << "Votre numero de compte est incorrect, Merci d'avoir utiliser nos services, au revoir!" << endl;
	}
	cin.sync();
	_getch();
	cin.sync();
	main();
}

void DoTheFunctionByChoice(string choice, string accountNumber, string userName, string userPassword, double* accountBalance)
{
	int intChoice = atoi(choice.c_str());//in C++,only int or enum is supported for the switch

	switch (intChoice)
	{
	case 1:
		Deposer(accountNumber, userName, userPassword, accountBalance);
		Consulter(accountNumber, userName, userPassword, accountBalance);
		break;
	case 2:
		Retirer(accountNumber, userName, userPassword, accountBalance);
		Consulter(accountNumber, userName, userPassword, accountBalance);
		break;
	case 3:
		Consulter(accountNumber, userName, userPassword, accountBalance);
		break;
	}
}

void UpdateBankAccountBalance(BankAccount* bankAccounts, int accountCount, string accountNumber, double accountBalance)
{
	for (int i = 0; i < accountCount; i++)
	{
		if (bankAccounts[i].accountNumber == accountNumber)
		{
			bankAccounts[i].accountBalance = accountBalance;
		}
	}
}

bool VerifyPassword(string userName, string userPassword)
{
	bool isPasswordRight = false;
	string nip;
	cout << endl << "\t" << "Bienvenue " << userName << endl;

	//If the password is incorrect,let customer try 3 times maximum.
	for (int i = 0; i < 3; i++)
	{
		cout << "Entrez votre nip : ";
		//getline(cin, nip);
		nip = GetPassword();
		if (nip == userPassword)
		{
			isPasswordRight = true;
			break;//If the password is correct, stop Verify, do the next work.
		}
	}
	return isPasswordRight;
}

void DisplayMainTitle()
{
	DisplayTitle("banque royale", "\t\t", true);
	DisplayTitle("Guichet Automatique Bancaire", "\t", false);
}

void DisplayTitle(string s, string space, bool isCapital)
{
	cout << space;
	string underLine;
	for (int i = 0; i < s.length(); i++)
	{
		if (isCapital)
		{
			cout << char(toupper(s[i]));
		}
		else
		{
			cout << char(s[i]);
		}
		underLine += "-";
	}
	cout << endl;
	cout << space << underLine << endl;
}

string ReadUserAccountNumber()
{
	string accountNumber;
	cout << "Entrez votre numero de compte : ";
	getline(cin, accountNumber);
	return accountNumber;
}

//Check if the AccountNumber which user entered has existed.
//If it is existed,read  the AccountNumber,userName,userPassword,accountBalance, return to the evoker.
bool IsAccountNumberExisted(BankAccount* bankAccounts, int accountsCount,string accountNumber,string* userName,string* userPassword, double* accountBalance)
{
	bool isAccountNumberExisted = false;
	for (int i = 0; i < accountsCount; i++)
	{
		if (accountNumber == bankAccounts[i].accountNumber) 
		{
			isAccountNumberExisted = true;
			*userName = bankAccounts[i].userName;
			*userPassword = bankAccounts[i].userPassword;
			*accountBalance = bankAccounts[i].accountBalance;
		}
	}
	return isAccountNumberExisted;
}

BankAccount* ReadFromText(int* accountCount)
{
	string accountNumber, userName, userPassword, accountBalance;
	ifstream infile;

	*accountCount = 0;
	infile.open("D:\BankInfo.txt");
	while (infile >> accountNumber >> userName >> userPassword >> accountBalance) 
	{
		if (accountNumber.length() == 0) break;
		*accountCount += 1;
	}
	infile.close();

	int i = 0;
	infile.open("D:\BankInfo.txt");
	BankAccount* bankAccounts = new BankAccount[*accountCount];

		while (!infile.eof()) 
		{
			getline(infile, accountNumber);
			if (accountNumber.length() == 0) break;

			getline(infile, userName);
			getline(infile, userPassword);
			getline(infile, accountBalance);

			//only when the txt file in the root of D:\, this will be work well.
			//to see the detail of all the accounts, open the following comments
			//cout << "accountNumber-- " << accountNumber << endl;
			//cout << "userName-- " << userName << endl;
			//cout << "userPassword-- " << userPassword << endl;
			//cout << "accountBalance-- " << accountBalance << endl;

			BankAccount bankAccount;
			bankAccount.accountNumber = accountNumber;
			bankAccount.userName = userName;
			bankAccount.userPassword = userPassword;
			bankAccount.accountBalance = atof((accountBalance).c_str());

			bankAccounts[i] = bankAccount;
			i += 1;
		}
	infile.close();
	return bankAccounts;
}

string ShowChoiceMenuAndGetChoice()
{
	string choice;
	cout << endl << "Choisir votre Transaction" << endl;
	cout << "\t1 - Pour Deposer" << endl;
	cout << "\t2 - Pour Retirer" << endl;
	cout << "\t3 - Pour consulter" << endl;
	do 
	{
		cout << "Entrez votre choix (1-3) : ";
		getline(cin,choice);
	} while (!(choice == "1" || choice == "2" || choice == "3"));
	return choice;
}

void Deposer(string accountNumber, string userName, string userPassword, double* accountBalance)
{
	double deposerAmount;
	string strDeposerAmount;//in case the customer enter a non-number
	do 
	{
		cout << endl << "Entrez le montant a Deposer $ : ";
		getline(cin, strDeposerAmount);
		deposerAmount = atof(strDeposerAmount.c_str());
	} while ((deposerAmount < 2 && cout << "Le montant doit être supérieur à 2")
		|| (deposerAmount > 20000 && cout << "Le montant doit être inférieur à 20 000"));

	*accountBalance += deposerAmount;
	cout << "--- la transaction a reussi ---" << endl << endl;
}

void Retirer(string accountNumber, string userName, string userPassword, double* accountBalance)
{
	double retirerAmount;
	string strRetirerAmount;
	do 
	{
		cout << endl << "Entrez le montant a retirer $ : ";
		getline(cin, strRetirerAmount);
		retirerAmount = atof(strRetirerAmount.c_str());
	} while ((retirerAmount < 20 && cout << "le montant devrait être supérieur à 20" ) 
		|| (retirerAmount > 500 && cout << "le montant devrait être inférieur à 500")
		|| (((int)retirerAmount % 20) != 0 && cout << "le montant devrait être un multiple entier de 20")
		|| (retirerAmount - *accountBalance > 0 && cout << "Dépasser le montant de votre compte"));

	*accountBalance -= retirerAmount;
	cout << endl << "--- la transaction a reussi ---" << endl << endl;
}

void Consulter(string accountNumber, string userName, string userPassword, double* accountBalance)
{
	cout << "Les infos du compte" << endl;
	cout << "\tNumero : " << accountNumber << endl;
	cout << "\tClient : " << userName << endl;
	cout << "\tNip : " << userPassword << endl;
	cout << "\tSolde $ : " << to_string(*accountBalance) << endl;
}

void WriteToText(BankAccount* bankAccounts, int accountCount)
{
	ofstream outfile;
	outfile.open("D:\BankInfo.txt");
	if (outfile.is_open())
	{
		for (int i = 0; i < accountCount; i++)
		{
			outfile << bankAccounts[i].accountNumber << endl;
			outfile << bankAccounts[i].userName << endl;
			outfile << bankAccounts[i].userPassword << endl;
			outfile << to_string(bankAccounts[i].accountBalance) << endl;
		}
		outfile.close();
	}
	else
	{
		cout << "Impossible d'ouvrir le fichier de données, la transaction ne peut pas être enregistrée!" << endl;
		cout << "composez le 911 pour trouver le Programmeur" << endl;
	}
}