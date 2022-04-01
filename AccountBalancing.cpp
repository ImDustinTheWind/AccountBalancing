//***********************************************************************************************************
//Programming Assignment 02
//Programmer: Dustin Sherer
//Completed: 02/5/2022
//Status: complete
//
//This program is designed to help balance a checkbook at the end of the month, by having the user enter the initial balance followed by transactions.
// For each transaction, there should be a valid transaction type: C - process a check, D - process a deposit, E - do end of the month processing and exit program.
//***********************************************************************************************************

#include <iostream>
#include <iomanip>
#include "AccountBalancing.h"


int main()
{
	std::cout << "Checkbook Balancing Program\n\n";

	double InitialBalance = EnterInitialBalance(); //declare and init Initial Balance
	double AccountBalance = InitialBalance;        //declare and init Account Balance from InitialBalance
	int ChecksProcessed = 0;					   //keeps count of ChecksProcessed
	bool CalcAgain = false;					   //bool to keep track is user wants to calculate another month

	//std::cout << "Account Balance is: $" << AccountBalance << std::endl;

	// ChooseTransaction() starts main program loop
	AccountBalance = ChooseTransaction(AccountBalance, ChecksProcessed);
	
	//pause window
	EndProcess(CalcAgain);

	return 0;
};

//ask for and return initial account balance
double EnterInitialBalance()
{
    double InitBalance = 0.0; //declare & initialize double for input

	//asks for initial balance
	std::cout << "Enter the beginning balance: ";
	std::cin >> InitBalance;
	std::cout << std::endl;

	//instructions for transaction types
	std::cout << "Commands: \nC - process a check \nD - process a deposit \nE - end the program \n\n";

	//return initial balance to main()
	return InitBalance;
}

//ask for type of transaction required, then running appropriate function
double ChooseTransaction(double  tAccountBalance, int tChecksProcessed)
{
	//initialize holding variable for transaction amount (checkAmount/depositAmount)
	double tTransactionAmount = 0.0;

	//initialize and ask user for transaction type
	char transType;
	std::cout << "Enter transaction type: ";
	std::cin >> transType;

	//Used for decision though each different transaction/process
	switch (transType)
	{
		case 'C':
			//Checks transaction amount is valid, 
			tTransactionAmount = CheckTransaction(tAccountBalance, tChecksProcessed);
			tAccountBalance = ProcessCheck(tAccountBalance, tTransactionAmount);
			tChecksProcessed++; //adds 1 to count for each check processed
			std::cout << "Total service charges: $" << std::fixed << std::setprecision(2) << ServiceCharges(tChecksProcessed) << std::endl;
			std::cout << std::endl;

			ChooseTransaction(tAccountBalance, tChecksProcessed);
			break;

		case 'D':
			tTransactionAmount = CheckTransaction(tAccountBalance, tChecksProcessed);
			tAccountBalance = ProcessDeposit(tAccountBalance, tTransactionAmount);
			std::cout << "Total service charges: $" << std::fixed << std::setprecision(2) << ServiceCharges(tChecksProcessed) << std::endl;
			std::cout << std::endl;

			ChooseTransaction(tAccountBalance, tChecksProcessed);
			break;

		case 'E':
			return ProcessEndMonth(tAccountBalance, tChecksProcessed);
			break;

		default: //if invalid char, repeat ChooseTransaction()
			std::cout << "You must enter valid transaction type:" << std::endl;
			ChooseTransaction(tAccountBalance, tChecksProcessed);
	}
}

//Checks to ensure transaction amount is valid, if  not go back to switch statement
double CheckTransaction(double trAccountBalance, int trChecksProcessed)
{
	double transactionAmount;
	std::cout << "Enter transaction amount: ";
	std::cin >> transactionAmount;

	//if invalid transaction amount "$0.00", repeat ChooseTransaction()
	if (transactionAmount < 0) 
	{
		std::cout << "Transactions can not be $0.00" << std::endl;
		ChooseTransaction(trAccountBalance, trChecksProcessed);
	}
	else
	{
		return transactionAmount;
	}
}

//if transaction is a check, subtracts from balance, returns new balance
double ProcessCheck(double cAccountBalance, double checkAmount)
{
	//double checkAmount = CheckTransaction(cAccountBalance);
	std::cout << "Processing check for $" << std::fixed << std::setprecision(2) << checkAmount << std::endl;
	checkAmount *= -1; //convert amount to negative
	cAccountBalance = AdjustBalance(cAccountBalance, checkAmount);
	std::cout << "Service charge: $0.35 for a check" << std::endl;

	return cAccountBalance;
}

//if transaction is a deposit, adds it to the balance, returns new balance
double ProcessDeposit(double dAccountBalance, double depositAmount)
{
	//double depositAmount = CheckTransaction(dAccountBalance);
	std::cout << "Processing deposit for $" << std::fixed << std::setprecision(2) << depositAmount << std::endl;
	dAccountBalance = AdjustBalance(dAccountBalance, depositAmount);

	return dAccountBalance;
}

//function completes final amount resulting from all transactions, w/ application of service fees, and returns final balance
double ProcessEndMonth(double eAccountBalance, int eChecksProcessed)
{
	std::cout << "Processing end of the month" << std::endl;
	eAccountBalance -= ServiceCharges(eChecksProcessed); //apply service charges
	std::cout << "Final balance: $" << std::fixed << std::setprecision(2) << eAccountBalance << std::endl;
	std::cout << std::endl;

	return eAccountBalance;
}

//used to perform the calculations for ProcessCheck() & ProcessDeposit functions
double AdjustBalance(double aAccountBalance, double transactionAmount)
{
	aAccountBalance = aAccountBalance + transactionAmount; //not using saved balance
	std::cout << "Balance: $" << std::fixed << std::setprecision(2) << aAccountBalance << std::endl;

	return aAccountBalance;
}

//calculate the month's worth of service charges
double ServiceCharges(int ChecksProcessed)
{
	double serviceCharges = ChecksProcessed * .35;

	return serviceCharges;
}


//function used to prevent cmd-line from insta-closing and gives user option to calculate another month
void EndProcess(bool isEndMonth)
{
	while (!isEndMonth)
	{
		char answer;
		std::cout << "Do you wish to calculate another month? (Y/N)" << std::endl;
		std::cin >> answer;
		if (answer == 'N')
		{
			isEndMonth = true;
		}
		else if (answer == 'Y')
		{ 
			std::cout << std::endl;
			main(); 
		}
		else
		{
			isEndMonth = false;
		}
	}
}